#include "Player.h"


Player::Player(float positionX, float positionY)
{
	moveSpeed = 4;
<<<<<<< HEAD
	mRectangle.height = 64;
	mRectangle.width = 64;
	mPosition.x = positionX;
	mPosition.y = positionY;
	mAliveStatus = true;
	mID = "player";
	mTexture = Loading::getLoading().getplayer();
	mSprite.setTexture(mTexture);
	mSprite.setOrigin(32, 32);
=======
	rectangle.height = 64;
	rectangle.width = 64;
	position.x = positionX;
	position.y = positionY;
	aliveStatus = true;
	ID = "player";
	
	sprite.setTexture(Loading::getLoading().GetTexture(Textures::Zid));
	sprite.setOrigin(32, 32);
>>>>>>> 97ffd0a5d4a67d2695be9e338ba428acf86c2ca4
	
	
}


Player::~Player()
{
}


void Player::updateEntity()
{

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		mPosition.x -= moveSpeed;
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		mPosition.y -= moveSpeed;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		mPosition.x += moveSpeed;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		mPosition.y += moveSpeed;
	}

	playerListener.setPosition(mPosition.x, mPosition.y, 1);
	mSprite.setPosition(mPosition);
}

void Player::drawEntity(sf::RenderWindow *window)
{
	window->draw(mSprite);
}
