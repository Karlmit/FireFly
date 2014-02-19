#include "Zid.h"

#include <SFML/Window/Mouse.hpp>
#include "Box2dWorld.h"
#include "Camera.h"
#include "RayCastCallback.h"

#include <iostream>

const float DENSITY = 3.f;
const float FORCE = 5.f;
const float IMP_FORCE = 7.f;
const float DAMPING = 2.f;
const float SCALE = 1.f;

// Sugar
const float EMISSION_RATE = 5.f;
const float SUGAR_GRAVITY = 120.f;
const float LOSE_SUGAR_EMISSION = 220.f;
const float LOSE_SUGAR_TIME = 0.6f;

Zid::Zid(sf::Vector2f position)
: mSprite(Loading::getTexture("zid.png"))
, idleAnimation(Loading::getTexture("zidIdleAnim.png", true), 64, 64, 1, 8, 10)
, dashAnimation(Loading::getTexture("explosionAnim.png"), 64, 64, 5, 5, 2)
, dashSound(Loading::getSound("canary.wav"), true)
, mRigidbody()
, mInStickyZone(false)
, mParticleSystem()
, mEmitter()
, mSweetZid(false)
, mLoseSugarTimer()
{
	// Sätter origin för spriten till mitten
	sf::FloatRect bounds = mSprite.getLocalBounds();
	mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

	// Sätter startposition
	setPosition(position);

	// Sätter camerans start position
	Camera::currentCamera().setPosition(position);
	Camera::currentCamera().setTargetPosition(position);

	// Adds a dynamic circle body to zid
	float colRadius = 24.f;
	float density = DENSITY;
	mRigidbody.AddDynCircleBody(colRadius, getPosition(), density);

	// Damping for slowing zid down when not moving
	mRigidbody.getBody()->SetLinearDamping(DAMPING);
	mRigidbody.getBody()->SetFixedRotation(true);

	// Set zid as bullet to prevent going through stuff
	mRigidbody.getBody()->SetBullet(true);

	// So zid can be used in callbacks
	mRigidbody.getBody()->SetUserData(this);

	mID = "Zid";
	dashFrameNo = 0;

	// Set up particle system //
	// Create emitter
	mEmitter.setEmissionRate(EMISSION_RATE);
	mEmitter.setParticleLifetime(sf::seconds(3.f));
	mEmitter.setParticleScale(sf::Vector2f(0.2f, 0.2f));
	mEmitter.setParticleColor(sf::Color::White);

	

	// Create particle system, add reference to emitter
	mParticleSystem.setTexture(Loading::getTexture("particle.png"));
	mParticleSystem.addEmitter(thor::refEmitter(mEmitter));

	// fade in/out animations
	thor::FadeAnimation fader(0.09f, 0.1f);

	// Add particle affectors
	//mParticleSystem.addAffector( thor::AnimationAffector(colorizer) );
	mParticleSystem.addAffector( thor::AnimationAffector(fader) );
	mParticleSystem.addAffector( thor::TorqueAffector(100.f) );
	mParticleSystem.addAffector( thor::ForceAffector(sf::Vector2f(0.f, SUGAR_GRAVITY))  );

	
} 



void Zid::updateEntity(sf::Time dt) 
{
	// SugarStuff
	sugarStuff(dt);	

	// S?ger att allt ljud som Zid g?r ska h?ras fr?n Zid.
	sf::Listener::setPosition(getPosition().x, 1, getPosition().y);
	
	if(zidDash == true)
	{
		if(dashFrameNo < dashAnimation.getAnimLength())
		{
			dashFrameNo++;
			dashAnimation.updateAnimation();
			mSprite = dashAnimation.getCurrentSprite();
		}
		else
		{
		dashFrameNo = 0;
		zidDash = false;
		idleAnimation.updateAnimation();
		mSprite = idleAnimation.getCurrentSprite();
		}
	}
	else
	{
		dashFrameNo = 0;
		zidDash = false;
		idleAnimation.updateAnimation();
		mSprite = idleAnimation.getCurrentSprite();
	}

	

	// Box2d physics body
	b2Body* body = mRigidbody.getBody();

	
	// Checks mouse input and apply force on the rigidbody based on that
	movement();
	

	// Change direction on the sprite based on velocity
	
	if (body->GetLinearVelocity().x < -0.1f) 
	{
		mDirLeft = true;
		mSprite.setScale(-SCALE, SCALE);
	}
	else if (body->GetLinearVelocity().x > 0.1f)
	{
		mDirLeft = false;
		mSprite.setScale(SCALE, SCALE);
	}
	else if(body->GetLinearVelocity().x >= -0.1f && 0.1f >= body->GetLinearVelocity().x)
	{
		if(mDirLeft == true)
		{
			mSprite.setScale(-SCALE, SCALE);
		}
		else
		{
			mSprite.setScale(SCALE, SCALE);
		}
	}


	// Set the camera to follow zid
	Camera::currentCamera().setTargetPosition(getPosition());

	// Get the position and rotation from the rigidbody
	mRigidbody.update();				
	setPosition(mRigidbody.getPosition());
	setRotation(mRigidbody.getRotation());
}
		
void Zid::drawEntity(sf::RenderTarget& target, sf::RenderStates states) const
{	
	states.transform *= getTransform();
	//target.draw(idleAnimation.getCurrentSprite(), states);
	target.draw(mSprite, states);

	// Draw particles
	target.draw(mParticleSystem);

	// Rigidbody debug draw
	if (Globals::DEBUG_MODE)
		mRigidbody.drawDebug(target, states);
}

void Zid::movement()
{
	// Box2d physics body
	b2Body* body = mRigidbody.getBody();


	// Counter gravity
	body->ApplyForce(body->GetMass() * - b2Vec2(0,-10.f), body->GetWorldCenter(), true);

	if (mInStickyZone)
		mRigidbody.getBody()->SetLinearDamping(999.f);

	// Reset the damping if changed due to StickyZone when dashing
	if (zidDash)
		mRigidbody.getBody()->SetLinearDamping(DAMPING);

	
	// Apply force to go to the mouse position when pressing left mouse button
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) == true) {
		sf::Vector2f mousePos = Camera::currentCamera().getMousePosition();

		b2Vec2 mouse = Rigidbody::SfToBoxVec(mousePos);
		b2Vec2 force = mouse - Rigidbody::SfToBoxVec(getPosition());
		float length = force.Normalize();

		// If mouse is a certain distance away use full force
		// and decrease it when mouse is closer to Zid
		if (length > 0.5f) {			

			force *= FORCE;
			body->ApplyForceToCenter(force, true);
		}
		else
		{
			force *= FORCE * (length / 0.5f) * 0.5f;
			body->ApplyForceToCenter(force, true);
		}
	}

	// Apply impulse for the right mouse button
	static bool mouseRightDownLast = false;
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right) == true) 
	{
		if (mouseRightDownLast) {
			//mouseRightDownLast = false;
		}
		else {
			mouseRightDownLast = true;			

			// Reset the damping if changed due to StickyZone when dashing
			mRigidbody.getBody()->SetLinearDamping(DAMPING);

			// Calculate direction and impulse from zids position and mouse position
			sf::Vector2f mousePos = Camera::currentCamera().getMousePosition();
			b2Vec2 mouse = Rigidbody::SfToBoxVec(mousePos);
			b2Vec2 force = mouse - Rigidbody::SfToBoxVec(getPosition());
			float length = force.Normalize();

			force *= IMP_FORCE;

			// Apply impulse
			body->ApplyLinearImpulse(force , body->GetWorldCenter(), true);
			zidDash = true;
			if (mSweetZid)
			{
				mSweetZid = false;
				mLoseSugarTimer.restart();
			}


			//Temporary until a real dashsound
			//dashSound.play();
		}
			
	}
	else {
		mouseRightDownLast = false;
	}


	// Debug teleport ability with F11 and mouse position
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F11))
	{
		body->SetTransform(Rigidbody::SfToBoxVec(Camera::currentCamera().getMousePosition()), 0);
	}

}

void Zid::sugarStuff(sf::Time dt)
{
	if (mSweetZid)
	{		
		mEmitter.setParticleVelocity(sf::Vector2f());
		mEmitter.setParticlePosition( thor::Distributions::circle(getPosition(), 10.f) );
		mEmitter.setEmissionRate(EMISSION_RATE);

		// Manage lifetime of particle based on distance to the ground
		RayCastCallback ray;
		b2Vec2 from = Rigidbody::SfToBoxVec(getPosition());
		b2Vec2 to = from + b2Vec2(0, -30);
		Box2dWorld::instance().RayCast(&ray, from, to);
		if (ray.hit)
		{
			float distance = Rigidbody::BoxToSfFloat( (Rigidbody::SfToBoxVec(getPosition()) - ray.point).Length() );
			float lifetime = sqrtf(2 * distance / SUGAR_GRAVITY);	// Fysik A ftw
		
			mEmitter.setParticleLifetime(sf::seconds(lifetime+0.02f));
		}
	}
	else
	{
		mEmitter.setEmissionRate(0);
	}

	if (mLoseSugarTimer.getElapsedTime().asSeconds() < LOSE_SUGAR_TIME)
	{
		mEmitter.setParticleVelocity( thor::Distributions::circle(sf::Vector2f(), 100));
		mEmitter.setParticlePosition( thor::Distributions::circle(getPosition(), 10.f) );
		mEmitter.setEmissionRate(LOSE_SUGAR_EMISSION);

		// Manage lifetime of particle based on distance to the ground
		RayCastCallback ray;
		b2Vec2 from = Rigidbody::SfToBoxVec(getPosition());
		b2Vec2 to = from + b2Vec2(0, -30);
		Box2dWorld::instance().RayCast(&ray, from, to);
		if (ray.hit)
		{
			float distance = Rigidbody::BoxToSfFloat( (Rigidbody::SfToBoxVec(getPosition()) - ray.point).Length() );
			float lifetime = sqrtf(2 * distance / SUGAR_GRAVITY);	// Fysik A ftw
		
			mEmitter.setParticleLifetime(sf::seconds(lifetime*0.90f));
		}
	}

	// Update particle system
	mParticleSystem.update(dt);
}

void Zid::BeginContact(b2Contact *contact, Entity* other)
{
	if (other->getID() == "StickyZone")
	{
		mInStickyZone = true;
	}

	if (other->getID() == "Sugar")
	{
		mSweetZid = true;
	}
}

void Zid::EndContact(b2Contact *contact, Entity* other)
{
	if (other->getID() == "StickyZone")
	{
		mInStickyZone = false;
	}
}
