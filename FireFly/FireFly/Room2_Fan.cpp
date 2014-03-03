#include "Room2_Fan.h"


const unsigned FRAMES_PER_SECOND = 60;
const unsigned TIME_PER_FRAME = unsigned( 1000 / FRAMES_PER_SECOND );


Room2_Fan::Room2_Fan(string texture, sf::Vector2f position)
	: mSprite(Loading::getTexture("Room 2/takflakt_scale.png"))
	, mIsOn(true)
	, mFanAnimation(Loading::getTexture(texture), 1644, 320, 1, 4, TIME_PER_FRAME)
{
	// Sätter origin för spriten till mitten
	sf::FloatRect bounds = mSprite.getLocalBounds();
	mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

	setPosition(position);
	mID = "Room2_Fan";
}


void Room2_Fan::updateEntity(sf::Time dt)
{
	if (!mIsOn)
		return;


	mFanAnimation.updateAnimation();
}

void Room2_Fan::sendMessage(Entity* sender ,string message)
{
	if (message == "TurnOff")
		mIsOn = false;
	else if (message == "TurnOn")
		mIsOn = true;
}

void Room2_Fan::drawEntity(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	if (mIsOn)	
		target.draw(mFanAnimation.getCurrentSprite(), states);
	else
		target.draw(mSprite, states);
}