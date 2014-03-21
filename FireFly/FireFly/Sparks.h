#pragma once

#include "Entity.h"
#include "Animation.h"
#include "Audio.h"


class Sparks : public Entity
{
public: 
	Sparks(sf::Vector2f position);

private:
	virtual void updateEntity(sf::Time dt);	
	virtual void drawEntity(sf::RenderTarget& target, sf::RenderStates states) const;
	Animation spark;
	sf::Sprite mSprite;
	sf::Clock mSparkClock;
};

