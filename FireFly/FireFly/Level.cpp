#include "Level.h"
#include "Loading.h"
#include "Box2dWorld.h"
#include "Camera.h"

#include "Zid.h"
#include "EntitySprite.h"
#include "StaticLineCollider.h"
#include "LevelBoundryCollider.h"
#include "Jar.h"
#include "Mal.h"
#include "Trigger.h"

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


void Level::startLevel(string levelName)
{
	// Clear all entities
	EntityList::getEntityList().emptyList();

	// Creates a box2d world
	Box2dWorld::newWorld(b2Vec2(0, -10.f));
	

	// Loads the level
	string mapStr = "Maps/";
	mapStr.append(levelName);

	loadMap(mapStr);

	// Runs start() on all entities
	EntityList::getEntityList().startList();
}

void Level::loadMap(string filename)
{
	// Loads all the map data in to the Map class object
	Map map;
	if (map.loadMap(filename) == false) {
		cout << endl << "There is no map with the name \"" << filename << "\"" << endl;
		return;
	}

	cout << "Loads level \"" << filename << "\"" << endl;

	// Gets the entitylist
	EntityList& eList = EntityList::getEntityList();

	// Get the map width and height
	float mapWidth = float(map.getTileWidth());
	float mapHeight = float(map.getTileHeight());	

	// Level boundry
	//sf::FloatRect levelBoundry(-mapWidth/2, -mapHeight/2, mapWidth, mapHeight);
	sf::FloatRect levelBoundry(0, 0, mapWidth, mapHeight);

	// Sets level boundry for the camera
	Camera::currentCamera().setBounds(levelBoundry);

	// Adds a collider around the entire level
	eList.addEntity(new LevelBoundryCollider(levelBoundry), Layer::Front, false);

	// Adding Zid get that from the object loop
	//eList.addEntity(new Zid(sf::Vector2f(300, 0)), Layer::Front);

	// Goes through images used in the map
	cout << "\n[Image set]\n";
	for (MapTileset tileset : map.getTilesets())
	{
		cout << "First gid=" << tileset.getFirstgid() << " name=" << tileset.getName() 
			<< "\twidth=" << tileset.getTilewidth() << "\theight=" << tileset.getTileheight() << endl;
		cout << "src=" << tileset.getImageSource() << endl;
		cout << endl;
	}
	cout << endl;

	// Goes through all object in the map file						
	for (MapObjectGroup group : map.getObjectGroups())
	{		
		cout << "--[" << group.getName() << "]--" << endl;
		for (MapObject obj : group.getObjects())
		{
			// Gets the data for the object
			float width = float(obj.getWidth());
			float height = float(obj.getWidth());
			sf::Vector2f position(float(obj.getX()), float(obj.getY()));
			MapTileset tileset = map.getTileset(obj.getGid());
			float imageWidth  = float(tileset.getTilewidth());
			float imageHeight = float(tileset.getTileheight());
			Layer layer = getLayerFromString(group.getName());
			string mapDir = "Maps/";
			mapDir.append(tileset.getImageSource());
			//string imageSrc = mapDir;
			string imageSrc = tileset.getImageSource();
			string entityType = obj.getType();

			cout << "[" << obj.getType() << "](" << position.x << ", " <<  position.y << ")\t" 
					<< "\"" << obj.getName() << "\"" << "\t"
					<< "gid=" << obj.getGid() << " "
					<< endl;

			// Spawn the right entity based on type and/or layer
			if (entityType == "EntitySprite")
			{
				position = sf::Vector2f(position.x+imageWidth/2, position.y-imageHeight/2);
				eList.addEntity(new EntitySprite(imageSrc, position), layer, false);
			}
			else if (entityType == "Jar")
			{
				position = sf::Vector2f(position.x+imageWidth/2, position.y-imageHeight/2);
				eList.addEntity(new Jar(imageSrc, position), layer, false);
			}
			else if (entityType == "ZidSpawn") 
			{
				eList.addEntity(new Zid(position), Layer::NPC, false);
			}
			else if (entityType == "Moth") 
			{
				eList.addEntity(new Mal(position), Layer::NPC, false);
			}
			else if (layer == Layer::Collision || entityType == "StaticCollision" || entityType == "StaticCollisionLoop")
			{
				bool loop = entityType == "StaticCollisionLoop" ? true : false;
				vector<sf::Vector2f> sfPoints;

				cout << "Polylines= ";
				for (MapPoint p : obj.getPolyline().getPoints())
				{
					cout << p.x << "," << p.y << " ";
					sf::Vector2f sfPoint(float(p.x), float(p.y));
					sfPoint = sfPoint + position;
					sfPoints.push_back(sfPoint);
				}
				cout << endl;

				if (!sfPoints.empty())
					eList.addEntity(new StaticLineCollider(sfPoints, loop), Layer::Foreground, false);
			}
			else if (entityType == "Trigger")
			{
				sf::FloatRect rect;
				rect.left = position.x;
				rect.top = position.y;
				rect.width = width;
				rect.height = height;
				eList.addEntity(new Trigger(rect), Layer::Foreground, false);
			}
		}

		cout << endl;
	}		
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
	else if (strLayer == "Misc")
		return Layer::Misc;
	else if (strLayer == "NPC")
		return Layer::NPC;

	string ectStr = "Level::getLayerFromString - No Layer with that name: ";
	ectStr.append(strLayer);
	throw logic_error(ectStr);
	return Layer::Background;
}

