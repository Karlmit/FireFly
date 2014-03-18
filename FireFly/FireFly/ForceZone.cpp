#include "ForceZone.h"

// Temp hack to decrease force to the left
// If needed somewhere else than room 2 change this to a more generic one

ForceZone::ForceZone(sf::FloatRect rect)
	: mActivated(true)
	, mRigidbody()
	, mBodiesInTheZone()
	, mForce()
	, mb2Position(Rigidbody::SfToBoxVec(rect.left, rect.top))
	, mb2Width(Rigidbody::SfToBoxFloat(rect.width))
	, mb2Height(Rigidbody::SfToBoxFloat(rect.height))
{
	mRigidbody.AddTriggerBoxBody(rect, false, sf::Vector2f(0,0));
	mRigidbody.getBody()->SetUserData(this);
	
}

void ForceZone::start()
{
	if (isProperty("xForce") && isProperty("yForce"))
		mForce = b2Vec2(getPropertyFloat("xForce"), getPropertyFloat("yForce"));
}

void ForceZone::sendMessage(Entity* sender, string message)
{
	if (message == "Activate")
		mActivated = true;
	
	if (message == "Deactivate")
		mActivated = false;
}

void ForceZone::updateEntity(sf::Time dt)
{
	if (!mActivated)
		return;

	//
	//	Applies force depending on proximity and value of "Direction".
	//
	for (b2Body* body : mBodiesInTheZone)
	{

		if(isProperty("Direction") == true)
		{
			if(getProperty("Direction") == "Left")
			{
				xRatioFromSource = 1.f - (mb2Position.x + mb2Width - body->GetPosition().x ) / mb2Width;
				body->ApplyForceToCenter(xRatioFromSource*mForce, true);
			}
			else if(getProperty("Direction") == "Right")
			{
				xRatioFromSource = 1.f - (1.f - (mb2Position.x + mb2Width - body->GetPosition().x ) / mb2Width);
				body->ApplyForceToCenter(xRatioFromSource*mForce, true);
			}
			else if(getProperty("Direction") == "Up")
			{
				yRatioFromSource = ((mb2Position.y + mb2Height - body->GetPosition().y ) / mb2Height) - 1.f;
				body->ApplyForceToCenter(yRatioFromSource*mForce, true);
			}
			else if(getProperty("Direction") == "Down")
			{
				yRatioFromSource = 1.f + (1.f - (mb2Position.y + mb2Height - body->GetPosition().y ) / mb2Height);
				body->ApplyForceToCenter(yRatioFromSource*mForce, true);
			}
		}
		else
		{
			xRatioFromSource = 1.f;
			body->ApplyForceToCenter(xRatioFromSource*mForce, true);
		}
	}
}

void ForceZone::drawEntity(sf::RenderTarget& target, sf::RenderStates states) const
{
	// Rigidbody debug draw
	if (Globals::DEBUG_MODE)
		mRigidbody.drawDebug(target, states);
}

void ForceZone::BeginContact(b2Contact *contact, Entity* other)
{
	
	if (mActivated && other->getID() == "Zid")
		other->sendMessage(this, "InAcZone");

	mBodiesInTheZone.insert(contact->GetFixtureA()->GetBody());
	mBodiesInTheZone.insert(contact->GetFixtureB()->GetBody());
}

void ForceZone::EndContact(b2Contact *contact, Entity* other)
{
	mBodiesInTheZone.erase(contact->GetFixtureA()->GetBody());
	mBodiesInTheZone.erase(contact->GetFixtureB()->GetBody());

	if (other->getID() == "Zid")
		other->sendMessage(this, "OutAcZone");
}