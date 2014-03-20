#pragma once

#include "Entity.h"
#include "Tween.h"

class FadeSprite : public Entity 
{
public:
	FadeSprite(string textureID ,sf::Vector2f position);
	virtual void sendMessage(Entity* entity, std::string message);

private:
	virtual void updateEntity(sf::Time dt);	
	virtual void drawEntity(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	sf::Sprite mSprite;
	bool mActivate;

	Tween mAlphaTween;
	float mAlpha;
};