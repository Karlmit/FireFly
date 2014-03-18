#pragma once

#include "Entity.h"
#include "EntityList.h"

class FallingSprite : public Entity 
{
public:
	FallingSprite(string fallingTextureID, string endTextureID, sf::Vector2f startPosition, sf::Vector2f endPosition, std::string id, float scale = 1.f);
	virtual void sendMessage(Entity* entity, std::string message);

private:
	virtual void updateEntity(sf::Time dt);	
	virtual void drawEntity(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	sf::Sprite mSprite;
	sf::Sprite mEndSprite;
	bool mActivate;
	Rigidbody mRigidbody;
	sf::Vector2f mEndPosition;
	bool mFallingComplete;
	float mSpriteHeight;
};