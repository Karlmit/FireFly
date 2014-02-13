#include "ForceZone.h"


ForceZone::ForceZone(sf::FloatRect rect)
	: mRigidbody()
	, mBodiesInTheZone()
	, mForce()
{
	mRigidbody.AddTriggerBoxBody(rect);
	mRigidbody.getBody()->SetUserData(this);
	
}

void ForceZone::start()
{
	if (isProperty("xForce") && isProperty("yForce"))
		mForce = b2Vec2(getPropertyFloat("xForce"), getPropertyFloat("yForce"));
}

void ForceZone::updateEntity(sf::Time dt)
{
	for (b2Body* body : mBodiesInTheZone)
		body->ApplyForceToCenter(mForce, true);
}

void ForceZone::drawEntity(sf::RenderTarget& target, sf::RenderStates states) const
{
	// Rigidbody debug draw
	if (Globals::DEBUG_MODE)
		mRigidbody.drawDebug(target, states);
}

void ForceZone::BeginContact(b2Contact *contact, Entity* other)
{
	mBodiesInTheZone.insert(contact->GetFixtureA()->GetBody());
	mBodiesInTheZone.insert(contact->GetFixtureB()->GetBody());
}

void ForceZone::EndContact(b2Contact *contact, Entity* other)
{
	mBodiesInTheZone.erase(contact->GetFixtureA()->GetBody());
	mBodiesInTheZone.erase(contact->GetFixtureB()->GetBody());
}