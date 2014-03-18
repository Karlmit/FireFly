#include "CrackZone.h"


CrackZone::CrackZone(sf::FloatRect rect)
	: mRigidbody()
	, mActivated(true)
{
	mRigidbody.AddTriggerBoxBody(rect, false, sf::Vector2f(0,0));
	mRigidbody.getBody()->SetUserData(this);
}

void CrackZone::BeginContact(b2Contact *contact, Entity* other)
{
	
}
