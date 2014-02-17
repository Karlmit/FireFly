#pragma once
#include "Entity.h"
#include "Animation.h"
#include "EntityList.h"

#include <SFML\Graphics\Sprite.hpp>
#include <SFML\Graphics\RectangleShape.hpp>

class Mal : public Entity
{
public:
	Mal(sf::Vector2f position);
	~Mal();

private:
	virtual void start();
	virtual void updateEntity(sf::Time dt);
	virtual void drawEntity(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void sendMessage(Entity* sender, string message);

private:
	virtual void BeginContact(b2Contact *contact, Entity* other); 
	virtual void EndContact(b2Contact *contact, Entity* other); 
	
	void movement();
	Rigidbody mRigidbody;
	Animation  idleAnimation;
	Entity* mZid;
	b2Vec2 mZidPosition;
	sf::Sprite mSprite;
	bool mDirLeft;

	bool mEatingCoat;
	sf::Vector2f mCoatPositon;
	bool mFinishedEatingCoat;
};

