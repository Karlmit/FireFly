#pragma once

#include "Entity.h"

class Jar : public Entity 
{
public:
	Jar(string texture, sf::Vector2f position);

private:
	virtual void	updateEntity(sf::Time dt);	
	virtual void	drawEntity(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	Rigidbody mRigidbody;
	sf::Sprite mSprite;
};