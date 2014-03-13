#ifndef ZID_H
#define ZID_H

#include "Entity.h"
#include "EntityList.h"
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
	bool isSweet();
	sf::Vector2f getDroppedSugar();
	bool inPCZone();
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
	Audio dashSound;
	Entity* mSpoderMan;
	bool zidDash;
	int dashFrameNo;
	bool mDirLeft;
	bool mInStickyZone;
	bool mAlive;
	bool mInFireflyZone;

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
	float mSlooowDooown;
	bool mInAcZone;
	bool hivemindContact;
};

#endif