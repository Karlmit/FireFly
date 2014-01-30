#include "EntityList.h"

EntityList EntityList::eL;

EntityList::EntityList()
{
}

EntityList::~EntityList()
{
}

EntityList &EntityList::getEntityList()
{
	return eL;
}

void EntityList::addEntity(Entity *entity)
{
	listedEntities.push_back(entity);
}

void EntityList::updateList()
{
	for(entityList::iterator i = listedEntities.begin(); i != listedEntities.end(); i++)
	{
		if((*i)->getAliveStatus() == true)  // if entity is alive it will be added to tempEntities
		{
			tempEntities.push_back((*i));
		}
		else
		{
			delete (*i);  //decreases chance of memory leaks.
		}
	}
	listedEntities.clear();		
	listedEntities = tempEntities;
	tempEntities.clear();
}

void EntityList::emptyList()
{
	for(entityList::iterator i = listedEntities.begin(); i != listedEntities.end(); i++)
	{
		delete (*i);
	}
}
