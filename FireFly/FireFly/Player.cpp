#include "Player.h"


Player::Player(float positionX, float positionY)
{
	moveSpeed = 4;
	rectangle.height = 64;
	rectangle.width = 64;
	position.x = positionX;
	position.y = positionY;
	aliveStatus = true;
	ID = "player";
	
	sprite.setTexture(Loading::getLoading().GetTexture(Textures::Zid));
	sprite.setOrigin(32, 32);
	
	
}


Player::~Player()
{
}


void Player::updateEntity()
{

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		position.x -= moveSpeed;
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		position.y -= moveSpeed;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		position.x += moveSpeed;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		position.y += moveSpeed;
	}

	playerListener.setPosition(position.x, position.y, 1);
	sprite.setPosition(position);
}

void Player::drawEntity(sf::RenderWindow *window)
{
	window->draw(sprite);
}
