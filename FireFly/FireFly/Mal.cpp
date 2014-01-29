#include "Mal.h"

Mal::Mal(void)
{
	rectangle.height = 64;
	rectangle.width = 64;
	position.x = 400;
	position.y = 300;
	aliveStatus = true;
	ID = "mal";
	texture = Loading::getLoading().getMothTexture();
	sprite.setTexture(texture);
	sprite.setOrigin(32, 32);
	buffer = Loading::getLoading().getFlySound();
	sound.setBuffer(buffer);
	sound.setLoop(true);
	sound.setPosition(400, 300, 1);
	sound.play(); //if sound should loop, play(); is in the constructor.
}


Mal::~Mal(void)
{
}

void Mal::updateEntity()
{
	sprite.setPosition(position);
}

void  Mal::drawEntity(sf::RenderWindow *window)
{
	window->draw(sprite);
}

