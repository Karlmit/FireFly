#include "SCHAKT2_FAN.h"


SCHAKT2_FAN::SCHAKT2_FAN(sf::Vector2f position)
	: mAnimation(Loading::getTexture("Schakt/schakt_fan_spritesheet.png"), 226, 17, 1, 4, 40)
{
	setPosition(position);
}


SCHAKT2_FAN::~SCHAKT2_FAN()
{
}

void SCHAKT2_FAN::updateEntity(sf::Time dt)
{
	mAnimation.updateAnimation();
	mSprite = mAnimation.getCurrentSprite();
	mSprite.setOrigin(0, mSprite.getLocalBounds().height);
}

void SCHAKT2_FAN::drawEntity(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(mSprite, states);
}
