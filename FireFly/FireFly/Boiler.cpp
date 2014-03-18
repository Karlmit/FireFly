#include "Boiler.h"
#include "Utility.h"
#include "EntityList.h"

const float SHAKE_DISTANCE = 2.f;
const float DEC_SPEED_SHAKE = 1.f;
const float DELAY_UNTIL_DEACTIVATE = 3.f;


Boiler::Boiler(string textureID ,sf::Vector2f position) 
: mSprite(Loading::getTexture(textureID))
, mPos()
, mActive(true)
, mShakiness(SHAKE_DISTANCE)
, mSuccess(Loading::getSound("Room 2/Datorblips/Blip1.wav"), true)
{
	// Sätter origin för spriten till mitten
	sf::FloatRect bounds = mSprite.getLocalBounds();
	mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

	setPosition(position);
	mPos = position;
	mID = "Boiler";
}

void Boiler::updateEntity(sf::Time dt) 
{
	if (!mActive && mDelayTimer.getElapsedTime().asSeconds() > DELAY_UNTIL_DEACTIVATE)
		mShakiness = max(0.f, mShakiness - dt.asSeconds() * DEC_SPEED_SHAKE);


	if (mShakiness != 0)
	{
		sf::Vector2f newPosition(mShakiness, 0);
		newPosition.rotateBy(Util::randFloat(0, 360));
		newPosition = newPosition + mPos;
		setPosition(newPosition);
	}
	else
		setPosition(mPos);

	
}
		
void Boiler::drawEntity(sf::RenderTarget& target, sf::RenderStates states) const
{	
	states.transform *= getTransform();
	target.draw(mSprite, states);
}

void Boiler::sendMessage(Entity* sender, string message)
{
	if (message == "Ants!" && mActive)
	{
		mActive = false;
		mDelayTimer.restart();
		mSuccess.play();
		EntityList::getEntityList().getEntity("Termometer")->sendMessage(this, "BoilerOff");
	}
}