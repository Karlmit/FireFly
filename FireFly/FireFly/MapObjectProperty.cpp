#include "MapObjectProperty.h"

MapObjectProperty::MapObjectProperty()
{
}

MapObjectProperty::MapObjectProperty(string name, string value)
: mName(name)
, mValue(value)
{}

MapObjectProperty::~MapObjectProperty()
{}


string MapObjectProperty::getName()
{
	return mName;
}

string MapObjectProperty::getValueString()
{
	return mValue;
}

int MapObjectProperty::getValueInt()
{
	stringstream strstream(mValue); 
	int value; 
	strstream >> value; 
	return value;
}

void MapObjectProperty::setName(string name)
{
	mName = name;
}

void MapObjectProperty::setValue(string value)
{
	mValue = value;
}