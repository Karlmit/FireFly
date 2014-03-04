#pragma once
#include <list>
#include "Entity.h"

enum class Layer 
{
	Background,
	Back,
	NPC,
	Front,
	Foreground,
	Collision,
	Light,
	Misc,
};

class EntityList
{
public:
	static EntityList& getEntityList(); //singleton
	typedef std::list <Entity*> entityList;

	void update(sf::Time dt);	// Updates all entities
	void draw(sf::RenderWindow& window);	// Draws all entities
	void drawBackground(sf::RenderWindow& window);
	void drawBack(sf::RenderWindow& window);
	void drawNPC(sf::RenderWindow& window);
	void drawFront(sf::RenderWindow& window);
	void drawForeground(sf::RenderWindow& window);
	
	void addEntity(Entity *entity, Layer layer = Layer::Front, bool runStart = true);	//adds new entities
	void updateList();	//deletes "dead" entities
	void emptyList();
	void startList(); // Runs once after levelload
	Entity* getEntity(std::string id);
	std::vector<Entity*> getEntities(std::string id);

private:
	EntityList();
	~EntityList();
	void operator=(const EntityList &eL);	//singleton
	static EntityList eL;	//singleton
	typedef std::list <Entity*> tempList; //stores "alive" entities
	tempList tempEntities;	//used for deleting killed entities

	entityList listedEntities;

	entityList BackgroundLayerList;
	entityList BackLayerList;
	entityList NPCLayerList;
	entityList FrontLayerList;
	entityList ForegroundLayerList;

};

