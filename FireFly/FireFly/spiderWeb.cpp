#include "spiderWeb.h"

#include <iostream>
spiderWeb::spiderWeb(sf::FloatRect rect)
	: mRigidbody()
{
	mRigidbody.AddTriggerBoxBody(rect, false, sf::Vector2f(0,0));
	mRigidbody.getBody()->SetUserData(this);
}

void spiderWeb::start()
{
	//Fetch Zid
}

void spiderWeb::updateEntity(sf::Time dt)
{
}

void spiderWeb::drawEntity(sf::RenderTarget& target, sf::RenderStates& states) const
{
	// Rigidbody debug draw
	if (Globals::DEBUG_MODE)
		mRigidbody.drawDebug(target, states);
}

void spiderWeb::BeginContact(b2Contact *contact, Entity* other)
{

}

void spiderWeb::EndContact(b2Contact *contact, Entity* other)
{

}