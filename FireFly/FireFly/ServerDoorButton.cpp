#include "ServerRoomButton.h"

ServerRoomButton::ServerRoomButton(sf::Vector2f position)
	: mSpriteOn(Loading::getTexture("Room 3/knapp_pa scale.png"))
	, mSpriteOff(Loading::getTexture("Room 3/knapp_av scale.png"))
	, mOn(false)
	, mRigidbody()
{
	// Sätter origin för spriten till mitten
	sf::FloatRect bounds = mSpriteOn.getLocalBounds();
	mSpriteOn.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

	bounds = mSpriteOff.getLocalBounds();
	mSpriteOff.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

	setPosition(position);

	//mRigidbody.AddDynCircleBody(500.f, position, 1.f, true);
	sf::FloatRect rect(position.x, position.y, 50.f, 50.f);
	mRigidbody.AddTriggerBoxBody(rect, false, sf::Vector2f());
	mRigidbody.getBody()->SetUserData(this);
}

void ServerRoomButton::updateEntity(sf::Time dt)
{

}

void ServerRoomButton::BeginContact(b2Contact *contact, Entity* other)
{
	mOn = !mOn;
}

void ServerRoomButton::EndContact(b2Contact *contact, Entity* other)
{}

void ServerRoomButton::drawEntity(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	if (mOn)	
		target.draw(mSpriteOn, states);
	else
		target.draw(mSpriteOff, states);

	if (Globals::DEBUG_MODE)
		mRigidbody.drawDebug(target, states);
}