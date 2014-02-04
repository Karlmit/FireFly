#include "Level.h"
#include "Loading.h"
#include "Box2dWorld.h"
#include "Camera.h"

#include "Zid.h"
#include "EntitySprite.h"
#include "StaticCollider.h"
#include "LevelBoundryCollider.h"
#include "Jar.h"

#include <iostream>

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

void Level::startLevel1()
{
	// Creates a box2d world
	Box2dWorld::newWorld(b2Vec2(0, -10.f));

	// Load the resources for this level
	Loading::getLoading().loadLevel0();
	

	loadMap("Maps/room1.tmx");
}

void Level::loadMap(string filename)
{
	cout << "Loads level \"" << filename << "\"" << endl;

	// Loads all the map data in to the Map class object
	Map map(filename);

	// Gets the entitylist
	EntityList& eList = EntityList::getEntityList();

	// Get the map width and height
	float mapWidth = float(map.getTileWidth());
	float mapHeight = float(map.getTileWidth());	

	// Level boundry
	sf::FloatRect levelBoundry(-mapWidth/2, -mapHeight/2, mapWidth, mapHeight);

	// Sets level boundry for the camera
	Camera::currentCamera().setBounds(levelBoundry);

	// Adds a collider around the entire level
	eList.addEntity(new LevelBoundryCollider(levelBoundry), Layer::Front);

	// Adding Zid
	eList.addEntity(new Zid(sf::Vector2f(300, 0)), Layer::Front);

	// Goes through images used in the map
	cout << "\n[Image set]\n";
	for (MapTileset tileset : map.getTilesets())
	{
		cout << "First gid=" << tileset.getFirstgid() << " name=" << tileset.getName() 
			<< "\twidth=" << tileset.getTilewidth() << "\theight=" << tileset.getTileheight() << endl;
	}
	cout << endl;

	// Goes through all object in the map file						
	for (MapObjectGroup group : map.getObjectGroups())
	{		
		cout << "--[" << group.getName() << "]--" << endl;
		for (MapObject obj : group.getObjects())
		{			
			if (obj.getType() == "EntitySprite")
			{
				sf::Vector2f position(float(obj.getX()), float(obj.getY()));
				MapTileset tileset = map.getTileset(obj.getGid());
				float imageWidth  = float(tileset.getTilewidth());
				float imageHeight = float(tileset.getTileheight());
				Layer layer = getLayerFromString(group.getName());


				eList.addEntity(new EntitySprite(TexturesID::ROOM1_JAR, position), layer);

				cout << "[" << "EntitySprite" << "](" << position.x << ", " <<  position.y << ")\t" 
					<< "\"" << obj.getName() << "\"" << "\t"
					<< "gid=" << obj.getGid() << " "
					<< endl;
			}
			else
			{
				sf::Vector2f position(float(obj.getX()), float(obj.getY()));
				Layer layer = getLayerFromString(group.getName());
				cout << "[" << obj.getType() << "](" << position.x << ", " <<  position.y << ") " 
					<< "\"" << obj.getName() << "\"" << " "
					<< "gid=" << obj.getGid() << " "
					<< endl;
			}
		}

		cout << endl;
	}
	
		
}

TexturesID Level::getTexIdFromString(string strTexId)
{
	for (int i = 0; i < int(TexturesID::SIZE_OF_ENUM); i++)
	{
		if (strTexId == TexturesIDNames[i])
			return TexturesID(i);
	}

	throw logic_error("Level::getTexIdFromString - No texture id with that name.");
	return TexturesID::SIZE_OF_ENUM;
}

Layer Level::getLayerFromString(string strLayer)
{
	if (strLayer == "Background")
		return Layer::Background;
	else if (strLayer == "Front")
		return Layer::Front;
	else if (strLayer == "Foreground")
		return Layer::Foreground;
	else if (strLayer == "Collision")
		return Layer::Collision;

	throw logic_error("Level::getLayerFromString - No Layer with that name.");
	return Layer::Background;
}

