#pragma once
#include "Entity.h"
#include "Animation.h"
#include "EntityList.h"

#include <SFML\Graphics\Sprite.hpp>

class SuCam : public Entity
{
public:
	SuCam(sf::FloatRect rect);
	~SuCam();
private:
	virtual void start();
	virtual void updateEntity(sf::Time dt);
	virtual void drawEntity(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void BeginContact(b2Contact *contact, Entity* other);
	virtual void blink();

	Animation blinkAnimation;
	Animation shutAnimation;
	Animation openAnimation;
	Rigidbody mRigidbody;
	Entity* mZid;
	b2Vec2 mZidPosition;
//	sf::Vector2f mPosition;
	sf::Sprite mSprite;
	sf::FloatRect mRect;
	unsigned int blinkFrame;
	bool zidSensed;
};

