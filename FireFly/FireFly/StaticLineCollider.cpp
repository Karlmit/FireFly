#include "StaticLineCollider.h"


StaticLineCollider::StaticLineCollider(vector<sf::Vector2f> points, bool loop)
: mRigidbody()
{
	mRigidbody.AddStaticLineBody(points, loop);
	// Add into box2d callbacks
	mRigidbody.getBody()->SetUserData(this);

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