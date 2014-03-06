#pragma once
#include "Entity.h"
#include "Animation.h"
#include "EntityList.h"

#include <SFML\Graphics\Sprite.hpp>
#include <SFML\Graphics\RectangleShape.hpp>


class Wasp : public Entity
{
public:
	Wasp(sf::Vector2f position);

private:
	virtual void start();
	virtual void updateEntity(sf::Time dt);
	virtual void drawEntity(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void sendMessage(Entity* sender, string message);

	void movement();
	

private:
	Rigidbody mRigidbody;
	Animation idleAnimation;
	Animation attackAnimation;
	Entity* mZid;
	b2Vec2 mZidPosition;
	sf::Sprite mSprite;
	bool mDirLeft;
	bool bonk;
	unsigned int bonkFrame;

	bool mHunting;
};

