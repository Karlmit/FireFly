#pragma once

#include "Entity.h"

class Room1_Coat : public Entity
{
public:
	Room1_Coat(sf::Vector2f position);
	virtual void sendMessage(Entity* sender, string message);
	
private:
	virtual void	updateEntity(sf::Time dt);	
	virtual void	drawEntity(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	vector<sf::Sprite> mSprites;
	float mEatProgress;
	bool mEating;
	int mCurrentSprite;
};