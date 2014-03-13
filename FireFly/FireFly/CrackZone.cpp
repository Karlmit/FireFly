#include "CrackZone.h"


CrackZone::CrackZone(sf::FloatRect rect)
	: mRigidbody()
	, mActivated(true)
{
	mRigidbody.AddTriggerBoxBody(rect);
	mRigidbody.getBody()->SetUserData(this);
}

void CrackZone::BeginContact(b2Contact *contact, Entity* other)
{
		
}
