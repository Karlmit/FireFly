#include "MapObject.h"

MapObject::MapObject(string name, string type, int gid, int width, int height, int x, int y)
: mName(name)
, mType(type)
, mGid(gid)
, mWidth(width)
, mHeight(height)
, mX(x)
, mY(y)
{
}

MapObject::MapObject()
{
}

MapObject::~MapObject()
{}

void MapObject::insertProperty(string name, string value)
{
    mProperties.push_back(MapObjectProperty(name, value));
}

void MapObject::insertProperty(MapObjectProperty prop)
{
    mProperties.push_back(prop);
}