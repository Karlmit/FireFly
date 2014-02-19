#include "RayCastCallback.h"

RayCastCallback::RayCastCallback()
	: hit(false)
{
}

float32 RayCastCallback::ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction)
{
	this->fixture = fixture;
	this->point = point;
	this->normal = normal;
	this->fraction = fraction;
	this->hit = true;

	return fraction;
}