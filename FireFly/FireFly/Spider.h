#pragma once
#include "Entity.h"
#include "Animation.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RectangleShape.hpp>


class Spider : public Entity
{
public:
	Spider(sf::Vector2f position);
	~Spider(void);
	
private:
	Animation idleAnimation;
	sf::Sprite mSprite;
	Rigidbody mRigidbody;
	bool direction;
	void movement();
	virtual void updateEntity(sf::Time dt);	
	virtual void drawEntity(sf::RenderTarget& target, sf::RenderStates states) const;
};

