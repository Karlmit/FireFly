#include "MapTileset.h"

MapTileset::MapTileset(int firstgid, string name, int tilewidth, int tileheight, string image_source)
: mFirstgid(firstgid)
, mName(name)
, mTilewidth(tilewidth)
, mTileheight(tilewidth)
, mImage_source(image_source)
{
}

MapTileset::MapTileset()
{
}

MapTileset::~MapTileset()
{
}

