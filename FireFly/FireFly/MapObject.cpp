#include "MapObject.h"

MapObject::MapObject(string name, string type, int width, int height, int x, int y)
: mName(name)
, mType(type)
, mWidth(width)
, mHeight(height)
, mX(x)
, mY(y)
{
}

MapObject::~MapObject()
{}

void MapObject::insertProperty(string name, string value)
{
    mProperties.push_back(MapObjectProperty(name, value));
}