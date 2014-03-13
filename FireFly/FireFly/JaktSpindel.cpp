#include "JaktSpindel.h"
#include "Utility.h"
#include <iostream>
#include "EntityList.h"

const float SPEED = 380.f;
const float SCALE = 1.f;
const float FOLLOW_DISTANCE_ZID_SQR = 600.f*600.f;
const float ATTACK_DISTANCE = 170.f;
const float ATTACK_SPEED = 10.f;
const float MUSIC_MUTE_DISTANCE = 600.f;
const float MUSIC_FADEUP_DISTANCE = 500.f;

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

	mActivate = false;
	mAttack = false;
	mMusic = false;
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
	if(message == "Deactivate")
	{
		mActivate = false;
	}


}

void JaktSpindel::updateEntity(sf::Time dt)
{
	//check length from zid to jaktSpindel
	sf::Vector2f direction = getPosition() - mZid->getPosition();
	float length = direction.getLength();

	//music
	if(length >= MUSIC_MUTE_DISTANCE && mMusic == true)
	{
		MusicManager::fadeDown("fiol");
		mMusic = false;
	}

	if(length <= MUSIC_FADEUP_DISTANCE && mMusic == false)
	{
		MusicManager::fadeUp("fiol");
		mMusic = true;
	}


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

		//Is Jaktspindel close enough for attack?
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