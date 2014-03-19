#include "Trigger.h"
#include <iostream>
#include "MusicManager.h"
#include "Level.h"

Trigger::Trigger(sf::FloatRect rect)
	: mRigidbody()
	, mSuccess(Loading::getSound("Room 2/Datorblips/Blip1.wav"), true)
	, mDeadRat(Loading::getSound("Schakt/deadRatSound.wav"), true)
{
	mRigidbody.AddTriggerBoxBody(rect, false, sf::Vector2f(0,0));
	mRigidbody.getBody()->SetUserData(this);

	//DeadRat
	mDeadRatOnce = false;
	//mSuccess
	mFanOn = false;
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
		{
			for (string id : getProperties("ToggleOn"))
			{
				EntityList::getEntityList().getEntity(id)->sendMessage(this, "ToggleOn");
			
			}
		}
		if (isProperty("ToggleOff"))
			for (string id : getProperties("ToggleOff"))
			{
				EntityList::getEntityList().getEntity(id)->sendMessage(this, "ToggleOff");
				mFanOn = false;
			}

				
		if (isProperty("Toggle"))
			for (string id : getProperties("Toggle"))
				EntityList::getEntityList().getEntity(id)->sendMessage(this, "Toggle");

		if (isProperty("TurnOn"))
		{
			EntityList::getEntityList().getEntity(getProperty("TurnOn"))->sendMessage(this, "TurnOn");
			if(mFanOn == false)
			{
				mSuccess.play();
				mFanOn = true;
			}
		}

		if (isProperty("TurnOff"))
		{
			EntityList::getEntityList().getEntity(getProperty("TurnOff"))->sendMessage(this, "TurnOff");
		}

		if (isProperty("ScreenOn"))
		{
			EntityList::getEntityList().getEntity(getProperty("ScreenOn"))->sendMessage(this, "ScreenOn");			
		}
			if (isProperty("ScreenOff"))
		{
			EntityList::getEntityList().getEntity(getProperty("ScreenOff"))->sendMessage(this, "ScreenOff");
		}




			
		if(isProperty("Spider"))
			EntityList::getEntityList().getEntity("spoderMan")->sendMessage(this, "spiderisinRoom");

		if(isProperty("DeadRatSoundZone") && mDeadRatOnce == false)
		{
			mDeadRat.play();
			mDeadRatOnce = true;
		}

	}	
}

void Trigger::EndContact(b2Contact *contact, Entity* other)
{	

	if (isProperty("TriggerOnce") && getProperty("TriggerOnce") == other->getID())
		killEntity();
}