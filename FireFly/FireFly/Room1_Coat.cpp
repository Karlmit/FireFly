#include "Room1_Coat.h"

const float EATING_SPEED = 0.5f;

Room1_Coat::Room1_Coat(sf::Vector2f position)
	: mSprites()
	, mCurrentSprite(0)
	, mEating(false)
{
	mSprites.push_back(sf::Sprite(Loading::getTexture("Room 1/Coat 1.png")));
	mSprites.push_back(sf::Sprite(Loading::getTexture("Room 1/Coat 2.png")));
	mSprites.push_back(sf::Sprite(Loading::getTexture("Room 1/Coat 3.png")));
	mSprites.push_back(sf::Sprite(Loading::getTexture("Room 1/Coat 4.png")));
	mSprites.push_back(sf::Sprite(Loading::getTexture("Room 1/Coat 5.png")));
}

void Room1_Coat::eat()
{
	mEating = true;
}

void Room1_Coat::updateEntity(sf::Time dt)
{
	if (mEating)
	{

	}
}

void Room1_Coat::drawEntity(sf::RenderTarget& target, sf::RenderStates states) const
{

}