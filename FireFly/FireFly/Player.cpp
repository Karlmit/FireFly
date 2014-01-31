#include "Player.h"
#include <SFML\Window\Keyboard.hpp>

Player::Player(float positionX, float positionY)
{
	/*
	moveSpeed = 4;
	mRectangle.height = 64;
	mRectangle.width = 64;
	mPosition.x = positionX;
	mPosition.y = positionY;
	mAliveStatus = true;
	mID = "player";

	
	mSprite.setTexture(Loading::getLoading().GetTexture(Textures::Zid));
	mSprite.setOrigin(32, 32);
	
	*/
}


Player::~Player()
{
}


void Player::updateEntity(sf::Time dt)
{
	/*
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
	*/
}

void Player::drawEntity(sf::RenderTarget& target, sf::RenderStates states) const
{
	//window->draw(mSprite);
}
