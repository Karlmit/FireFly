#pragma once
#include "Entity.h"

class lever : public Entity
{
public:
	lever(sf::Vector2f position, std::string imageSRC);
	~lever();
	virtual void updateEntity(sf::Time dt);	
	virtual void drawEntity(sf::RenderTarget& target, sf::RenderStates states) const;
private:
	sf::Sprite mSprite;
	Rigidbody firstBody;
	Rigidbody secondBody;
	void createLever(sf::Vector2f position, sf::FloatRect rect);
};

