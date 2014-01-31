#pragma once

#include "Entity.h"

class StaticCollider : public Entity 
{
public:
	StaticCollider(sf::Vector2f position);

private:
	virtual void	updateEntity(sf::Time dt);	
	virtual void	drawEntity(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	Rigidbody mRigidbody;
};