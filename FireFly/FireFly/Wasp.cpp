#include "Wasp.h"
#include "Utility.h"

const float MIN_FOLLOW_DISTANCE = 5.f;
const float DENSITY = 0.5f;
const float FORCE = 0.8f;

const float SCALE = 0.8f;

Wasp::Wasp(sf::Vector2f position)
	: idleAnimation(Loading::getTexture("balgeting_flygande_spritesheet.png"), 128, 128, 6, 6, 20)
	, attackAnimation(Loading::getTexture("balgeting_attack_spritesheet.png"), 128, 128, 6, 6, 20)
	, mRigidbody()
	, mHunting(false)
{
	//start position
	setPosition(position);

	//dynamic circle
	float colRadius = 24.f;
	float density = DENSITY;
	mRigidbody.AddDynCircleBody(colRadius, getPosition(), density);

	//damping
	mRigidbody.getBody()->SetLinearDamping(3.f);
	mRigidbody.getBody()->SetFixedRotation(true);
	mRigidbody.getBody()->SetBullet(true);
	mRigidbody.getBody()->SetUserData(this);

	mID = "Wasp";

	bonkFrame = 0;
	bonk = false;	
}


// Get pointers to other entities in start instead of the constructor to make sure the entity is spawned
void Wasp::start()
{
	mZid = EntityList::getEntityList().getEntity("Zid");

	if (isProperty("hunting"))
		mHunting = getProperty("hunting") == "true";
}

void Wasp::sendMessage(Entity* sender, string message)
{
	if (message == "StartHunting")
		mHunting = true;
	else if (message == "StopHunting")
		mHunting = false;
}

void Wasp::updateEntity(sf::Time timePerFrame)
{
	// Gets Zids position in Box2D coords
	mZidPosition = Rigidbody::SfToBoxVec(mZid->getPosition());

	//Get the sprite from animation
	if (bonk)
	{
		attackAnimation.updateAnimation();
		mSprite = attackAnimation.getCurrentSprite();
	}
	else
	{
		idleAnimation.updateAnimation();
		mSprite = idleAnimation.getCurrentSprite();	
	}

	//Box2D physics body
	b2Body *body = mRigidbody.getBody();

	//Defines the movement of Wasp
	movement();

	// Sets the look direction based on velocity
	if (body->GetLinearVelocity().x < -0.2f)
	{
		mDirLeft = true;
		mSprite.setScale(-SCALE, SCALE);
	}
	else if (body->GetLinearVelocity().x > 0.2f)
	{
		mDirLeft = false;
		mSprite.setScale(SCALE, SCALE);
	}
	else if(body->GetLinearVelocity().x >= -0.2f && 0.2f >= body->GetLinearVelocity().x)
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
	//Get position and rotation from Rigidbody
	mRigidbody.update();
	setPosition(mRigidbody.getPosition());
	setRotation(mRigidbody.getRotation());
}

void Wasp::drawEntity(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(mSprite, states);
	if(Globals::DEBUG_MODE)
		mRigidbody.drawDebug(target, states);
}

void Wasp::movement()
{
	b2Body *body = mRigidbody.getBody();

	//counter gravity
	body->ApplyForce(body->GetMass() * - b2Vec2(0, -10.f), body->GetWorldCenter(), true);

	//Current position in box2d coords
	b2Vec2 currentPosition = Rigidbody::SfToBoxVec(getPosition());

	//Zid in sf coords
	sf::Vector2f sfZidPos = Rigidbody::BoxToSfVec(mZidPosition);

	//Gets the direction from Wasp to Zid
	b2Vec2 direction = mZidPosition - currentPosition;

	//Converts the direction into a distance
	float length = direction.Normalize();

	

	//Depending on distance to Zid, Wasp either charges at Zid or moves passively
	if(length < MIN_FOLLOW_DISTANCE && mHunting)
	{
		if(bonk == false)
		{
			// Moves slower away from Zid (then proceeds with protocol "bonk")
			float va = -std::atan2f(getPosition().x - sfZidPos.x, getPosition().y - sfZidPos.y);
			b2Vec2 dirRand = mZidPosition - currentPosition;
			dirRand.Normalize();
			dirRand *= FORCE*-0.3f;
			body->ApplyForceToCenter(dirRand, true);
			++bonkFrame;
			if(bonkFrame >= 60)
			{
				bonk = true;
				attackAnimation.resetAnimation();
			}
		}
		else if(bonk == true)
		{
			// Moves quickly towards Zid (and bumps into the jar)
			float va = -std::atan2f(getPosition().x - sfZidPos.x, getPosition().y - sfZidPos.y);
			b2Vec2 dirRand = mZidPosition - currentPosition;
			dirRand.Normalize();
			dirRand *= FORCE*2;
			body->ApplyForceToCenter(dirRand, true);
			--bonkFrame;
			if(bonkFrame < 1)
			{
				bonk = false;
			}
		}
	}
	else
	{
		//Passive, wasp is pushed in random directions violently
		float x = float(-1 + rand()%3);
		float y = float(-1 + rand()%3);
		b2Vec2 force(x, y);
		force *= FORCE*(2.f);
		body->ApplyForceToCenter(force, true);
		bonkFrame = 0;
		bonk = false;
	}
}