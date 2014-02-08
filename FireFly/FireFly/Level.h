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
private:
	Level();
	~Level();
	void operator=(const Level &level);
	static Level level;

private:
	// Spawn entities from a map file
	void loadMap(string filename);
	Layer getLayerFromString(string strLayer);
};

