#pragma once

#include "Entity.h"
#include "Audio.h"

const float DEF_DENSITY = 4.f;

class Jar : public Entity
{
public:
	Jar(string texture, sf::Vector2f position, float density = DEF_DENSITY, bool dynamic = true);

private:
	virtual void	updateEntity(sf::Time dt);	
	virtual void	drawEntity(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	Rigidbody mRigidbody;
	sf::Sprite mSprite;
	Audio mBreakSound;
	bool mBroken;

private:
	// Box2d callback functions
	virtual void BeginContact(b2Contact *contact); 
	//virtual void EndContact(b2Contact *contact); 
	//virtual void PreSolve(b2Contact *contact, const b2Manifold *oldManifold); 
	virtual void PostSolve(b2Contact *contact, const b2ContactImpulse *impulse);
};