#include "Level.h"
#include "Loading.h"
#include "Box2dWorld.h"
#include "Camera.h"

#include "Zid.h"
#include "EntitySprite.h"
#include "StaticCollider.h"
#include "LevelBoundryCollider.h"
#include "Jar.h"

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
	// Creates a box2d world
	Box2dWorld::newWorld(b2Vec2(0, -10.f));

	// Load the resources for this level
	Loading::getLoading().loadLevel0();

	// Level boundry
	sf::FloatRect levelBoundry(-2500, -1080, 5000, 2160);

	// Sets level boundry for the camera
	Camera::currentCamera().setBounds(levelBoundry);
	//Camera::currentCamera().setBounds(sf::FloatRect(0, 0, 5000, 2160));

	// Create the entities for this level 
	// Should come from a level file later
	EntityList& eList = EntityList::getEntityList();	

	// Adding some sprites
	eList.addEntity(new EntitySprite(TexturesID::ROOM1_Background), Layer::Background);
	eList.addEntity(new EntitySprite(TexturesID::ROOM1_Foreground), Layer::Foreground);
	eList.addEntity(new EntitySprite(TexturesID::ROOM1_Coat5), Layer::Front);

	// Adding Zid
	eList.addEntity(new Zid(sf::Vector2f(300, 0)), Layer::Front);
	
	// Adds a collider around the entire level
	eList.addEntity(new LevelBoundryCollider(levelBoundry), Layer::Front);

	// Adds a jar
	eList.addEntity(new Jar(TexturesID::ROOM1_JAR, sf::Vector2f(0,0)), Layer::Front);
}

