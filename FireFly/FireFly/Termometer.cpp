#include "Termometer.h"
#include "EntityList.h"

const int MAX_TEMP = 3;
const float SCALE = 0.7f;

Termometer::Termometer(sf::Vector2f position)
	: mTermoSprites()
	, mCurrentSprite(3)
	, mBoilerOn(true)
	, mCeilingFanOff(true)
	, mComputerOn(true)
{

	sf::Sprite cold = sf::Sprite(Loading::getTexture("Room 2/termometer_cold.png"));
	sf::Sprite med = sf::Sprite(Loading::getTexture("Room 2/termometer_med.png"));
	sf::Sprite warm = sf::Sprite(Loading::getTexture("Room 2/termometer_warm.png"));
	sf::Sprite hot = sf::Sprite(Loading::getTexture("Room 2/termometer_hot.png"));
	mTermoSprites.push_back(cold);
	mTermoSprites.push_back(med);
	mTermoSprites.push_back(warm);
	mTermoSprites.push_back(hot);

	for (sf::Sprite& sprite : mTermoSprites)
	{
		// Sätter origin för spriten till mitten
		sf::FloatRect bounds = sprite.getLocalBounds();
		sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

		sprite.setScale(SCALE, SCALE);
	}	

	mID = "Termometer";
	setPosition(position);
}

void Termometer::updateEntity(sf::Time dt)
{
	mCurrentSprite = 0;
	mCurrentSprite += mBoilerOn ? 1 : 0;
	mCurrentSprite += mCeilingFanOff ? 1 : 0;
	mCurrentSprite += mComputerOn ? 1 : 0;
}

void Termometer::sendMessage(Entity* sender ,string message)
{
	if (message == "BoilerOn")
		mBoilerOn = true;
	else if (message == "BoilerOff")
		mBoilerOn = false;
	else if (message == "CeilingFanOn")
		mCeilingFanOff = false;
	else if (message == "CeilingFanOff")
		mCeilingFanOff = true;
	else if (message == "ComputerOn")
		mComputerOn = true;
	else if (message == "ComputerOff")
		mComputerOn = false;
	
	if (!mBoilerOn && !mCeilingFanOff && !mComputerOn)
		EntityList::getEntityList().getEntity("Room2_AC")->sendMessage(this, "TurnOff");
	else
		EntityList::getEntityList().getEntity("Room2_AC")->sendMessage(this, "TurnOn");
}

void Termometer::drawEntity(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
		
	target.draw(mTermoSprites.at(mCurrentSprite), states);
}