#include "FireflyZone.h"


FireflyZone::FireflyZone(sf::FloatRect rect)
	: mRigidbody()
{
	mRigidbody.AddTriggerBoxBody(rect, false, sf::Vector2f(0,0));
	mRigidbody.getBody()->SetUserData(this);

	setPosition(rect.left+(rect.width/2), rect.top+(rect.height/2));

//	imitateZid = false;
}

void FireflyZone::start()
{
	mID = "FireflyZone";
	mZid = EntityList::getEntityList().getEntity("Zid");
	dora = static_cast <FireflyNPC*>(EntityList::getEntityList().getEntity("FireflyNPC"));
}

void FireflyZone::drawEntity(sf::RenderTarget& target, sf::RenderStates states) const
{
	//Rigidbody debug draw
	if (Globals::DEBUG_MODE)
		mRigidbody.drawDebug(target, states);
}

void FireflyZone::BeginContact(b2Contact *contact, Entity* mZid)
{
//	imitateZid = true;
	dora->imitateZid = true;
}

void FireflyZone::EndContact(b2Contact *contact, Entity* mZid)
{
//	imitateZid = false;
	dora->imitateZid = false;
}