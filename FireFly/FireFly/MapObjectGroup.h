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
	MapObjectGroup();
	~MapObjectGroup();

	string getName(){ return mName; }
    int getWidth(){ return mWidth; }
    int getHeight(){ return mHeight; }
	vector<MapObject> getObjects(){ return mObjects; }

	void setName(string name){ mName = name; }
    void setName(char* name){ mName = name; }
    void setWidth(int width){ mWidth = width; }
    void setHeight(int height){ mHeight = height; }

	void insertObject(MapObject object);
};
