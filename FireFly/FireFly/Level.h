#pragma once
#include "EntityList.h"
#include "Player.h"
class Level
{
public:
	static Level &getLevel();
	void loadLevel0();
private:
	Level();
	~Level();
	void operator=(const Level &level);
	static Level level;
};

