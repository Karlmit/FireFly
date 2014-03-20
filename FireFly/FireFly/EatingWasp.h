#pragma once
#include "Entity.h"
#include "Animation.h"

class EatingWasp : public Entity
{
public:
	EatingWasp(std::string image, sf::Vector2f position);
	~EatingWasp();

	virtual void updateEntity(sf::Time dt);	
	virtual void drawEntity(sf::RenderTarget& target, sf::RenderStates states) const;
private:
	sf::Sprite mSprite;
	Animation mAnimation;
};

