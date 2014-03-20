#include "FadeSprite.h"
#include <iostream>


FadeSprite::FadeSprite(string textureID ,sf::Vector2f position) 
: mSprite(Loading::getTexture(textureID))
, mActivate(false)
, mAlpha(0)
{
	// Sätter origin för spriten till mitten
	sf::FloatRect bounds = mSprite.getLocalBounds();
	mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

	setPosition(position);
}

void FadeSprite::updateEntity(sf::Time dt) 
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		sendMessage(this, "Deactivate");
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		sendMessage(this, "Activate");

	mAlphaTween.update(dt);

	sf::Color color(255,255,255,uint8(mAlpha));
	mSprite.setColor(color);
		
}
		
void FadeSprite::drawEntity(sf::RenderTarget& target, sf::RenderStates states) const
{	
	if(mActivate == true)
	{
		states.transform *= getTransform();
		target.draw(mSprite, states);
	}
}

void FadeSprite::sendMessage(Entity* entity, std::string message)
{
	if(message == "Activate")
	{
		mActivate = true;

		float targetAlpha = 255;
		mAlphaTween.clearTweens();		
		mAlphaTween.addTween(&CDBTweener::TWEQ_CUBIC, CDBTweener::TWEA_OUT, 2.0f, &mAlpha, targetAlpha);
	}
	if(message == "Deactivate")
	{
		float targetAlpha = 0;
		mAlphaTween.clearTweens();		
		mAlphaTween.addTween(&CDBTweener::TWEQ_CUBIC, CDBTweener::TWEA_OUT, 2.0f, &mAlpha, targetAlpha);
	}

}
