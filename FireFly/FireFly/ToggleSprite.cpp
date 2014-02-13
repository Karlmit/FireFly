#include "ToggleSprite.h"

ToggleSprite::ToggleSprite(string textureIDOn, string textureIDOff, bool isOn ,sf::Vector2f position)
	: mSpriteOn(Loading::getTexture(textureIDOn))
	, mSpriteOff(Loading::getTexture(textureIDOff))
	, mOn(isOn)
{
	// Sätter origin för spriten till mitten
	sf::FloatRect bounds = mSpriteOn.getLocalBounds();
	mSpriteOn.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

	bounds = mSpriteOff.getLocalBounds();
	mSpriteOff.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

	setPosition(position);
}

void ToggleSprite::updateEntity(sf::Time dt)
{

}

void ToggleSprite::sendMessage(Entity* sender ,string message)
{
	if (message == "Toggle")
		mOn = !mOn;
	else if (message == "ToggleOn")
		mOn = true;
	else if (message == "ToggleOff")
		mOn = false;
}

void ToggleSprite::drawEntity(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	if (mOn)	
		target.draw(mSpriteOn, states);
	else
		target.draw(mSpriteOff, states);
}