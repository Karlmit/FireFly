#include "Myra.h"
#include "Utility.h"
#include <iostream>
#include "EntityList.h"

const float SPEED = 100.f;
const float SCALE = 0.7f;
const float FOLLOW_DISTANCE_ZID_SQR = 600.f*600.f;
const float MIN_DISTANCE_TO_SWEET_ZID_SQR = 200.f*200.f;
const float MIN_DISTANCE_TO_SUGAR_SQR = 150.f*150.f;
const float TIME_CHECKING_OUT_SUGAR = 12.F;

Myra::Myra(float pos, vector<sf::Vector2f> path, vector<float> lengths, vector<sf::Vector2f> directions, float totalLength)
	: mSprite(Loading::getTexture("Ernst.png"))
	, mPath(path)
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
	, mZidDroppedSugar(false)
	, mZidIsSweet(false)
	, mZid(nullptr)
	, mDroppedSugarZid()
	, mDroppedInBoiler(false)
	, mPos(0)
	, mWalking(Loading::getTexture("Room 2/myra_gang_spritesheet.png"), 128, 58, 1, 8, 80)
	
{
	// Sätter origin för spriten till mitten
	sf::FloatRect bounds = mSprite.getLocalBounds();
	mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

	setPosition(pos);
}

void Myra::start()
{
	mZid = static_cast<Zid*>(EntityList::getEntityList().getEntity("Zid"));
}





void Myra::updateEntity(sf::Time dt)
{
	
	// Check if in boiler then destroy self and send a message to the boiler
	if (mDroppedInBoiler && mPos == mTotalLength)
	{
		EntityList::getEntityList().getEntity("Boiler")->sendMessage(this, "Ants!");
		this->killEntity();
	}

	// If dropped sugar in boiler //
	if (mDroppedInBoiler)
	{
		// Move Right
		setPosition(mPos + SPEED * dt.asSeconds());
		mMoveForward = true;
	}

	
	if (!mDroppedInBoiler)
	{
		// Dropped sugar //

		if (!mZid->isSweet() && mZidIsSweet)
		{
			mZidDroppedSugar = true;
			mDroppedSugarZid.restart();
		}

		if (mZidDroppedSugar && mDroppedSugarZid.getElapsedTime().asSeconds() < TIME_CHECKING_OUT_SUGAR)
		{
			
				

			// Check if dropped in boiler
			if (mZid->getDroppedSugar().y > 3000 && 3600 < mZid->getDroppedSugar().x && mZid->getDroppedSugar().x < 4400)
				mDroppedInBoiler = true;
						

			// Go towards sugar //
			float distanceSqr = (mZid->getDroppedSugar() - this->getPosition()).getLengthSqr();
			if ( distanceSqr > MIN_DISTANCE_TO_SUGAR_SQR && mZid->getDroppedSugar().y > 3000 && mZid->getDroppedSugar().x < 4400)
			{
				const float check_dist_value = 1000.f;
				sf::Vector2f leftPos = calcPosition(mPos - check_dist_value);
				sf::Vector2f rightPos = calcPosition(mPos + check_dist_value);
				float leftDistanceSqr = (mZid->getDroppedSugar() - leftPos).getLengthSqr();
				float rightDistanceSqr = (mZid->getDroppedSugar() - rightPos).getLengthSqr();

				if (leftDistanceSqr < rightDistanceSqr)
				{
					// Move left
					setPosition(mPos - SPEED * dt.asSeconds());
					mMoveForward = false;
				}
				else
				{
					// Move right
					setPosition(mPos + SPEED * dt.asSeconds());
					mMoveForward = true;
			
				}

			}
		
		}
		else
		{
			mZidDroppedSugar = false;
		}



		mZidIsSweet = mZid->isSweet();
		// --------- //




		// Go toward sweet zid //
		float distanceSqr = (mZid->getPosition() - this->getPosition()).getLengthSqr();
		if (mZid->isSweet() && distanceSqr > MIN_DISTANCE_TO_SWEET_ZID_SQR && distanceSqr < FOLLOW_DISTANCE_ZID_SQR)
		{
			const float check_dist_value = 300.f;
			sf::Vector2f leftPos = calcPosition(mPos - check_dist_value);
			sf::Vector2f rightPos = calcPosition(mPos + check_dist_value);
			float leftDistanceSqr = (mZid->getPosition() - leftPos).getLengthSqr();
			float rightDistanceSqr = (mZid->getPosition() - rightPos).getLengthSqr();

			if (leftDistanceSqr < rightDistanceSqr)
			{
				// Move left
				setPosition(mPos - SPEED * dt.asSeconds());
				mMoveForward = false;
			}
			else
			{
				// Move right
				setPosition(mPos + SPEED * dt.asSeconds());
				mMoveForward = true;
			
			}

		}
		// ----- //


		// else idle //
		else if (mIdle)
			idleMovement(dt);
	}
	

	

	// Rotation //
	float satan =  std::atan2f(mCurrentDirection.y, mCurrentDirection.x);
	float newRotation = satan * 180/3.14f;

	if (abs(mTargetRotation - newRotation) > 0.1f)
	{
		mSuperTweenRotation.clearTweens();
		mSuperTweenRotation.addTween(&CDBTweener::TWEQ_CUBIC, CDBTweener::TWEA_OUT, 1.0f, &mRotation, newRotation);		
	}

	mSuperTweenRotation.update(dt);
	mSprite.setRotation(mRotation);
	// --------- //
	
	// Set the scale to turn the sprite left or right
	if (mMoveForward)
		mSprite.setScale(SCALE, SCALE);
	else
		mSprite.setScale(-SCALE, SCALE);

		
}

void Myra::drawEntity(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(mSprite, states);
}

void Myra::idleMovement(sf::Time dt)
{
	if (mIdleMove)
	{

		if (mIdleMoveTimer.getElapsedTime().asSeconds() < mTimeForIdle)
		{
			if (mMoveForward )
				setPosition(mPos + dt.asSeconds() * SPEED);

			if (!mMoveForward)
				setPosition(mPos - dt.asSeconds() * SPEED);
		}
		else
		{
			mIdleMove = false;
			mIdleMoveTimer.restart();
			mTimeForIdle = Util::randFloat(1, 3.f);
		}
	}
	else
	{
		if (mIdleMoveTimer.getElapsedTime().asSeconds() > mTimeForIdle)
		{
			mIdleMove = true;
			mIdleMoveTimer.restart();
			mMoveForward = Util::randBool();
			mTimeForIdle = Util::randFloat(1, 2.f);
		}
	}
}

void Myra::setPosition(float x)
{	
	mWalking.updateAnimation();
	mSprite = mWalking.getCurrentSprite();


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

sf::Vector2f Myra::calcPosition(float x)
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