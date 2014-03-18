#include "FallingSprite.h"
#include <iostream>

FallingSprite::FallingSprite(string fallingTextureID, string endTextureID, sf::Vector2f startPosition, sf::Vector2f endPosition, std::string id, float scale) 
: mSprite(Loading::getTexture(fallingTextureID))
, mEndSprite(Loading::getTexture(endTextureID))
, mActivate(true)
, mEndPosition(endPosition)
, mFallingComplete(false)
{
	mID = id;
	mSprite.setScale(scale, scale);
	mEndSprite.setScale(scale, scale);
	// Sätter origin för spriten till mitten
	sf::FloatRect bounds = mEndSprite.getLocalBounds();
	mSpriteHeight = bounds.height * scale;
	std::vector<sf::FloatRect> rects;
	sf::FloatRect startRect(bounds.left*scale, bounds.top*scale, bounds.width*scale, bounds.height*scale);
	mRigidbody.AddTriggerBoxBody(startRect, true, startPosition);
	mRigidbody.getBody()->SetFixedRotation(true);
	mRigidbody.getBody()->SetUserData(this);
	mRigidbody.getBody()->SetBullet(true);
	setPosition(startPosition);
}

void FallingSprite::updateEntity(sf::Time dt) 
{
	if(getPosition().y <= mEndPosition.y - mSpriteHeight - 3)
	{
		mRigidbody.update();
		setPosition(mRigidbody.getPosition());
	}
	else
	{
		mRigidbody.getBody()->SetType(b2_staticBody);
		mFallingComplete = true;
	}



}
		
void FallingSprite::drawEntity(sf::RenderTarget& target, sf::RenderStates states) const
{	
	if(mActivate == true && mFallingComplete == false)
	{
		states.transform *= getTransform();
		target.draw(mSprite, states);
	}
	if(mFallingComplete == true)
	{
		states.transform *= getTransform();
		target.draw(mEndSprite, states);
	}

		// Rigidbody debug draw
	if (Globals::DEBUG_MODE)
		mRigidbody.drawDebug(target, states);

}

void FallingSprite::sendMessage(Entity* entity, std::string message)
{
	if(message == "Activate")
	{
		mActivate = true;
	}
	if(message == "Deactivate")
	{
		mActivate = false;
	}


}
