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
	Animation mFanAnimation; // Fl�kt animation
	sf::Sprite mSprite;	// Fl�kten avst�ngd sprite
	bool mIsOn;
	Entity* mTermometer;
};