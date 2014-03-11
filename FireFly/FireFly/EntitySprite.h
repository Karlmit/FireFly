#pragma once

#include "Entity.h"

class EntitySprite : public Entity 
{
public:
	EntitySprite(string textureID);
	EntitySprite(string textureID ,sf::Vector2f position);
	virtual void sendMessage(Entity* entity, std::string message);

private:
	virtual void updateEntity(sf::Time dt);	
	virtual void drawEntity(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	sf::Sprite mSprite;
	bool mActivate;
};