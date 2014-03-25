#ifndef ZID_H
#define ZID_H

#include "Entity.h"
#include "EntityList.h"
#include "Animation.h"
#include "Audio.h"
#include "Log.h"
#include "Hivemind.h"
#include "FallingSprite.h"

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
	bool isSweet();
	sf::Vector2f getDroppedSugar();
	bool inHivemindZone();
	bool inPCZone();
	bool inFireflyZone();
	virtual void sendMessage(Entity* entity, std::string message);



private:
	virtual void updateEntity(sf::Time dt);	
	virtual void drawEntity(sf::RenderTarget& target, sf::RenderStates states) const;	

	virtual void BeginContact(b2Contact *contact, Entity* other); 
	virtual void EndContact(b2Contact *contact, Entity* other); 

	void animation();
	void movement();
	void sugarStuff(sf::Time dt);


private:
	sf::Sprite	mSprite;
	Rigidbody	mRigidbody;
	Animation idleAnimation;
	Animation dashAnimation;
	Animation idleSugarAnimation;
	Animation dashSugarAnimation;
	Animation deathAnimation;
	Animation electricDeathAnimation;
	bool mElctricDeath;
	int deathAnimCount;
	Audio dashSound;
	Entity* mSpoderMan;
	Entity* mWasp;
	bool zidDash;
	int dashFrameNo;
	bool mDirLeft;
	bool mInStickyZone;
	bool mAlive;
	bool hivemindContact;
	bool hivemindEnabled;
	bool mInFireflyZone;
	bool mSugarPile;

	// Light
	Entity* mLight;

	//PC stuff
	Entity* PC;
	sf::Clock PCButton;
	bool mPC_Zone;
	bool mJumpUp;

	//Schakt
	Entity* jaktspindel;

	//sugar stuff
	thor::ParticleSystem mParticleSystem;
	thor::UniversalEmitter mEmitter;
	bool mSweetZid;
	bool mLoseSugar;
	sf::Clock mLoseSugarTimer;
	sf::Vector2f mDroppedSugarPosition;
	Entity* SugarEntity;
	bool mFirstSugarDropped;
	sf::Clock sugarClock;
	float mSugarScale;

	float mSlooowDooown;
	bool mInAcZone;
};

#endif
