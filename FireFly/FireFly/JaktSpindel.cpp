#include "JaktSpindel.h"
#include "Utility.h"
#include <iostream>
#include "EntityList.h"

const float SPEED = 380.f;
const float SCALE = 1.f;
const float FOLLOW_DISTANCE_ZID_SQR = 600.f*600.f;
const float MIN_DISTANCE_TO_SWEET_ZID_SQR = 200.f*200.f;
const float MIN_DISTANCE_TO_SUGAR_SQR = 150.f*150.f;
const float TIME_CHECKING_OUT_SUGAR = 12.F;
const float ATTACK_DISTANCE = 110.f;
const float ATTACK_SPEED = 10.f;

JaktSpindel::JaktSpindel(float pos, vector<sf::Vector2f> path, vector<float> lengths, vector<sf::Vector2f> directions, float totalLength)
	: mPath(path)
	, mLengths(lengths)
	, mDirections(directions)
	, mTotalLength(totalLength)
	, mIdle(true)
	, mMoveForward(true)
	, mIdleMoveTimer()
	, mIdleMove(true)
	, mSuperTweenRotation()
	, mRotation(0)
	, mTargetRotation(0)
	, mSpeed(SPEED + Util::randFloat(-20.f, 20.f))
	, mPos(0)
	, walkAnimation(Loading::getTexture("spiderwalking1.png"), 256, 256, 2, 8, 65)
	, attackAnimation(Loading::getTexture("spindel_attack.png"), 256, 256, 2, 8, 65)
{
	mID = "JaktSpindel";
	// Sätter origin för spriten till mitten
	sf::FloatRect bounds = walkAnimation.getCurrentSprite().getLocalBounds();
	mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);


	//fadetoblack = static_cast<FadeToBlack*>(EntityList::getEntityList().getEntity("fade"));
//	fadetoblack->setNextLevel("schakt1");
//	fadetoblack->activate(false);
//	//EntityList::getEntityList().addEntity(&fade);

	mActivate = false;
	mAttack = false;
	setPosition(pos);
}

void JaktSpindel::start()
{
	mZid = static_cast<Zid*>(EntityList::getEntityList().getEntity("Zid"));
}


void JaktSpindel::sendMessage(Entity* entity, std::string message)
{
	if(message == "Activate")
	{
		mActivate = true;
	}

}

void JaktSpindel::updateEntity(sf::Time dt)
{
	if(mActivate == true)
	{
		walkAnimation.updateAnimation();
		mSprite = walkAnimation.getCurrentSprite();

		// When to destroy 5pathway
		if (mPos == mTotalLength)
		{
			mActivate = false;
			//this->killEntity();
		}

		//check length from zid to jaktSpindel
		sf::Vector2f direction = getPosition() - mZid->getPosition();
		float length = direction.getLength();
		if(length <= ATTACK_DISTANCE)
		{
			mAttack = true;
		}


		if(mAttack == false)
		{
		// Move Right
		setPosition(mPos + SPEED * dt.asSeconds());
		mMoveForward = true;
		}
		else
		{
			attack();
			attackAnimation.updateAnimation();
			mSprite = attackAnimation.getCurrentSprite();
			mSprite.setOrigin(256/2, 240);
			mZid->sendMessage(this, "kill");
			//Level::getLevel().fadeToBlackChangeLevel("schakt1.tmx");
		}


		// Rotation //
		float satan =  std::atan2f(mCurrentDirection.y, mCurrentDirection.x);
		float newRotation = satan * 180/3.14f;

		if (abs(mRotation - newRotation)  > 180)
		{
			if (newRotation > mRotation)
				newRotation -= 360;
			else
				newRotation += 360;
		}

		if(abs(mRotation - newRotation) > 0.1f)
		{
			mSuperTweenRotation.clearTweens();
			mSuperTweenRotation.addTween(&CDBTweener::TWEQ_CUBIC, CDBTweener::TWEA_OUT, 1.0f, &mRotation, newRotation);		
		}

		mSuperTweenRotation.update(dt);
		mSprite.setRotation(mRotation);
		// --------- //
		
		// Set the scale to turn the sprite left or right
		if (mMoveForward)
			mSprite.setScale(-SCALE, -SCALE);
		else
			mSprite.setScale(SCALE, SCALE);

	}	
}

void JaktSpindel::drawEntity(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(mSprite, states);
}

void JaktSpindel::attack()
{
	sf::Vector2f direction = mZid->getPosition() - getPosition();
	direction.normalize();
	sf::Vector2f position = Entity::getPosition();
	if(getPosition() != mZid->getPosition())
	{
		Entity::setPosition(position + direction*ATTACK_SPEED);
	}
}


void JaktSpindel::setPosition(float x)
{	
	if (x > mTotalLength)
		x = mTotalLength;
	if (x < 0)
		x = 0;

	sf::Vector2f Position;
	mPos = x;
	float StagePos = x;
	int StageIndex = 0;

	if (StageIndex != mPath.size()-1 && StagePos >= 0)
	{
		//StagePos += SPEED * dt.asSeconds();
		while (StagePos > mLengths[StageIndex])
		{
			StagePos -= mLengths[StageIndex]; 
			StageIndex++;              
			if (StageIndex == mPath.size()-1) 
			{
				Position = mPath[StageIndex];
				return;
			}
		}
		Position = mPath[StageIndex] + mDirections[StageIndex] * StagePos;
		//if (mMoveForward)
			mCurrentDirection = mDirections[StageIndex];
		//else 
			//mCurrentDirection = -mDirections[StageIndex];
	}

	Entity::setPosition(Position);
}

sf::Vector2f JaktSpindel::calcPosition(float x)
{
	if (x > mTotalLength)
		x = mTotalLength;
	if (x < 0)
		x = 0;

	sf::Vector2f Position;
	float StagePos = x;
	int StageIndex = 0;

	if (StageIndex != mPath.size()-1 && StagePos >= 0)
	{
		//StagePos += SPEED * dt.asSeconds();
		while (StagePos > mLengths[StageIndex])
		{
			StagePos -= mLengths[StageIndex]; 
			StageIndex++;              
			if (StageIndex == mPath.size()-1) 
			{
				Position = mPath[StageIndex];
				return Position;
			}
		}
		Position = mPath[StageIndex] + mDirections[StageIndex] * StagePos;
		//if (mMoveForward)
			//mCurrentDirection = mDirections[StageIndex];
		//else 
			//mCurrentDirection = -mDirections[StageIndex];
	}

	//Entity::setPosition(Position);
	return Position;
}