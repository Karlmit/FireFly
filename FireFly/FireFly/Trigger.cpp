#include "Trigger.h"
#include <iostream>
#include "MusicManager.h"

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

	vector<Entity*> ab;
	if (a != nullptr)
		ab.push_back(a);
	if (b != nullptr)
	ab.push_back(b);


	for (Entity* e : ab)
	{		
		if (e->getID() == "Zid" )
		{
			if (isProperty("MusicFade")) {
				MusicManager::fadeUp(getProperty("MusicFade"));
				cout << "Zid entered the " + getProperty("MusicFade")+ " zone!" << endl;
			}
		}
	}	
			
}

void Trigger::EndContact(b2Contact *contact)
{
	Entity* a = static_cast<Entity*> (contact->GetFixtureA()->GetBody()->GetUserData());
	Entity* b = static_cast<Entity*> (contact->GetFixtureB()->GetBody()->GetUserData());

	vector<Entity*> ab;
	if (a != nullptr)
		ab.push_back(a);
	if (b != nullptr)
		ab.push_back(b);

	for (Entity* e : ab)
	{		
		if (e->getID() == "Zid" )
		{
			if (isProperty("MusicFade")) {
				MusicManager::fadeDown(getProperty("MusicFade"));
				cout << "Zid had left the " + getProperty("MusicFade")+ " zone!" << endl;
			}
		}
	}
}