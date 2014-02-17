#pragma once

#include "Box2D\Box2D.h"
class Entity;

class ContactListener
{
public:
	virtual void BeginContact(b2Contact *contact, Entity* other) {}
 
	virtual void EndContact(b2Contact *contact, Entity* other) {}
 
	virtual void PreSolve(b2Contact *contact, const b2Manifold *oldManifold, Entity* other) {}
 
	virtual void PostSolve(b2Contact *contact, const b2ContactImpulse *impulse, Entity* other) {}
};