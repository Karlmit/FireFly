#include "Player.h"


Player::Player(float positionX, float positionY)
{
	moveSpeed = 4;
	rectangle.height = 64;
	rectangle.width = 64;
	position.x = positionX;
	position.y = positionY;
	velocity.x = 1;
	velocity.y = 1;
	aliveStatus = true;
	ID = "player";
	texture = Loading::getLoading().getplayer();
	sprite.setTexture(texture);
	sprite.setOrigin(32, 32);
}


Player::~Player()
{
}


void Player::updateEntity()
{
	//velocity.x++;
	//sprite.setRotation(velocity.x);

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
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		//velocity.y-= 0.1;
		velocity.x-= 0.1;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
		//velocity.y+= 0.1;
		velocity.x+= 0.1;
	}

	sprite.setScale(velocity.x, velocity.y);
	sprite.setPosition(position);
}

void Player::drawEntity(sf::RenderWindow *window)
{
	window->draw(sprite);
}
