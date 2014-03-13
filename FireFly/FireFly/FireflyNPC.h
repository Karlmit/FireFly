#pragma once
#include "Entity.h"
#include "Animation.h"
#include "EntityList.h"
// #include "FireflyZone.h"

#include <SFML\Graphics\Sprite.hpp>
#include <SFML\Graphics\RectangleShape.hpp>
#include <Camera.h>

class FireflyNPC : public Entity
{
public:
	FireflyNPC(sf::Vector2f position);
	~FireflyNPC(void);

	bool imitateZid;
private:
	virtual void start();
	virtual void updateEntity(sf::Time dt);
	virtual void drawEntity(sf::RenderTarget& target, sf::RenderStates states) const;
	void movement();

	Rigidbody mRigidbody;
	Animation idleAnimation;
	Animation dashAnimation;
	Entity* mZid;
	b2Vec2 mZidPosition;
	sf::Sprite mSprite;
	bool mDirLeft;
};