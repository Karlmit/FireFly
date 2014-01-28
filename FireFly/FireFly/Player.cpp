#include "Player.h"


Player::Player(float positionX, float positionY)
{
	rectangle.height = 64;
	rectangle.width = 64;
	position.x = positionX;
	position.y = positionY;
	aliveStatus = true;
	ID = "player";
	texture = Loading::getLoading().getplayer();
	sprite.setTexture(texture);
}


Player::~Player()
{
}


void Player::updateEntity()
{
	velocity.x++;
	sprite.setRotation(velocity.x);

	sprite.setPosition(position);
}

void Player::drawEntity(sf::RenderWindow *window)
{
	window->draw(sprite);
}
