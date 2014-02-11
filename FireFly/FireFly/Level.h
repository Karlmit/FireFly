#pragma once
#include "EntityList.h"
#include "Player.h"
#include "Mal.h"
#include "Map.h"

class Level
{
public:
	static Level &getLevel();

	// Start level #
	void startLevel(string level);
	void update();

private:
	Level();
	~Level();
	void operator=(const Level &level);
	static Level level;

public:
	void changeMap(string filename);

private:
	bool mChangeMap;
	string mChangeMapTo;

private:
	// Spawn entities from a map file
	void loadMap(string filename);
	Layer getLayerFromString(string strLayer);
};

