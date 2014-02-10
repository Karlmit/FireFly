#pragma once

#include <string>
#include <vector>
using namespace std;

#include "MapObjectProperty.h"
#include "MapPolyline.h"

class MapObject
{
private:
	string mName;
    string mType;
	int mGid;
    int mX;
    int mY;
	int mWidth;
	int mHeight;
    vector<MapObjectProperty> mProperties;
	MapPolyline mPolyline;

public:
	MapObject(string name, string type, int gid, int x, int y);
	MapObject();
	~MapObject();

	string getName(){ return mName; }
    string getType(){ return mType; }
	int getGid() { return mGid; }
    int getX(){ return mX; }
    int getY(){ return mY; }
	int getWidth(){ return mWidth; }
    int getHeight(){ return mHeight; }
	vector<MapObjectProperty> getProperties(){ return mProperties; }
	MapObjectProperty getProperty(string name)
	{ 
		for (MapObjectProperty prop : mProperties)
			if (prop.getName() == name)
				return prop; 

		return MapObjectProperty();
	}
	MapPolyline getPolyline() { return mPolyline; }

	void setName(string name){ mName = name; }
    void setName(char* name){ mName = name; }
    void setType(string type){ mType = type; }
    void setType(char* type ){ mType = type; }
	void setGid(int gid) { mGid = gid; }
    void setX(int x){ mX = x; }
    void setY(int y){ mY = y; }
	void setWidth(int width){ mWidth = width; }
    void setHeight(int height){ mHeight = height; }

	void insertProperty(string name, string value);
	void insertProperty(MapObjectProperty prop);

	void setPolyline(string strPoly) { mPolyline = MapPolyline(strPoly); }

};
