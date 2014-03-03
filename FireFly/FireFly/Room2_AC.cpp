#include "Room2_AC.h"
#include "EntityList.h"


const unsigned FRAMES_PER_SECOND = 60;
const unsigned TIME_PER_FRAME = unsigned( 1000 / FRAMES_PER_SECOND );


Room2_AC::Room2_AC(string texture, sf::Vector2f position)
	: mSprite(Loading::getTexture("Room 2/ventilflakt_scale.png"))
	, mIsOn(true)
	, mFanAnimation(Loading::getTexture(texture), 287, 449, 1, 8, TIME_PER_FRAME)
{
	// Sätter origin för spriten till mitten
	sf::FloatRect bounds = mSprite.getLocalBounds();
	mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

	setPosition(position);
	mID = "Room2_AC";
}

void Room2_AC::start()
{
	mForceZone = EntityList::getEntityList().getEntity("ACForceZone");
}


void Room2_AC::updateEntity(sf::Time dt)
{
	// Temp using keyboard to turn off AC-fan
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		sendMessage(this, "TurnOn");
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
		sendMessage(this, "TurnOff");


	if (!mIsOn)
		return;

	mFanAnimation.updateAnimation();

	
}

void Room2_AC::sendMessage(Entity* sender ,string message)
{
	if (message == "TurnOff")
	{
		mIsOn = false;
		mForceZone->sendMessage(this, "Deactivate");
	}
	else if (message == "TurnOn")
	{
		mIsOn = true;
		mForceZone->sendMessage(this, "Activate");
	}
}

void Room2_AC::drawEntity(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	if (mIsOn)	
		target.draw(mFanAnimation.getCurrentSprite(), states);
	else
		target.draw(mSprite, states);
}