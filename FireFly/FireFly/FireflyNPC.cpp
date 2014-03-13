 #include "FireflyNPC.h"
 #include "Utility.h"
 #include "MirrorQueue.h"
 #include <iostream>

const float MIN_FOLLOW_DISTANCE = 5.f;
const float DENSITY = 3.f;
const float FORCE = 5.f;


FireflyNPC::FireflyNPC(sf::Vector2f position)
	: idleAnimation(Loading::getTexture("zidIdleAnim.png"), 64, 64, 1, 8, 10)
	, dashAnimation(Loading::getTexture("explosionAnim.png"), 64, 64, 5, 5, 2)
	,mRigidbody()
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

	mID = "FireflyNPC";

	imitateZid = false;
}


FireflyNPC::~FireflyNPC(void)
{
}

//Get pointers to other entities in start instead of the constructor to make sure the entity is spawned
void FireflyNPC::start()
{
	mZid = EntityList::getEntityList().getEntity("Zid");
	mZone = EntityList::getEntityList().getEntity("CrackZone");
}

void FireflyNPC::updateEntity(sf::Time timePerFrame)
{

	//Gets CrackZones position in Box2D coords
	mZonePosition = Rigidbody::SfToBoxVec(230, 1246);

	//Get the sprite from animation
	idleAnimation.updateAnimation();
	mSprite=idleAnimation.getCurrentSprite();

	//Box2D physics body
	b2Body *body = mRigidbody.getBody();

	//Defines the movement of FireflyNPC
	movement();

	//Sets the look irection based on velocity
	if(body->GetLinearVelocity().x < -0.2f)
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
	//Get position and rotation from Rigidbody
	mRigidbody.update();
	setPosition(mRigidbody.getPosition());
	setRotation(mRigidbody.getRotation());
}

void FireflyNPC::drawEntity(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(mSprite, states);
	if(Globals::DEBUG_MODE)
		mRigidbody.drawDebug(target, states);
}

void FireflyNPC::movement()
{
	b2Body *body = mRigidbody.getBody();

	//counter gravity
	body->ApplyForce(body->GetMass() * - b2Vec2(0, -10.f), body->GetWorldCenter(), true);

	//Current position in box2d coords
	b2Vec2 currentPosition = Rigidbody::SfToBoxVec(getPosition());
//	std::cout << currentPosition.x << ", " << currentPosition.y << endl;

	//Zid in sf coords
	sf::Vector2f sfZonePos = Rigidbody::BoxToSfVec(mZonePosition);
//	std::cout << sfZonePos.x << ", " << sfZonePos.y << endl;

	//Gets the direction from FireflyNPC to Zid
	b2Vec2 direction = mZonePosition - currentPosition;
//	std::cout << direction.x << ", " << direction.y << endl;

	//Converts the direction into a distance
	float length = direction.Normalize();


	//Depending on if Zid is next to the jar, FireFlyNPC either traces Zids movements or moves passively
	if(imitateZid == false)
	{
		//Passive, FireflyNPC is pushed in random directions violently
		float x = float(-1 + rand()%3);
		float y = float(-1 + rand()%3);
		b2Vec2 force(x, y);
		force *= FORCE;
		body->ApplyForceToCenter(force, true);
	}
	else
	{
		b2Vec2 dirRand = mZonePosition - currentPosition;
		dirRand.Normalize();
		dirRand *= FORCE;
		body->ApplyForceToCenter(dirRand, true);
	/*	auto q = MirrorQueue::getMirrorQueue().getQueue();
		if (q->size() >= QUEUE_LENGTH)
		{
			body->ApplyForceToCenter(FORCE*(q->front()),true);
			q->pop();
		}	*/

	}
}