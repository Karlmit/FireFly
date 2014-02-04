#pragma once

#include <vector>
using namespace std;
#include "tinyxml2.h"

#include "MapObjectGroup.h"
#include "MapTileset.h"

class Map
{
private:
	string mVersion;
    string mOrientation;
    int mWidth;
    int mHeight;
    int mTilewidth;
    int mTileheight;
    vector<MapTileset> mTilesets;
    vector<MapObjectGroup> mObjectGroups;

public:
	Map(string source);
    ~Map();

	bool loadMap(string source);
	bool loadTilesets(tinyxml2::XMLDocument *map);
	bool loadObjectGroups(tinyxml2::XMLDocument *map);
};