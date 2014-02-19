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

private:
	//Animation mFanAnimation; // Replace sprite with this when anim
	sf::Sprite mSprite;	// Temp spriteaaaaaaaaaaaa-aaAAaa

	bool mIsOn;
	float mScale;
};