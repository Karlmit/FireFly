#include "PC.h"
#include <iostream>

PC::PC(sf::Vector2f position)
{
	mID = "PC";
	mScreen.setSize(sf::Vector2f(595, 360));
	mScreen.setFillColor(sf::Color::Black);
	mScreen.setPosition(position);

	mFont.loadFromFile("Resources/PressStart2P.ttf");
	
	mText.setPosition(position.x + 190, position.y + 180);
	mText.setFont(mFont);
	mText.setCharacterSize(15);
	mText.setColor(sf::Color::Green);
	mText.setString(sf::String("Password:"));
}


PC::~PC()
{
}

void PC::sendMessage(Entity* entity, std::string message)
{
	
}

void PC::sendSfString(Entity* entity, sf::String message)
{
	msfString = message;
}


void PC::updateEntity(sf::Time dt)
{
	mText.setString(msfString);
}

void PC::drawEntity(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(mScreen, states);
	target.draw(mText,states);

	if(Globals::DEBUG_MODE)
	{

	}

	//mRigidbody.drawDebug(target, states);
}

void PC::getTextEntered(std::string text)
{
	mText.setString(text);
}
