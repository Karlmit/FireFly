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
	virtual void sendMessage(Entity* sender, string message);

	virtual void BeginContact(b2Contact *contact, Entity* other); 
	virtual void EndContact(b2Contact *contact, Entity* other); 

private:
	bool mActivated;
	Rigidbody mRigidbody;
	set<b2Body*> mBodiesInTheZone;
	b2Vec2 mForce;
	b2Vec2 mb2Position;
	float xRatioFromSource;
	float yRatioFromSource;
	float mb2Width;
	float mb2Height;

};
