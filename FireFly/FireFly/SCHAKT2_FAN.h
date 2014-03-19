#pragma once
#include "Entity.h"
#include "Animation.h"

class SCHAKT2_FAN : public Entity
{
public:
	SCHAKT2_FAN(sf::Vector2f position);
	~SCHAKT2_FAN();

	virtual void updateEntity(sf::Time dt);	
	virtual void drawEntity(sf::RenderTarget& target, sf::RenderStates states) const;
private:
	sf::Sprite mSprite;
	Animation mAnimation;

};

