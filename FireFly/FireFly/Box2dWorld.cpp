
#include "Box2dWorld.h"

std::unique_ptr<b2World> Box2dWorld::sWorld(nullptr);

void Box2dWorld::newWorld(b2Vec2 gravity) 
{
	sWorld.reset(new b2World(gravity));
}

b2World& Box2dWorld::instance() 
{
	return *sWorld.get();
}