#pragma once

#include "Entity.h"
#include "Hivemind.h"

class CrackZone :
	public Entity
{
public:
	CrackZone(sf::FloatRect rect);

	virtual void BeginContact(b2Contact *contact, Entity* other);
private:
	Rigidbody mRigidbody;
	bool mActivated;
//	Hivemind fireflyHivemind;
};

