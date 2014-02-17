#pragma once

#include "Entity.h"
#include "MapObjectProperty.h"

class Trigger : public Entity
{
public:
	Trigger(sf::FloatRect rect);

	virtual void updateEntity(sf::Time dt);	
	virtual void drawEntity(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	virtual void BeginContact(b2Contact *contact, Entity* other); 
	virtual void EndContact(b2Contact *contact, Entity* other); 

private:
	Rigidbody mRigidbody; 
};