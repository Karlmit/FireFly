#pragma once
#include "EntityList.h"
#include "Player.h"
#include "Mal.h"
#include "Map.h"
#include "Spider.h"


class Level
{
public:
	static Level &getLevel();
	static sf::Vector2f getLevelSize();
	static void startLevel(string level);
	static void changeMap(string filename);
	static void fadeToBlackChangeLevel(string filename);
	static void update();
	static void restartLevel(float delay = 0);

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

	// restartlevel
	bool mRestartingLevel;
	float mDelay;
	sf::Clock mDelayTimer;

private:
	// Spawn entities from a map file
	void loadMap(string filename);
	Layer getLayerFromString(string strLayer);
};

