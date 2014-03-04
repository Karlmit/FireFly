#pragma once

#include "Entity.h"

class Termometer : public Entity 
{
public:
	Termometer(sf::Vector2f position);

private:
	virtual void updateEntity(sf::Time dt);	
	virtual void drawEntity(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void sendMessage(Entity* sender, string message);

private:
	vector<sf::Sprite> mTermoSprites;
	int mCurrentSprite;
	bool mBoilerOn;
	bool mCeilingFanOff;
	bool mComputerOn;

};