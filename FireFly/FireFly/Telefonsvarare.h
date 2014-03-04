#pragma once

#include "Entity.h"
#include "Audio.h"
#include "Animation.h"



class Telefonsvarare : public Entity
{
public:
	Telefonsvarare(sf::Vector2f position);

private:
	virtual void updateEntity(sf::Time dt);	
	virtual void drawEntity(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void sendMessage(Entity* sender, string message);

	virtual void BeginContact(b2Contact *contact, Entity* other); 
	virtual void EndContact(b2Contact *contact, Entity* other);

private:
	enum class State 
	{
		Blinking,
		Repeat,
		Running
	};

private:
	Animation mBlinking;
	Animation mRepeat;
	Animation mRunning;

	Audio mAudioMessage;
	Rigidbody mRigidbody;

	State mState;
};
