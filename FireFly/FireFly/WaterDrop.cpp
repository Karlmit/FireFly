#include "WaterDrop.h"


WaterDrop::WaterDrop(sf::Vector2f position, float endPosition, float width, float height)
	: mSprite(Loading::getTexture("Schakt/WaterDrop.png", true))
{
	mID = "WaterDropp";
	//RigidBody
	sf::FloatRect bounds = mSprite.getLocalBounds();
	sf::FloatRect rects(bounds.left, bounds.top, bounds.width, bounds.height);
	mRigidbody.AddTriggerBoxBody(rects, true, position);
	mRigidbody.getBody()->SetUserData(this);

	mEndPosition = endPosition;
	mPosition = position;
	setPosition(position);
}

WaterDrop::WaterDrop(float xPosition, float yPosition, float endPosition, float width, float height)
	: mSprite(Loading::getTexture("Schakt/WaterDrop.png", true))
	, 	mPosition(xPosition, yPosition)
{
	mID = "WaterDropp";
	//RigidBody
	sf::FloatRect bounds = mSprite.getLocalBounds();
	sf::FloatRect rects(bounds.left, bounds.top, bounds.width, bounds.height);
	mRigidbody.AddTriggerBoxBody(rects, true, sf::Vector2f(xPosition, yPosition));
	mRigidbody.getBody()->SetUserData(this);
	mEndPosition = endPosition;
	setPosition(mPosition);
}

WaterDrop::~WaterDrop()
{
}


void WaterDrop::sendMessage(Entity* entity, std::string message)
{

}

void WaterDrop::updateEntity(sf::Time dt)
{
	mRigidbody.update();
	setPosition(mRigidbody.getPosition());

	if(mRigidbody.getPosition().y >= mEndPosition)
	{
		mRigidbody.getBody()->SetTransform(Rigidbody::SfToBoxVec(mPosition), 0);
		mRigidbody.getBody()->SetLinearVelocity(Rigidbody::SfToBoxVec(0, 12));
	}


}

void WaterDrop::drawEntity(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(mSprite, states);

	// Rigidbody debug draw
	if (Globals::DEBUG_MODE)
		mRigidbody.drawDebug(target, states);
}


