#include "SugarBowlTop.h"

SugarBowlTop::SugarBowlTop(string texture, sf::Vector2f position, bool dynamic)
	: mSprite(Loading::getTexture("Room 2/sugarbowltop_scale.png", true)),
	mRigidbody()
{
	sf::FloatRect bounds = mSprite.getLocalBounds();

	
	std::vector<sf::FloatRect> rects;
	rects.push_back(bounds);

	mStartPosition = position;
	mRigidbody.setPosition(position);
	mRigidbody.AddDynRectBody(rects, position, 5, true);
	mRigidbody.getBody()->SetFixedRotation(true);

	// Adds itself to body data for collision callbacks
	mRigidbody.getBody()->SetUserData(this);
}


SugarBowlTop::~SugarBowlTop(void)
{
}


void SugarBowlTop::updateEntity(sf::Time dt)
{
	//hinders lid from falling into the bowl
	if(getPosition().x > mStartPosition.x + 65 || getPosition().x < mStartPosition.x - 65)
	{
		mRigidbody.getBody()->SetFixedRotation(false);
	}
	else
	{
		mRigidbody.getBody()->SetFixedRotation(true);
	}



	mRigidbody.update();
	setRotation(mRigidbody.getRotation());
	setPosition(mRigidbody.getPosition());

}

void SugarBowlTop::drawEntity(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(mSprite, states);

		// Rigidbody debug draw
	if (Globals::DEBUG_MODE)
		mRigidbody.drawDebug(target, states);
}
