#include "WaterDrop.h"


WaterDrop::WaterDrop(sf::Vector2f position, float endPosition, float spawnTime)
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
	mActivate = false;
	mSpawnTime = spawnTime;
	mSpawnClock.restart();
}


WaterDrop::~WaterDrop()
{
}


void WaterDrop::sendMessage(Entity* entity, std::string message)
{

}

void WaterDrop::updateEntity(sf::Time dt)
{
	if(mSpawnClock.getElapsedTime().asSeconds() > mSpawnTime)
	{
		mActivate = true;
	}
	if(mActivate == true)
	{
		mRigidbody.update();
		setPosition(mRigidbody.getPosition());

		if(mRigidbody.getPosition().y >= mEndPosition)
		{
			mRigidbody.getBody()->SetTransform(Rigidbody::SfToBoxVec(mPosition), 0);
			mRigidbody.getBody()->SetLinearVelocity(Rigidbody::SfToBoxVec(0, 6));
		}
	}

}

void WaterDrop::drawEntity(sf::RenderTarget& target, sf::RenderStates states) const
{
	if(mActivate == true)
	{
		states.transform *= getTransform();
		target.draw(mSprite, states);
	}
	// Rigidbody debug draw
	if (Globals::DEBUG_MODE)
		mRigidbody.drawDebug(target, states);
}


