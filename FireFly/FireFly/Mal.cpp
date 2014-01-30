#include "Mal.h"

Mal::Mal(void)
{
	mRectangle.height = 64;
	mRectangle.width = 64;
	mPosition.x = 400;
	mPosition.y = 300;
	mAliveStatus = true;
	mID = "mal";
	mTexture = Loading::getLoading().getMothTexture();
	mSprite.setTexture(mTexture);
	mSprite.setOrigin(32, 32);
	mBuffer = Loading::getLoading().getFlySound();
	mSound.setBuffer(mBuffer);
	mSound.setLoop(true);
	mSound.setPosition(400, 300, 1);
	mSound.play(); //if sound should loop, play(); is in the constructor.
}


Mal::~Mal(void)
{
}

void Mal::updateEntity()
{
	mSprite.setPosition(mPosition);
}

void  Mal::drawEntity(sf::RenderWindow *window)
{
	window->draw(mSprite);
}

