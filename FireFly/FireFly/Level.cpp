#include "Level.h"

Level Level::level;

Level::Level()
{
}


Level::~Level()
{
}

Level &Level::getLevel()
{
	return level;
}

void Level::loadLevel0()
{
	Loading::getLoading().loadplayer();
	Player *player = new Player(100, 100);
	EntityList::getEntityList().addEntity(player);
}

