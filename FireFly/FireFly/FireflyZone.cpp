// #include "FireflyZone.h"


/* FireflyZone::FireflyZone(sf::FloatRect rect)
	: mRigidbody()
{
	mRigidbody.AddTriggerBoxBody(rect);
	mRigidbody.getBody()->SetUserData(this);

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

void FireflyZone::BeginContact(b2Contact *contact, Entity* other)
{
//	imitateZid = true;
	dora->imitateZid = true;
}

void FireflyZone::EndContact(b2Contact *contact, Entity* other)
{
//	imitateZid = false;
	dora->imitateZid = false;
} */