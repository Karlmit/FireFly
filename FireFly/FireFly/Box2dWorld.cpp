
#include "Box2dWorld.h"
#include "WorldContactListener.h"

std::unique_ptr<b2World> Box2dWorld::sWorld(nullptr);
std::unique_ptr<WorldContactListener> Box2dWorld::sListener(nullptr);

void Box2dWorld::newWorld(b2Vec2 gravity) 
{
	sWorld.reset(new b2World(gravity));
	sListener.reset(new WorldContactListener());
	sWorld->SetContactListener(sListener.get());
}

b2World& Box2dWorld::instance() 
{
	return *sWorld.get();
}