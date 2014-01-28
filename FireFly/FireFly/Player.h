#pragma once
#include "Entity.h"

class Player : public Entity
{
public:
	Player(float positionX, float positionY);
	~Player();
	void updateEntity();
	void drawEntity(sf::RenderWindow *window);

private:
	float moveSpeed;
};

