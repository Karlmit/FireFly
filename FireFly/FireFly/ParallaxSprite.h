#pragma once

#include "Entity.h"

class ParallaxSprite : public Entity 
{
public:
	ParallaxSprite(string textureID ,sf::Vector2f position = sf::Vector2f());

private:
	virtual void updateEntity(sf::Time dt);	
	virtual void drawEntity(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	sf::Sprite mSprite;
	float mSpeedFactor;
	sf::Vector2f mPos;
};