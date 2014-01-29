#pragma once
#include "Entity.h"
class Mal : public Entity
{
public:
	Mal();
	~Mal();
	void updateEntity();
	void drawEntity(sf::RenderWindow *window);
private:
};

