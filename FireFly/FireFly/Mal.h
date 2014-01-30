#pragma once
#include "Entity.h"
class Mal : public Entity
{
public:
	Mal();
	~Mal();
	void updateEntity(sf:: Time timePerFrame);
	void drawEntity(sf::RenderWindow *window);
private:
};

