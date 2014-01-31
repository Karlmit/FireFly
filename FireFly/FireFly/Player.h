#pragma once
#include "Entity.h"
#include <SFML/Audio.hpp>

class Player : public Entity
{
public:
	Player(float positionX, float positionY);
	~Player();

	void updateEntity(sf::Time dt);
	void drawEntity(sf::RenderTarget& target, sf::RenderStates states) const;
private:
	sf::Listener playerListener;
};

