#include "MapPolyline.h"
#include <sstream>
#include <iostream>

vector<MapPoint> convertStrToPoints(string s)
{
	//cout << endl;
	vector<MapPoint> mapPoints;
	std::string delimiter = " ";

	size_t pos = 0;
	std::string token;
	while ((pos = s.find(delimiter)) != std::string::npos) {
		token = s.substr(0, pos);

		size_t pos2 = 0;
		pos2 = token.find(",");
		string sX = token.substr(0, pos2);
		token.erase(0, pos2+1);
		string sY = token;

		stringstream strstreamX(sX); 
		int intX; 
		strstreamX >> intX;

		stringstream strstreamY(sY); 
		int intY; 
		strstreamY >> intY; 
		
		mapPoints.push_back(MapPoint(intX, intY));
		//cout << "!" << sX << "!" << sY << "!" << endl;

		s.erase(0, pos + delimiter.length());
	}

	token = s;
	size_t pos2 = 0;
	pos2 = token.find(",");
	string sX = token.substr(0, pos2);
	token.erase(0, pos2+1);
	string sY = token;

	stringstream strstreamX(sX); 
	int intX; 
	strstreamX >> intX;

	stringstream strstreamY(sY); 
	int intY; 
	strstreamY >> intY; 
		
	mapPoints.push_back(MapPoint(intX, intY));

	//cout << "!" << sX << "!" << sY << "!" << endl;
	//cout << endl;

	return mapPoints;
}


MapPolyline::MapPolyline()
{
}

MapPolyline::MapPolyline(string stringOfPoints)
: mStringOfPoints(stringOfPoints)
{
	mPoints = convertStrToPoints(stringOfPoints);
}

MapPolyline::~MapPolyline()
{
}

void MapPolyline::setString(string stringOfPoints)
{
	mStringOfPoints = stringOfPoints;
	mPoints = convertStrToPoints(stringOfPoints);
}







MapPoint::MapPoint() 
	: x(0)
	, y(0)
{
}

MapPoint::MapPoint(int x, int y) 
	: x(x)
	, y(y)
{
}