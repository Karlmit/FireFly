#pragma once

#include "Entity.h"
#include "Animation.h"

class Room2_Fan : public Entity
{
public:
	Room2_Fan(string texture, sf::Vector2f position);

	virtual void updateEntity(sf::Time dt);	
	virtual void drawEntity(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void sendMessage(Entity* sender, string message);
	virtual void start();

private:
	Animation mFanAnimation; // Fläkt animation
	sf::Sprite mSprite;	// Fläkten avstängd sprite
	bool mIsOn;
	Entity* mTermometer;
};