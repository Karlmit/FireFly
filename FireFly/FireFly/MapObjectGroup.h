#pragma once

#include <string>
using namespace std;

#include "MapObject.h"

class MapObjectGroup
{
private:
	string mName;
    int mWidth;
    int mHeight;
    vector<MapObject> mObjects;

public:
	MapObjectGroup(string name, int width, int height);
	~MapObjectGroup();

	string getName(){ return mName; }
    int getWidth(){ return mWidth; }
    int getHeight(){ return mHeight; }
	vector<MapObject> getObjects(){ return mObjects; }

	void insertObject(MapObject object);
};
