#pragma once
#include "EntityList.h"
class Level
{
public:
	static Level &getLevel();
	void level0(sf::RenderWindow *window);
private:
	Level();
	~Level();
	void draw(sf::RenderWindow *window);
	void update();
	void operator=(const Level &level);
	static Level level;
};

