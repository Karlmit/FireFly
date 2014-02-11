#pragma once

#include "MapObjectProperty.h"
#include <vector>
using namespace std;

class Properties
{
public:
	void setProperties(const vector<MapObjectProperty>& properties) { mProperties = properties; }

	vector<MapObjectProperty> getProperties(){ return mProperties; }

	string getProperty(string name)
	{ 
		for (MapObjectProperty prop : mProperties)
			if (prop.getName() == name)
				return prop.getValueString(); 

		return "";
	}

	int getPropertyInt(string name)
	{ 
		for (MapObjectProperty prop : mProperties)
			if (prop.getName() == name)
				return prop.getValueInt(); 

		return 0;
	}

	float getPropertyFloat(string name)
	{ 
		for (MapObjectProperty prop : mProperties)
			if (prop.getName() == name)
				return prop.getValueFloat(); 

		return 0;
	}

	bool isProperty(string name)
	{
		for (MapObjectProperty prop : mProperties)
			if (prop.getName() == name)
				return true; 

		return false;
	}

private:
	vector<MapObjectProperty> mProperties;
};