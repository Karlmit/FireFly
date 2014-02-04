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
	int mGid;
    int mX;
    int mY;
    vector<MapObjectProperty> mProperties;

public:
	MapObject(string name, string type, int gid, int x, int y);
	MapObject();
	~MapObject();

	string getName(){ return mName; }
    string getType(){ return mType; }
	int getGid() { return mGid; }
    int getX(){ return mX; }
    int getY(){ return mY; }
	vector<MapObjectProperty> getProperties(int index){ return mProperties; }

	void setName(string name){ mName = name; }
    void setName(char* name){ mName = name; }
    void setType(string type){ mType = type; }
    void setType(char* type ){ mType = type; }
	void setGid(int gid) { mGid = gid; }
    void setX(int x){ mX = x; }
    void setY(int y){ mY = y; }

	void insertProperty(string name, string value);
	void insertProperty(MapObjectProperty prop);

};
