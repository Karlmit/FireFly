#pragma once

#include <sstream>
#include <vector>
using namespace std;

class MapPoint
{
public:
	int x;
	int y;

public:
	MapPoint();
	MapPoint(int x, int y);
};

class MapPolyline
{
private:
	string mStringOfPoints;
	vector<MapPoint> mPoints;

public:
	MapPolyline();
	MapPolyline(string stringOfPoints);
	~MapPolyline();	
	
	string getStringOfPoints() { return mStringOfPoints; }
	vector<MapPoint> getPoints() { return mPoints; }

	void setString(string stringOfPoints);	
};

