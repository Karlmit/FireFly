#include "Mal.h"

Mal::Mal(void)
{
	/*
	mRectangle.height = 64;
	mRectangle.width = 64;
	mPosition.x = 100;
	mPosition.y = 100;
	mAliveStatus = true;
	mID = "mal";
	
	mSprite.setTexture(Loading::getLoading().GetTexture(Textures::Moth));
	mSprite.setOrigin(32, 32);
	
	mSound.setBuffer(Loading::getLoading().GetSound(SoundEffects::Moth));
	mSound.setLoop(true);
	mSound.setPosition(100, 100, 1);
	mSound.play(); //if sound should loop, play(); is in the constructor.
	*/
}


Mal::~Mal(void)
{
}

void Mal::updateEntity(sf:: Time timePerFrame)
{
	//mSprite.setPosition(mPosition);
}

void  Mal::drawEntity(sf::RenderTarget& target, sf::RenderStates states) const
{
	//window->draw(mSprite);
}

