#pragma once

#include "Entity.h"

class Boiler : public Entity
{
public:
	Boiler(string textureID ,sf::Vector2f position);

private:
	virtual void updateEntity(sf::Time dt);	
	virtual void drawEntity(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void sendMessage(Entity* sender, string message);

private:
	sf::Sprite mSprite;
	sf::Vector2f mPos;
	bool mActive;
	float mShakiness;
	sf::Clock mDelayTimer;
};