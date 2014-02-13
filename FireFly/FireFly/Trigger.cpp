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
		if (isProperty("MusicFadeDownAll"))
			MusicManager::fadeDownAll();

		if (isProperty("MusicFadeUp")) 
			MusicManager::fadeUp(getProperty("MusicFadeUp"));

		if (isProperty("ChangeMap"))
			Level::getLevel().fadeToBlackChangeLevel(getProperty("ChangeMap"));

		if (isProperty("ToggleOn"))
			for (string id : getProperties("ToggleOn"))
				EntityList::getEntityList().getEntity(id)->sendMessage(this, "ToggleOn");

		if (isProperty("ToggleOff"))
			for (string id : getProperties("ToggleOff"))
				EntityList::getEntityList().getEntity(id)->sendMessage(this, "ToggleOff");

		if (isProperty("Toggle"))
			for (string id : getProperties("Toggle"))
				EntityList::getEntityList().getEntity(id)->sendMessage(this, "Toggle");
	}	
}

void Trigger::EndContact(b2Contact *contact, Entity* other)
{	

	if (isProperty("TriggerOnce") && getProperty("TriggerOnce") == other->getID())
		killEntity();
}