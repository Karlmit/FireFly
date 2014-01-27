#pragma once
#include "EntityList.h"
class Level
{
public:
	Level(void);
	~Level(void);
	void level0(sf::RenderWindow *window);
private:
	void draw(sf::RenderWindow *window);
	void update();

};

