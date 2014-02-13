#pragma once

#include "Entity.h"

class ToggleSprite : public Entity 
{
public:
	ToggleSprite(string textureIDOn, string textureIDOff, bool isOn ,sf::Vector2f position);

private:
	virtual void updateEntity(sf::Time dt);	
	virtual void drawEntity(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void sendMessage(Entity* sender, string message);

private:
	sf::Sprite mSpriteOn;
	sf::Sprite mSpriteOff;
	bool mOn;
};