#pragma once

#include "Entity.h"
using namespace std;

class StaticLineCollider : public Entity 
{
public:
	StaticLineCollider(vector<sf::Vector2f> points, bool loop = false);

private:
	virtual void	updateEntity(sf::Time dt);	
	virtual void	drawEntity(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	Rigidbody mRigidbody;
};