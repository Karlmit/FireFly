#pragma once

#include "Entity.h"

class ForceZone : public Entity
{
public:
	ForceZone(sf::FloatRect rect);

private:
	virtual void start();
	virtual void updateEntity(sf::Time dt);	
	virtual void drawEntity(sf::RenderTarget& target, sf::RenderStates states) const;

	virtual void BeginContact(b2Contact *contact, Entity* other); 
	virtual void EndContact(b2Contact *contact, Entity* other); 

private:
	Rigidbody mRigidbody;
	set<b2Body*> mBodiesInTheZone;
	b2Vec2 mForce;
};