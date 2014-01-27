#pragma once
#include <list>
#include "Entity.h"

class EntityList
{
public:
	static EntityList &getEntityList(); //singleton
	typedef std::list <Entity*> entityList;
	entityList listedEntities;
	void addEntity(Entity *entity);	//adds new entities
	void updateList();	//deletes "dead" enetities

private:
	EntityList();
	~EntityList();
	void operator=(const EntityList &eL);	//singleton
	static EntityList eL;	//singleton
	typedef std::list <Entity*> tempList; //stores "alive" entities
	tempList tempEntities;	//used for deleting killed entities

};

