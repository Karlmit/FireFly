#pragma once
#include "EntityList.h"
#include "Log.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>



class Hivemind : public Entity
{
public:
	Hivemind(sf::FloatRect rect,
			 const std::string texture);

	Hivemind(const Hivemind& hivemind);

	void start();

	sf::Sprite hivemindProjection;
	void spawn();
	void despawn();
	void BeginContact(b2Contact *contact, Entity* other);
	void EndContact(b2Contact *contact, Entity* other);

private:
	virtual void drawEntity(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void updateEntity(sf::Time dt);
	Rigidbody mRigidbody;
	unsigned int scale;
	bool scaledUp;
	bool scaledDown;
	bool badScaling;
	bool fadeTime;

	Entity* mZid;

	sf::Sprite mSprite;
	sf::Texture texture;
	unsigned int opacity;
	unsigned int mScaleSpeed;
};