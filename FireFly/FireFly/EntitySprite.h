#pragma once

#include "Entity.h"

#include <SFML\Graphics\Sprite.hpp>

class EntitySprite : public Entity 
{
public:
	EntitySprite(TexturesID textureID);
	EntitySprite(TexturesID textureID ,sf::Vector2f position);

private:
	virtual void	updateEntity(sf::Time dt);	
	virtual void	drawEntity(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	sf::Sprite mSprite;
};