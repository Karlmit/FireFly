#pragma once
#include "Entity.h"
#include "Animation.h"
#include "EntityList.h"

#include <SFML\Graphics\Sprite.hpp>


class Wasp : public Entity
{
public:
	Wasp(sf::Vector2f position);
	~Wasp(void);

private:
	Rigidbody mRigidbody;
	Animation idleAnimation;
	Entity* mZid;
	b2Vec2 mZidPosition;
	sf::Sprite mSprite;
};

