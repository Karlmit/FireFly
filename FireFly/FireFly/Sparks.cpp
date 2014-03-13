#include "Sparks.h"


Sparks::Sparks(std::string texture, unsigned int width, unsigned int height, sf::Vector2f position, unsigned int numberOfColumns)
	: spark(Loading::getTexture(texture), width, height, 1, numberOfColumns, 100) 
{
	setPosition(position);
}


void Sparks::updateEntity(sf::Time dt)
{
	spark.updateAnimation();
	mSprite = spark.getCurrentSprite();
}

void Sparks::drawEntity(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(mSprite, states);
}
