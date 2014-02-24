#include "Myra.h"
#include "Utility.h"
#include <iostream>

const float SPEED = 100.f;

Myra::Myra(float pos, vector<sf::Vector2f> path, vector<float> lengths, vector<sf::Vector2f> directions, float totalLength)
	: mSprite(Loading::getTexture("Ernst.png"))
	, mPath(path)
	, mLengths(lengths)
	, mDirections(directions)
	, mTotalLength(totalLength)
	, mIdleMoveForward(true)
	, mIdleMoveTimer()
	, mIdle(true)
	, mTweenRotation()
	, mRotation(0)
	, mTargetRotation(0)
{
	// Sätter origin för spriten till mitten
	sf::FloatRect bounds = mSprite.getLocalBounds();
	mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);


	setPosition(pos);
}





void Myra::updateEntity(sf::Time dt)
{
	
	//CDBTweener oTweener;
	//oTweener.addTween(&CDBTweener::TWEQ_CUBIC, CDBTweener::TWEA_INOUT, 2.0f, &fPos, 10.0f);
	//oTweener.removeTween
	//(*oTweener.getTweens().begin())->getDurationSec()

	if (mIdle)
	{

		if (mIdleMoveTimer.getElapsedTime().asSeconds() < mTimeForIdle)
		{
			if (mIdleMoveForward )
				setPosition(mPos + dt.asSeconds() * SPEED);

			if (!mIdleMoveForward)
				setPosition(mPos - dt.asSeconds() * SPEED);
		}
		else
		{
			mIdle = false;
			mIdleMoveTimer.restart();
			mTimeForIdle = Util::randFloat(1, 3.f);
		}
	}
	else
	{
		if (mIdleMoveTimer.getElapsedTime().asSeconds() > mTimeForIdle)
		{
			mIdle = true;
			mIdleMoveTimer.restart();
			mIdleMoveForward = Util::randBool();
			mTimeForIdle = Util::randFloat(1, 2.f);
		}
	}

	float satan =  std::atan2f(mCurrentDirection.y, mCurrentDirection.x);
	//cout << satan << endl;
	float newRotation = satan * 180/3.14f;
	//mSprite.setRotation(satan * 180/3.14f);

	if (abs(mTargetRotation - newRotation) > 0.1f)
	{
		mTweenRotation.clearTweens();
		mTweenRotation.addTween(&CDBTweener::TWEQ_CUBIC, CDBTweener::TWEA_OUT, 1.0f, &mRotation, newRotation);		
		mTargetRotation = newRotation;
	}

	mTweenRotation.update(dt);

	
	if (mIdleMoveForward)
		mSprite.setScale(1, 1);
	else
		mSprite.setScale(-1, 1);

		


}

void Myra::drawEntity(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(mSprite, states);
}

void Myra::setPosition(float x)
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
		//if (mIdleMoveForward)
			mCurrentDirection = mDirections[StageIndex];
		//else 
			//mCurrentDirection = -mDirections[StageIndex];
	}

	Entity::setPosition(Position);
}