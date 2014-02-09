#pragma once

#include "Entity.h"

class Trigger : public Entity
{
public:
	Trigger(sf::FloatRect rect);

	virtual void updateEntity(sf::Time dt);	
	virtual void drawEntity(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	virtual void BeginContact(b2Contact *contact); 
	virtual void EndContact(b2Contact *contact); 

private:
	Rigidbody mRigidbody;
};