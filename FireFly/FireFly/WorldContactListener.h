#pragma once

#include <Box2D\Box2D.h>

class WorldContactListener : public b2ContactListener
{
	virtual void BeginContact(b2Contact *contact);
 
	virtual void EndContact(b2Contact *contact);
 
	virtual void PreSolve(b2Contact *contact, const b2Manifold *oldManifold);
 
	virtual void PostSolve(b2Contact *contact, const b2ContactImpulse *impulse);
};