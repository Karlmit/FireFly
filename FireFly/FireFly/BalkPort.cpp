#include "BalkPort.h"


BalkPort::BalkPort(string texture, sf::Vector2f position, float width, float height)
	: mRigidbody()
, mSprite(Loading::getTexture(texture, true))
{
	mID = "BalkPort";
	mActivate = false;
	mFloatRect.height = height;
	mFloatRect.width = width;

	// Sätter origin för spriten till mitten
	sf::FloatRect bounds = mSprite.getLocalBounds();
	//mSprite.setOrigin(bounds.width , bounds.height);
	
	std::vector<sf::FloatRect> rects;
	//rects
	rects.push_back(sf::FloatRect(mSprite.getLocalBounds().left, mSprite.getLocalBounds().top, bounds.width, bounds.height));
	mRigidbody.AddDynRectBody(rects, position, 1.f, true);
	mRigidbody.getBody()->SetFixedRotation(true);
	mRigidbody.getBody()->SetUserData(this);
	setPosition(position);
}


void BalkPort::sendMessage(Entity* entity, std::string message)
{
	if(message == "Activate")
	{
		mActivate = true;
		Entity* balkportgate = EntityList::getEntityList().getEntity("BalkPortGate");
		if(balkportgate != nullptr)
		balkportgate->killEntity();
	}

}

void BalkPort::updateEntity(sf::Time dt)
{
	//if(mActivate == true)
	//{
		mRigidbody.update();
		setPosition(mRigidbody.getPosition());
	//}


}

void BalkPort::drawEntity(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(mSprite, states);

	// Rigidbody debug draw
	if (Globals::DEBUG_MODE)
		mRigidbody.drawDebug(target, states);
}

