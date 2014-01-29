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

void Level::startLevel0()
{
	Loading::getLoading().loadLevel0();
	Player *player = new Player(100, 100);
	EntityList::getEntityList().addEntity(player);
	Mal *mal = new Mal();
	EntityList::getEntityList().addEntity(mal);
}

