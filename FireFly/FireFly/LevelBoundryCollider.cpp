#include "LevelBoundryCollider.h"


LevelBoundryCollider::LevelBoundryCollider(sf::FloatRect rect)
: mRigidbody()
{
	// Create the levelboundry around the rect
	std::vector<sf::Vector2f> listOfPoints;
	listOfPoints.push_back(sf::Vector2f(rect.left,				rect.top)); 
	listOfPoints.push_back(sf::Vector2f(rect.left,				rect.top+rect.height));
	listOfPoints.push_back(sf::Vector2f(rect.left+rect.width,	rect.top+rect.height));
	listOfPoints.push_back(sf::Vector2f(rect.left+rect.width,	rect.top));
	mRigidbody.AddStaticLineBody(listOfPoints, true);

	// Add into box2d callbacks
	mRigidbody.getBody()->SetUserData(this);
}

void LevelBoundryCollider::updateEntity(sf::Time dt) 
{
	
}
		
void LevelBoundryCollider::drawEntity(sf::RenderTarget& target, sf::RenderStates states) const
{	
	// Rigidbody debug draw
	if (Globals::DEBUG_MODE)
		mRigidbody.drawDebug(target, states);
}