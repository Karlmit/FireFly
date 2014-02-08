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


void Level::startLevel1()
{
	// Creates a box2d world
	Box2dWorld::newWorld(b2Vec2(0, -10.f));

	// Loads the level
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
	float mapHeight = float(map.getTileHeight());	

	// Level boundry
	//sf::FloatRect levelBoundry(-mapWidth/2, -mapHeight/2, mapWidth, mapHeight);
	sf::FloatRect levelBoundry(0, 0, mapWidth, mapHeight);

	// Sets level boundry for the camera
	Camera::currentCamera().setBounds(levelBoundry);

	// Adds a collider around the entire level
	eList.addEntity(new LevelBoundryCollider(levelBoundry), Layer::Front);

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
			sf::Vector2f position(float(obj.getX()), float(obj.getY()));
			MapTileset tileset = map.getTileset(obj.getGid());
			float imageWidth  = float(tileset.getTilewidth());
			float imageHeight = float(tileset.getTileheight());
			Layer layer = getLayerFromString(group.getName());
			//position = sf::Vector2f(position.x+imageWidth/2, position.y-imageHeight/2);
			//TexturesID texID = getTexIdFromString(tileset.getName());
			string mapDir = "Maps/";
			mapDir.append(tileset.getImageSource());
			string imageSrc = mapDir;
			string entityType = obj.getType();

			cout << "[" << obj.getType() << "](" << position.x << ", " <<  position.y << ")\t" 
					<< "\"" << obj.getName() << "\"" << "\t"
					<< "gid=" << obj.getGid() << " "
					<< endl;

			if (entityType == "EntitySprite")
			{
				position = sf::Vector2f(position.x+imageWidth/2, position.y-imageHeight/2);
				eList.addEntity(new EntitySprite(imageSrc, position), layer);
			}
			else if (entityType == "Jar")
			{
				position = sf::Vector2f(position.x+imageWidth/2, position.y-imageHeight/2);
				eList.addEntity(new Jar(imageSrc, position), layer);
			}
			else if (entityType == "ZidSpawn") 
			{
				eList.addEntity(new Zid(position), Layer::NPC);
			}
			else if (entityType == "Moth") 
			{
				eList.addEntity(new Mal(position), Layer::NPC);
			}
			else if (entityType == "StaticCollision" || entityType == "StaticCollisionLoop")
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

				eList.addEntity(new StaticLineCollider(sfPoints, loop), Layer::Foreground);
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

