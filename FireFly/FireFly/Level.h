#pragma once
#include "EntityList.h"
#include "Player.h"
#include "Mal.h"
#include "Map.h"

class Level
{
public:
	static Level &getLevel();
	static sf::Vector2f getLevelSize();
	static void startLevel(string level);
	static void changeMap(string filename);
	static void fadeToBlackChangeLevel(string filename);
	static void update();

private:
	Level();
	~Level();
	void operator=(const Level &level);
	static Level level;

public:
	
	

private:
	bool mChangeMap;
	string mChangeMapTo;
	sf::Vector2f mMapSize;

private:
	// Spawn entities from a map file
	void loadMap(string filename);
	Layer getLayerFromString(string strLayer);
};

