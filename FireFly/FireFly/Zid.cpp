#include "Zid.h"

#include <SFML/Window/Mouse.hpp>
#include "Box2dWorld.h"
#include "Camera.h"
#include "RayCastCallback.h"
// #include "FireflyZone.h"
// #include "MirrorQueue.h"
#include "Log.h"
#include "Level.h"
#include "Light.h"

#include <iostream>


const float DENSITY = 3.f;
const float FORCE = 5.f;
const float IMP_FORCE = 7.f;
const float DAMPING = 2.f;
const float SCALE = 1.f/2;

// Sugar
const float EMISSION_RATE = 5.f;
const float SUGAR_GRAVITY = 120.f;
const float LOSE_SUGAR_EMISSION = 220.f;
const float LOSE_SUGAR_TIME = 0.6f;
const float AC_ZONE_SUGAR_VEL_X = -200.f;

Zid::Zid(sf::Vector2f position)
: mSprite(Loading::getTexture("zid.png"))
, idleAnimation(Loading::getTexture("Zid_flying_128.png", true), 128, 128, 5, 8, 20)
, dashAnimation(Loading::getTexture("Zid_spurt_spritesheet.png"), 128, 128, 5, 5, 2)
, idleSugarAnimation(Loading::getTexture("Zid_flygande_socker_spritesheet.png", true), 128, 128, 5, 8, 20)
, dashSugarAnimation(Loading::getTexture("Zid_spurt_socker_spritesheet.png"), 128, 128, 5, 5, 2)
, dashSound(Loading::getSound("canary.wav"), true)
, mRigidbody()
, mInStickyZone(false)
, mInFireflyZone(false)
, mParticleSystem()
, mEmitter()
, mSweetZid(false)
, mLoseSugar(false)
, mLoseSugarTimer()
, mDroppedSugarPosition()
, mInAcZone(false)
, mAlive(true)
, hivemindContact(false)
, mSlooowDooown(0)
, mLight(nullptr)
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

	//ID
	mID = "Zid";

	//Is changed when animating Zid
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


	//PC Zone
	mPC_Zone = false;
	mJumpUp = false;

	// Zids light

	mLight = new Light(sf::Color(250,226,175,255), sf::Vector2f(1000,1000), 280, 360, 0, "zidLight");
	EntityList::getEntityList().addEntity(mLight, Layer::Light, false);
} 


void Zid::sendMessage(Entity* entity, string message)
{
		if(message == "button_pressed" && mPC_Zone == true)
	{
		float xPosition = 2614.f + rand()%600;
		mRigidbody.getBody()->SetTransform(b2Vec2(Rigidbody::SfToBoxFloat(xPosition), Rigidbody::SfToBoxFloat(-getPosition().y)), 0);
		b2Vec2 force(0, -20);
		mRigidbody.getBody()->ApplyLinearImpulse(force , mRigidbody.getBody()->GetWorldCenter(), true);
		mJumpUp = true;
		PCButton.restart();
	}


	if (message == "InAcZone")
	{
		mInAcZone = true;
	}
	if (message == "OutAcZone")
	{
		mInAcZone = false;
	}
	if(message == "kill")
	{
		mAlive = false;
		Log::write("Zid died from " + entity->getID() + ".");
	}

}




void Zid::updateEntity(sf::Time dt) 
{
	// if dead restart level
	if (mAlive == false)
	{
		Level::restartLevel(6.f);
		mRigidbody.getBody()->SetLinearDamping(1);
		mLight->sendMessage(this, "KillLight", 0);
	}


	// SugarStuff
	sugarStuff(dt);	

	// S?ger att allt ljud som Zid g?r ska h?ras fr?n Zid.
	sf::Listener::setPosition(getPosition().x, 1, getPosition().y);
	
	//Checks for contact with plastic jar crack
	if(hivemindContact == true)
	{
		//Kills Zid
		mAlive = false;
		Log::write("Zid died from hivemindContact.");

	}

	// Box2d physics body
	b2Body* body = mRigidbody.getBody();

	//Checks if Zid is able to move
	if(mAlive == true)
	{
		// Checks mouse input and apply force on the rigidbody based on that
		movement();
		// Animation
		animation();
	}
	else
	{
		body->SetFixedRotation(false);
	}

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

	PC = EntityList::getEntityList().getEntity("PC");
	if(mPC_Zone == true && PC != nullptr)
	{
		PC->sendMessage(this, "in_PC_Zone");
	}
	else if(PC != nullptr)
	{
		PC->sendMessage(this, "out_of_PC_Zone");
	}

	if(mPC_Zone == false)
	{
	// Set the camera to follow zid
	Camera::currentCamera().setTargetPosition(getPosition());
	}

	// Get the position and rotation from the rigidbody
	mRigidbody.update();				
	setPosition(mRigidbody.getPosition());
	setRotation(mRigidbody.getRotation());

	//get spoderMan
	mSpoderMan = EntityList::getEntityList().getEntity("spoderMan");
	//activates or deactivates the spider for room 2	
	if(mSweetZid && mSpoderMan != nullptr)
	{
		mSpoderMan->sendMessage(this, "activate");
	}
	else if(mSpoderMan != nullptr)
	{
		mSpoderMan->sendMessage(this, "deactivate");
	}

}
		
void Zid::drawEntity(sf::RenderTarget& target, sf::RenderStates states) const
{	
	states.transform *= getTransform();
	//target.draw(idleAnimation.getCurrentSprite(), states);
	target.draw(mSprite, states);

	// Draw particles
	target.draw(mParticleSystem);

	// Debug draw
	if (Globals::DEBUG_MODE)
	{
		mRigidbody.drawDebug(target, states);

		sf::RectangleShape dropSugarRect(sf::Vector2f(50.f, 50.f));
		dropSugarRect.setPosition(mDroppedSugarPosition + sf::Vector2f(-25, -25) );
		target.draw(dropSugarRect);
	}


}

void Zid::animation()
{
	if(zidDash == true)
	{
		if(dashFrameNo < dashAnimation.getAnimLength())
		{
			dashFrameNo++;
			if (mLoseSugar)
			{
				dashSugarAnimation.updateAnimation();
				mSprite = dashSugarAnimation.getCurrentSprite();
			}
			else
			{
				dashAnimation.updateAnimation();
				mSprite = dashAnimation.getCurrentSprite();
			}
		}
		else
		{
			dashFrameNo = 0;
			zidDash = false;
			
			if (mSweetZid)
			{
				idleSugarAnimation.updateAnimation();
				mSprite = idleSugarAnimation.getCurrentSprite();
			}
			else
			{
				idleAnimation.updateAnimation();
				mSprite = idleAnimation.getCurrentSprite();
			}
		}
	}
	else
	{
		dashFrameNo = 0;
		zidDash = false;

		if (mSweetZid)
		{
			idleSugarAnimation.updateAnimation();
			mSprite = idleSugarAnimation.getCurrentSprite();
		}
		else
		{
			idleAnimation.updateAnimation();
			mSprite = idleAnimation.getCurrentSprite();
		}
		
	}
}

void Zid::movement()
{
	// Box2d physics body
	b2Body* body = mRigidbody.getBody();

	if(PCButton.getElapsedTime().asMilliseconds() > 200 && mPC_Zone == true && mJumpUp == true)
	{
		b2Vec2 force(0, 4);
		mRigidbody.getBody()->ApplyLinearImpulse(force , mRigidbody.getBody()->GetWorldCenter(), true);
		mJumpUp = false;
	}


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
/*		if (mInFireflyZone)
		{
			auto q = MirrorQueue::getMirrorQueue().getQueue();
			if (q->size() > QUEUE_LENGTH)
				q->pop();
			q->push(force);
		} */
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
				mLoseSugar = true;
				mLoseSugarTimer.restart();
				EntityList::getEntityList().getEntity("Wasp")->sendMessage(this, "StopHunting");
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
		if (mInAcZone)
			mEmitter.setParticleVelocity(sf::Vector2f() + sf::Vector2f(AC_ZONE_SUGAR_VEL_X, 0));
		else
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

	if (mLoseSugar && mLoseSugarTimer.getElapsedTime().asSeconds() < LOSE_SUGAR_TIME)
	{
		if (mInAcZone)			
			mEmitter.setParticleVelocity(thor::Distributions::deflect(sf::Vector2f(AC_ZONE_SUGAR_VEL_X, 0), 50));
		else
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

			mDroppedSugarPosition = Rigidbody::BoxToSfVec(ray.point);
		}
	}
	else
		mLoseSugar = false;

	// Update particle system
	mParticleSystem.update(dt);
}

bool Zid::isSweet()
{
	return mSweetZid;
}

sf::Vector2f Zid::getDroppedSugar()
{
	return mDroppedSugarPosition;
}

void Zid::BeginContact(b2Contact *contact, Entity* other)
{
	//if(other->getID() == "FireflyZone")
//	if(other->getID() == "FireflyZone")
//		mInFireflyZone = true;


	if (other->getID() == "StickyZone")
	{
		mInStickyZone = true;
		Log::write("Zid got stuck in StickyZone");
	}



	if(other->getID() == "PC_Zone")
	{
		mPC_Zone = true;
	}
	if(other->getID() == "spoderMan")
	{
		mAlive = false;
		Log::write("Zid died from spoderMan.");
	}

	if(other->getID() == "SpiderStart")
	{
		jaktspindel = EntityList::getEntityList().getEntity("JaktSpindel");
		jaktspindel->sendMessage(jaktspindel, "Activate");
	}
	if(other->getID() == "Electric")
	{
		mAlive = false;
		Log::write("Zid died from electric.");
	}
	if (other->getID() == "Sugar")
	{
		Log::write("Zid found some sugar");
		mSweetZid = true;
		EntityList::getEntityList().getEntity("Wasp")->sendMessage(this, "StartHunting");
	}
	if(other->getID() == "CrackZone")
	{
		hivemindContact = true;
	}

	if (other->getID() == "Wasp")
	{
		Log::write("Zid died from wasp.");
		mAlive = false;
	}

	if(other->getID() == "BalkPortZone")
	{
		Entity* balkport = EntityList::getEntityList().getEntity("BalkPort");
		balkport->sendMessage(balkport, "Activate");
	}

}

void Zid::EndContact(b2Contact *contact, Entity* other)
{
	
	if(other->getID() == "CrackZone")
		hivemindContact = false;
	if (other->getID() == "StickyZone")
		mInStickyZone = false;
	if(other->getID() == "PC_Zone")
		mPC_Zone = false;
}

bool Zid::inPCZone()
{
	return mPC_Zone;
}
