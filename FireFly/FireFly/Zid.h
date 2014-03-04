#ifndef ZID_H
#define ZID_H

#include "Entity.h"
#include "Animation.h"
#include "Audio.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include <Thor/Particles.hpp>
#include <Thor/Animation.hpp>
#include <Thor/Vectors/PolarVector.hpp>
#include <Thor/Math/Distributions.hpp>

class Zid : public Entity
{
public:
	Zid(sf::Vector2f position);

private:
	virtual void updateEntity(sf::Time dt);	
	virtual void drawEntity(sf::RenderTarget& target, sf::RenderStates states) const;

	virtual void BeginContact(b2Contact *contact, Entity* other); 
	virtual void EndContact(b2Contact *contact, Entity* other); 

	void movement();
	void sugarStuff(sf::Time dt);

private:
	sf::Sprite	mSprite;
	Rigidbody	mRigidbody;
	Animation idleAnimation;
	Animation dashAnimation;
	Audio dashSound;
	bool zidDash;
	int dashFrameNo;
	bool mDirLeft;
	bool mInStickyZone;
	bool mInFireflyZone;

	thor::ParticleSystem mParticleSystem;
	thor::UniversalEmitter mEmitter;
	bool mSweetZid;
	sf::Clock mLoseSugarTimer;
};

#endif
