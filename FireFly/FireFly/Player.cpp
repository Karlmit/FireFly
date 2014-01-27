#include "Player.h"


Player::Player(float positionX, float positionY)
{
	rectangle.height = 64;
	rectangle.width = 64;
	position.x = positionX;
	position.y = positionY;
	aliveStatus = true;
	ID = "player";
	sprite.setColor(sf::Color::Yellow);
	sprite.setTexture();
}


Player::~Player()
{
}


void Player::updateEntity()
{
	sprite.setPosition(position);
}

void Player::drawEntity(sf::RenderWindow *window)
{
	window->draw(sprite);
}
