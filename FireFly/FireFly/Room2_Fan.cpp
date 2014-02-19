#include "Room2_Fan.h"

const float SPEED = 2.f;

Room2_Fan::Room2_Fan(string texture, sf::Vector2f position)
	: mSprite(Loading::getTexture(texture))
	, mIsOn(true)
	, mScale(1)
{
	// Sätter origin för spriten till mitten
	sf::FloatRect bounds = mSprite.getLocalBounds();
	mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

	setPosition(position);
	mID = "Room2_Fan";
}


void Room2_Fan::updateEntity(sf::Time dt)
{
	if (!mIsOn)
		return;

	static bool dir = true;
	
	if (dir)
	{
		mScale += SPEED * dt.asSeconds();

		if (mScale >= 1)
		{
			dir = false;			
			mScale = 1;
		}		
	}
	else
	{
		mScale -= SPEED * dt.asSeconds();

		if (mScale <= 0)
		{
			dir = true;
			mScale = 0;
		}		
	}

	mSprite.setScale(mScale, 1);	
}

void Room2_Fan::sendMessage(Entity* sender ,string message)
{
	if (message == "TurnOff")
		mIsOn = false;
	else if (message == "TurnOn")
		mIsOn = true;
}

void Room2_Fan::drawEntity(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
		
	target.draw(mSprite, states);
}