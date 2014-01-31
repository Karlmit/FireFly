#include "StaticCollider.h"


StaticCollider::StaticCollider(sf::Vector2f position) 
: mRigidbody(sf::FloatRect(position.x, position.y, 1000.f, 100.f), true)
{

}

void StaticCollider::updateEntity(sf::Time dt) 
{
	
}
		
void StaticCollider::drawEntity(sf::RenderTarget& target, sf::RenderStates states) const
{	
	// Rigidbody debug draw
	if (Globals::DEBUG_MODE)
		mRigidbody.drawDebug(target, states);
}