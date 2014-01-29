#include "GameLoop.h"


GameLoop GameLoop::gameloop;

GameLoop::GameLoop()
{
}


GameLoop::~GameLoop()
{
}

GameLoop &GameLoop::getGameLoop()
{
	return gameloop;
}

void GameLoop::runPrototype(sf::RenderWindow *window)
{
	draw(window);
	update();
}

void GameLoop::draw(sf::RenderWindow *window)
{
	for(EntityList::entityList::iterator i = EntityList::getEntityList().listedEntities.begin(); i != EntityList::getEntityList().listedEntities.end(); i++)
	{
		(*i)->drawEntity(window);
	}
}

void GameLoop::update()
{
	EntityList::getEntityList().updateList(); //deletes dead entities
	for(EntityList::entityList::iterator i = EntityList::getEntityList().listedEntities.begin(); i != EntityList::getEntityList().listedEntities.end(); i++)
	{
		(*i)->updateEntity();

	}
}
