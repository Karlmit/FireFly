#include "Zid.h"

#include <SFML/Window/Mouse.hpp>
#include "Box2dWorld.h"
#include "Camera.h"
#include "RayCastCallback.h"
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
const float	PICK_UP_TIME_SECONDS = 0.2f;
 
// Light
const float ZIDS_LIGHT_RADIUS = 300.f;

//waterDropp
const float WATER_FORCE = 1000.f;

Zid::Zid(sf::Vector2f position)
: mSprite(Loading::getTexture("zid.png"))
, idleAnimation(Loading::getTexture("Zid_flying_128.png", true), 128, 128, 5, 8, 20)
, dashAnimation(Loading::getTexture("Zid_spurt_spritesheet.png"), 128, 128, 5, 5, 2)
, idleSugarAnimation(Loading::getTexture("Zid_flygande_socker_spritesheet.png", true), 128, 128, 5, 8, 20)
, dashSugarAnimation(Loading::getTexture("Zid_spurt_socker_spritesheet.png"), 128, 128, 5, 5, 2)
, deathAnimation(Loading::getTexture("Zid_dod_spritesheet.png"), 128, 128, 5, 5, 20)
, electricDeathAnimation(Loading::getTexture("zid_eldod_spritesheet.png"), 128, 128, 5, 5, 20)
, deathAnimCount(0)
, dashSound(Loading::getSound("canary.wav"), true)
, mRigidbody()
, mInStickyZone(false)
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
, mFirstSugarDropped(false) 
, mElctricDeath(false)
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

	//sugar
	mSugarPile = false;
	mSugarScale = 0;

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
	mLight = new Light(sf::Color(250,226,175,255), sf::Vector2f(1000,1000), ZIDS_LIGHT_RADIUS, 360, 0, "zidLight");
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
		if (entity->getID() == "JaktSpindel")
		{
			Level::restartLevel(0.01f);
		}
	}

}




void Zid::updateEntity(sf::Time dt) 
{
	//get spoderMan & wasp
	mSpoderMan = EntityList::getEntityList().getEntity("spoderMan");
	mWasp = EntityList::getEntityList().getEntity("Wasp");
	

	// if dead restart level
	if (mAlive == false)
	{
		Level::restartLevel(6.f);
		mRigidbody.getBody()->SetLinearDamping(1);
		mLight->sendMessage(this, "KillLight", 0);

		if (deathAnimCount < 24)
		{
			deathAnimCount++;
			if(mElctricDeath == false)
			{
			deathAnimation.updateAnimation();
			mSprite = deathAnimation.getCurrentSprite();
			}
			else
			{
				electricDeathAnimation.updateAnimation();
				mSprite = electricDeathAnimation.getCurrentSprite();
			}

		}
	}


	// SugarStuff
	sugarStuff(dt);	

	// S?ger att allt ljud som Zid g?r ska h?ras fr?n Zid.
	sf::Listener::setPosition(getPosition().x, 1, getPosition().y);
	
	//Checks for contact with plastic jar crack
	if(hivemindContact == true)
	{
		//Kills Zid
//		mAlive = false;
//		Log::write("Zid died from hivemindContact.");

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
	{
		mRigidbody.getBody()->SetLinearDamping(DAMPING);
		sugarClock.restart();
	}

	
	// Apply force to go to the mouse position when pressing left mouse button
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) == true && Globals::ZID_INPUT) {
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

		//Make the hivemind zone usable.
		if(hivemindEnabled == false)
		{
			hivemindEnabled = true;
		}

	}

	// Apply impulse for the right mouse button
	static bool mouseRightDownLast = false;
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right) == true && Globals::ZID_INPUT) 
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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F11) && Globals::ZID_INPUT)
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
			if(mSugarPile)
			{
				if(mFirstSugarDropped == true)
				{
					SugarEntity->killEntity();
				}
				Entity* sugarPile = new FallingSprite("Room 2/socker_faller.png", "Room 2/socker.png", getPosition(), mDroppedSugarPosition, "sugarPile", mSugarScale);
				SugarEntity = sugarPile;
				EntityList::getEntityList().addEntity(sugarPile);
				mSugarPile = false;
				mFirstSugarDropped = true;
				
			}
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

bool Zid::inHivemindZone()
{
	return hivemindContact;
}

void Zid::BeginContact(b2Contact *contact, Entity* other)
{
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
		mElctricDeath = true;
	}
	if (other->getID() == "Sugar")
	{
		Log::write("Zid found some sugar");
		mSweetZid = true;
		mSugarPile = true;
		EntityList::getEntityList().getEntity("Wasp")->sendMessage(this, "StartHunting");
		mSugarScale = 1.f;
	}
	if(other->getID() == "sugarPile" && sugarClock.getElapsedTime().asSeconds() > PICK_UP_TIME_SECONDS && mSugarPile == false && mSugarScale > 0.f)
	{
		sugarClock.restart();
		Log::write("Zid found a sugarPile");
		mSweetZid = true;
		mSugarPile = true;
		EntityList::getEntityList().getEntity("Wasp")->sendMessage(this, "StartHunting");
		mSugarScale -= 0.3f;
		if(mSugarScale <= 0.f)
		{
			mSugarScale = 0.f;
		}

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
		jaktspindel = EntityList::getEntityList().getEntity("JaktSpindel");
		jaktspindel->sendMessage(jaktspindel, "Deactivate");
	}

	if(other->getID() == "KillZone")
	{
		mAlive = false;
	}

	if(other->getID() == "WaterDropp")
	{
		mRigidbody.getBody()->ApplyLinearImpulse(Rigidbody::SfToBoxVec(0, WATER_FORCE), mRigidbody.getBody()->GetWorldCenter(), true);
	}


	

}

void Zid::EndContact(b2Contact *contact, Entity* other)
{
	if (other->getID() == "StickyZone")
		mInStickyZone = false;
	if(other->getID() == "PC_Zone")
		mPC_Zone = false;
}

bool Zid::inPCZone()
{
	return mPC_Zone;
}
