#include "BrokenJar.h"


BrokenJar::BrokenJar(sf::Vector2f position)
	: brokenjar(Loading::getTexture("Room 1/burk_kross_spritesheet.png"), 662, 204, 1, 6, 10)
{
	brokenjar.mLoopOnce = true;
	mActivate = false;
	mSprite.setOrigin(662/2, 204/2);
}

void BrokenJar::sendMessage(Entity* entity, std::string message)
{
	if(message == "Activate")
	{
		mActivate = true;
	}
}


void BrokenJar::updateEntity(sf::Time dt)
{
	if(mActivate == true)
	{
		if(brokenjar.mLoopOnce == true)
		{
			brokenjar.oneLoop();
		}

		mSprite = brokenjar.getCurrentSprite();
	}
}

void BrokenJar::drawEntity(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(mSprite, states);
}

