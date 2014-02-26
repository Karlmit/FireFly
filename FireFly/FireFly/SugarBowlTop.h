#pragma once
#include "Entity.h"


class SugarBowlTop : public Entity
{
public:
	SugarBowlTop(string texture, sf::Vector2f position, bool dynamic = true);
	~SugarBowlTop();

private:
	virtual void updateEntity(sf::Time dt);	
	virtual void drawEntity(sf::RenderTarget& target, sf::RenderStates states) const;
	
	Rigidbody mRigidbody;
	sf::Sprite mSprite;
	sf::Vector2f mStartPosition;
	
};

