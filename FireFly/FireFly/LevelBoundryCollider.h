#pragma once

#include "Entity.h"

class LevelBoundryCollider : public Entity 
{
public:
	LevelBoundryCollider(sf::FloatRect rect);

private:
	virtual void	updateEntity(sf::Time dt);	
	virtual void	drawEntity(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	Rigidbody mRigidbody;
};