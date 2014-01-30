#include "Mal.h"

Mal::Mal(void)
{
<<<<<<< HEAD
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
=======
	rectangle.height = 64;
	rectangle.width = 64;
	position.x = 400;
	position.y = 300;
	aliveStatus = true;
	ID = "mal";
	
	sprite.setTexture(Loading::getLoading().GetTexture(Textures::Moth));
	sprite.setOrigin(32, 32);
	
	sound.setBuffer(Loading::getLoading().GetSound(SoundEffects::Moth));
	sound.setLoop(true);
	sound.setPosition(400, 300, 1);
	sound.play(); //if sound should loop, play(); is in the constructor.
>>>>>>> 97ffd0a5d4a67d2695be9e338ba428acf86c2ca4
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

