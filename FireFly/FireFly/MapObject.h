#pragma once


#include <string>
#include <vector>
using namespace std;

#include "MapObjectProperty.h"

class MapObject
{
private:
	string mName;
    string mType;
    int mWidth;
    int mHeight;
    int mX;
    int mY;
    vector<MapObjectProperty> mProperties;

public:
	MapObject(string name, string type, int width, int height, int x, int y);
	~MapObject();

	string getName(){ return mName; }
    string getType(){ return mType; }
    int getWidth(){ return mWidth; }
    int getHeight(){ return mHeight; }
    int getX(){ return mX; }
    int getY(){ return mY; }
	vector<MapObjectProperty> getProperties(int index){ return mProperties; }


	void insertProperty(string name, string value);

};
