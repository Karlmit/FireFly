#include "Level.h"


Level::Level(void)
{
}


Level::~Level(void)
{
}

void Level::level0(sf::RenderWindow *window)
{
	update();
	draw(window);
	
}

void Level::draw(sf::RenderWindow *window)
{
	for(EntityList::entityList::iterator i = EntityList::getEntityList().listedEntities.begin(); i != EntityList::getEntityList().listedEntities.end(); i++)
	{
		(*i)->drawEntity(window);
	}
}

void Level::update()
{
	EntityList::getEntityList().updateList(); //deletes dead entities
	for(EntityList::entityList::iterator i = EntityList::getEntityList().listedEntities.begin(); i != EntityList::getEntityList().listedEntities.end(); i++)
	{
		(*i)->updateEntity();
	}
}