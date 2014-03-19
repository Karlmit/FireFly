#include "EatingWasp.h"


EatingWasp::EatingWasp(std::string image, sf::Vector2f position)
	: mAnimation(Loading::getTexture(image), 128, 128, 6, 5, 60)
{
	setPosition(position);
}


EatingWasp::~EatingWasp(void)
{
}

void EatingWasp::updateEntity(sf::Time dt)
{
	mAnimation.updateAnimation();
	mSprite = mAnimation.getCurrentSprite();
	mSprite.setOrigin(0, mSprite.getLocalBounds().height);
}

void EatingWasp::drawEntity(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(mSprite, states);
}