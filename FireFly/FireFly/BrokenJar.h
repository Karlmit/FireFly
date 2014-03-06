#pragma once

#include "Entity.h"
#include "Animation.h"

class BrokenJar : public Entity
{
public:
	BrokenJar(sf::Vector2f position);
	virtual void sendMessage(Entity* entity, std::string message);

private:
	virtual void	updateEntity(sf::Time dt);	
	virtual void	drawEntity(sf::RenderTarget& target, sf::RenderStates states) const;
	Animation brokenjar;
	sf::Sprite mSprite;
	bool mActivate;

};