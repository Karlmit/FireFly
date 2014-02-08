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
	Map();
    ~Map();

	bool loadMap(string source);
	void loadTilesets(tinyxml2::XMLDocument *xmlmap);
	void loadObjectGroups(tinyxml2::XMLDocument *xmlmap);

	string getVersion(){ return mVersion; }
    string getOrientation(){ return mOrientation; }
    int getWidth(){ return mWidth; }
    int getHeight(){ return mHeight; }
    int getTileWidth(){ return mTilewidth; }
    int getTileHeight(){ return mTileheight; }
	MapTileset getTileset(int gid);
	
	vector<MapTileset> getTilesets() { return mTilesets; }
	vector<MapObjectGroup> getObjectGroups() { return mObjectGroups; }
	
};