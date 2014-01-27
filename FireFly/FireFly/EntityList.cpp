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