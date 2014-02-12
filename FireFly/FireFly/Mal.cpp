#include "Mal.h"
#include "Utility.h"

//
const float MIN_FOLLOW_DISTANCE = 6.f;
const float DENSITY = 2.f;
const float FORCE = 5.f;

const float INNER_FOLLOW_RADIUS = 120.f;
const float OUTER_FOLLOW_RADIUS = 300.f;

Mal::Mal(sf::Vector2f position)
	: idleAnimation(Loading::getTexture("spritesheet_moth1.png"), 64, 64, 4, 1, 20, 4)
	, mRigidbody()
	, mEatingCoat(false)
	, mCoatPositon()
	, mFinishedEatingCoat(false)
{
	//start position
	setPosition(position);

	//dynamic circle
	float colRadius = 24.f;
	float density = DENSITY;
	mRigidbody.AddDynCircleBody(colRadius, getPosition(), density);

	// box2d callbacks
	mRigidbody.getBody()->SetUserData(this);

	//damping
	mRigidbody.getBody()->SetLinearDamping(3.f);
	mRigidbody.getBody()->SetFixedRotation(true);

	mRigidbody.getBody()->SetBullet(true);

	mID = "Mal";	
}


Mal::~Mal(void)
{
}

// Get pointers to other entities in start instead of the constructor to make sure the entity is spawned
void Mal::start()
{
	mZid = EntityList::getEntityList().getEntity("Zid");

	Entity* coutHole = EntityList::getEntityList().getEntity("CoatHolePoint");
	if (coutHole)
		mCoatPositon = coutHole->getPosition();
}

void Mal::updateEntity(sf:: Time timePerFrame)
{
	// Updates the animation
	idleAnimation.updateAnimation();

	// Gets zids position in box2d coords
	mZidPosition = Rigidbody::SfToBoxVec(mZid->getPosition());

	// Get the sprite from animation
	idleAnimation.updateAnimation();
	mSprite=idleAnimation.getCurrentSprite();


	// Box2d physics body
	b2Body *body = mRigidbody.getBody();
	
	//Defines the movement of Mal
	movement();


	// Sets the look direction based on velocity
	if (body->GetLinearVelocity().x < -0.2f) 
	{
		mDirLeft = true;
		mSprite.setScale(-1.f, 1.f);
	}
	else if (body->GetLinearVelocity().x > 0.2f)
	{
		mDirLeft = false;
		mSprite.setScale(1.f, 1.f);
	}
	else if(body->GetLinearVelocity().x >= -0.2f && 0.2f >= body->GetLinearVelocity().x)
	{
		if(mDirLeft == true)
		{
			mSprite.setScale(-1.f, 1.f);
		}
		else
		{
			mSprite.setScale(1.f, 1.f);
		}
	}


	//get position and rotation from Rigidbody
	mRigidbody.update();
	setPosition(mRigidbody.getPosition());
	setRotation(mRigidbody.getRotation());	
}

void  Mal::drawEntity(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(mSprite, states);

	if(Globals::DEBUG_MODE)
		mRigidbody.drawDebug(target, states);
}

void Mal::sendMessage(Entity* sender, string message)
{
	if (message == "CoatFinished")
	{
		mEatingCoat = false;
		mFinishedEatingCoat = true;
	}

}

void Mal::movement()
{
	b2Body *body = mRigidbody.getBody();

	//counter gravity
	body->ApplyForce(body->GetMass() * - b2Vec2(0, -10.f), body->GetWorldCenter(), true);

	// Current position in box2d coords
	b2Vec2 currentPosition = Rigidbody::SfToBoxVec(getPosition());

	// Zid in sf coords
	sf::Vector2f sfZidPos = Rigidbody::BoxToSfVec(mZidPosition);
			
	//Gets the direction from Mal to Zid
	b2Vec2 direction = mZidPosition - currentPosition;
	float length = direction.Normalize();

	//Depedning on distance to Zid Mal either follows Zid or moves passivly around
	// or eating coat
	if (mEatingCoat)
	{
		b2Vec2 dirRand = Rigidbody::SfToBoxVec(mCoatPositon) - currentPosition;
		dirRand.Normalize();
		dirRand *= FORCE;
		body->ApplyForceToCenter(dirRand, true);
	}
	else if (length < MIN_FOLLOW_DISTANCE && !mFinishedEatingCoat)
	{	
		// Random target behind zid
		float va = -std::atan2f(getPosition().x - sfZidPos.x, getPosition().y - sfZidPos.y);		
		b2Vec2 randTargetPos = Rigidbody::SfToBoxVec(Util::randPointInCircle(OUTER_FOLLOW_RADIUS, INNER_FOLLOW_RADIUS, va+3.14f, va)) + mZidPosition;

		b2Vec2 dirRand = randTargetPos - currentPosition;
		dirRand.Normalize();
		dirRand *= FORCE;
		body->ApplyForceToCenter(dirRand, true);

	}
	else
	{	//Passive
		//pushes Mal to a random direction
		float x = float(-1 + rand()%3);		
		float y = float(-1 + rand()%3);
		b2Vec2 force(x, y);
		force *= FORCE;
		body->ApplyForceToCenter(force, true);
	}

}

void Mal::BeginContact(b2Contact *contact, Entity* other)
{
	if (other->getID() == "Room1_Coat_Zone")
	{
		Entity* coat = EntityList::getEntityList().getEntity("Room1_Coat");
		coat->sendMessage(this, "StartEating");
		mEatingCoat = true;
	}
}

void Mal::EndContact(b2Contact *contact, Entity* other)
{

}

