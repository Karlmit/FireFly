#include "StaticLineCollider.h"


StaticLineCollider::StaticLineCollider(vector<sf::Vector2f> points)
: mRigidbody()
{
	mRigidbody.AddStaticLineBody(points);
}

void StaticLineCollider::updateEntity(sf::Time dt) 
{
	
}
		
void StaticLineCollider::drawEntity(sf::RenderTarget& target, sf::RenderStates states) const
{	
	// Rigidbody debug draw
	if (Globals::DEBUG_MODE)
		mRigidbody.drawDebug(target, states);
}