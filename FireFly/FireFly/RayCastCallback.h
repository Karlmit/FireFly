#pragma once 

#include "Box2D\Box2D.h"

class RayCastCallback : public b2RayCastCallback
{
public:
	RayCastCallback();

public:
	b2Fixture* fixture;
	b2Vec2	point;
	b2Vec2 normal;
	float32 fraction;
	bool hit;

private:
	float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction);

	
};