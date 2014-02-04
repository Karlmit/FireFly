#pragma once

#include <sstream>
using namespace std;

class MapObjectProperty
{
private:
	string mName;
	string mValue;

public:
	MapObjectProperty(string name, string value);
	~MapObjectProperty();
	
	string getName();
	string getValueString();
    int getValueInt();    

	void setName(string name);
    //void setName(char* name){ this->name = name; }
    void setValue(string value);
    //void setValue(char* value){ this->value = value; }
};