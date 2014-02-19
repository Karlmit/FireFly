#include "StickyZone.h"

#include <iostream>
StickyZone::StickyZone(sf::FloatRect rect)
	: mRigidbody()
{
	mRigidbody.AddTriggerBoxBody(rect);
	mRigidbody.getBody()->SetUserData(this);
}

void StickyZone::start()
{
	mID = "StickyZone";
}

void StickyZone::updateEntity(sf::Time dt)
{
	
}

void StickyZone::drawEntity(sf::RenderTarget& target, sf::RenderStates states) const
{
	// Rigidbody debug draw
	if (Globals::DEBUG_MODE)
		mRigidbody.drawDebug(target, states);
}

void StickyZone::BeginContact(b2Contact *contact, Entity* other)
{
	// Make anything caught in the sticky zone stick
	// except Zid that handles it himself
	if (other->getID() != "Zid")
	{
		contact->GetFixtureA()->GetBody()->SetLinearDamping(999.f);
		contact->GetFixtureB()->GetBody()->SetLinearDamping(999.f);
	}
}

void StickyZone::EndContact(b2Contact *contact, Entity* other)
{

}