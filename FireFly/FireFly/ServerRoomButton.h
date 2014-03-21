#pragma once

#include "Entity.h"
#include "Rigidbody.h"

class ServerRoomButton : public Entity 
{
public:
	ServerRoomButton(sf::Vector2f position);

private:
	virtual void updateEntity(sf::Time dt);	
	virtual void drawEntity(sf::RenderTarget& target, sf::RenderStates states) const;

	virtual void BeginContact(b2Contact *contact, Entity* other); 
	virtual void EndContact(b2Contact *contact, Entity* other); 

private:
	sf::Sprite mSpriteOn;
	sf::Sprite mSpriteOff;
	bool mOn;
	Rigidbody mRigidbody;
};