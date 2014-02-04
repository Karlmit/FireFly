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
	MapTileset();
    ~MapTileset();

	int getFirstgid(){ return mFirstgid; }
    string getName(){ return mName; }
    int getTilewidth(){ return mTilewidth; }
    int getTileheight(){ return mTileheight; }
    string getImageSource(){ return mImage_source; }

	void setFirstgid(int gid){ mFirstgid = gid; }
    void setName(string name){ mName = name; }
    void setName(char* name){ mName = name; }
    void setTilewidth(int width){ mTilewidth = width; }
    void setTileheight(int height){ mTileheight = height; }
    void setImageSource(string source){ mImage_source = source; }
    void setImageSource(char* source){ mImage_source = source; }

};