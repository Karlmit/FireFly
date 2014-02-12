#include "Trigger.h"
#include <iostream>
#include "MusicManager.h"
#include "Level.h"

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

void Trigger::BeginContact(b2Contact *contact, Entity* other)
{
	if (other->getID() == "Zid")
	{
		if (isProperty("MusicFadeUp")) 
		{
			MusicManager::fadeUp(getProperty("MusicFadeUp"));
		}

		if (isProperty("ChangeMap"))
			Level::getLevel().changeMap(getProperty("ChangeMap"));
	}	
}

void Trigger::EndContact(b2Contact *contact, Entity* other)
{
	/*
	if (other->getID() == "Zid")
	{
		if (isProperty("MusicFade")) 
		{
			MusicManager::fadeDown(getProperty("MusicFade"));
			cout << "Zid had left the " + getProperty("MusicFade")+ " zone!" << endl;
		}
	}
	*/

	if (isProperty("TriggerOnce") && getProperty("TriggerOnce") == other->getID())
		killEntity();
}