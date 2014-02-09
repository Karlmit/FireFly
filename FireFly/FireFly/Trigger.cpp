#include "Trigger.h"
#include <iostream>

Trigger::Trigger(sf::FloatRect rect)
	: mRigidbody()
{
	mRigidbody.AddTriggerBoxBody(rect);
	mRigidbody.getBody()->SetUserData(this);
}

void Trigger::updateEntity(sf::Time dt)
{

}

void Trigger::drawEntity(sf::RenderTarget& target, sf::RenderStates states) const
{
	// Rigidbody debug draw
	if (Globals::DEBUG_MODE)
		mRigidbody.drawDebug(target, states);
}

void Trigger::BeginContact(b2Contact *contact)
{
	Entity* a = static_cast<Entity*> (contact->GetFixtureA()->GetBody()->GetUserData());
	Entity* b = static_cast<Entity*> (contact->GetFixtureB()->GetBody()->GetUserData());

	if (a != nullptr)
		if (a->getID() == "Zid" )
			cout << "Zid entered the zone!" << endl;
	
	if (b != nullptr)
		if (b->getID() == "Zid" )
			cout << "Zid entered the zone!" << endl;
}

void Trigger::EndContact(b2Contact *contact)
{
	Entity* a = static_cast<Entity*> (contact->GetFixtureA()->GetBody()->GetUserData());
	Entity* b = static_cast<Entity*> (contact->GetFixtureB()->GetBody()->GetUserData());

	if (a != nullptr)
		if (a->getID() == "Zid" )
			cout << "Zid left the zone!" << endl;

	if (b != nullptr)
		if (b->getID() == "Zid" )
			cout << "Zid left the zone!" << endl;
}