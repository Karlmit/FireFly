#pragma once

#include <string>
using namespace std;

class MapTileset
{
private:
	int mFirstgid;
    string mName;
    int mTilewidth;
    int mTileheight;
    string mImage_source;

public:
	MapTileset(int firstgid, string name, int tilewidth, int tileheight, string image_source);
    ~MapTileset();

	int getFirstgid(){ return mFirstgid; }
    string getName(){ return mName; }
    int getTilewidth(){ return mTilewidth; }
    int getTileheight(){ return mTileheight; }
    string getImageSource(){ return mImage_source; }

};