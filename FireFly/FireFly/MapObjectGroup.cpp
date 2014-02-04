#include "MapObjectGroup.h"

MapObjectGroup::MapObjectGroup(string name, int width, int height)
: mName(name)
, mWidth(width)
, mHeight(height)
{
}

MapObjectGroup::~MapObjectGroup()
{
}

void MapObjectGroup::insertObject(MapObject object)
{
	mObjects.push_back(object);
}
