#include "FadeToBlack.h"
#include <iostream>

#include "Level.h"

FadeToBlack::FadeToBlack(float delay, bool fadeTo, string nextMap)
	: mDelay(delay)
	, mFadeTo(fadeTo)
	, mRectShape(Level::getLevelSize())
	, mColor()
	, mNextMap(nextMap)
{
	mID = "fade";
	mColor = sf::Color::Black;
	if (fadeTo)
		mColor.a = 0;
	else
		mColor.a = 255;

	mRectShape.setFillColor(mColor);

	mTimer.restart();
}

void FadeToBlack::sendMessage(Entity* entity, std::string message)
{
	if(message == "activate")
	{
		mFadeTo = true;
	}

}


void FadeToBlack::updateEntity(sf::Time dt) 
{
	if (mFadeTo)
	{
		// Fade to black and change level
		if (mTimer.getElapsedTime().asSeconds() < mDelay)
		{
			float percent = mTimer.getElapsedTime().asSeconds() / mDelay;
			mColor.a = sf::Uint8(min(int(255 * percent), 255));
			mRectShape.setFillColor(mColor);
		}
		else
		{
			mRectShape.setFillColor(sf::Color::Black);
			Level::changeMap(mNextMap);
		}
	}
	else
	{
		// Fade from black
		if (mTimer.getElapsedTime().asSeconds() < mDelay)
		{
			float percent = 1.f - (mTimer.getElapsedTime().asSeconds() / mDelay);
			mColor.a = sf::Uint8(max(int(255 * percent), 0));
			mRectShape.setFillColor(mColor);
		}
		else
		{
			mRectShape.setFillColor(sf::Color::Transparent);
			killEntity();
		}
	}
}
		
void FadeToBlack::drawEntity(sf::RenderTarget& target, sf::RenderStates states) const
{	
	states.transform *= getTransform();
	target.draw(mRectShape, states);
}

void FadeToBlack::activate(bool activate)
{
	mFadeTo = activate;
}

void FadeToBlack::setNextLevel(std::string level)
{
	mNextMap = level;
}

