#pragma once

#include "Box2D\Box2D.h"
#include "WorldContactListener.h"
#include <memory>

class Box2dWorld {

public:
	static void newWorld(b2Vec2 gravity);
	static b2World& instance();

private:
	static std::unique_ptr<b2World> sWorld;
	static std::unique_ptr<WorldContactListener> sListener;
};