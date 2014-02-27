#include "PC.h"
#include <iostream>

PC::PC(sf::Vector2f position)
{
	mID = "PC";
	mScreen.setSize(sf::Vector2f(595, 360));
	mScreen.setFillColor(sf::Color::Black);
	mScreen.setPosition(position);

	mFont.loadFromFile("Resources/PressStart2P.ttf");
	
	mTextEntered.setFont(mFont);
	mTextEntered.setCharacterSize(15);
	mTextEntered.setColor(sf::Color::Green);
	mPassword = mTextEntered;
	mPassInvalid = mTextEntered;
	mMenuText = mTextEntered;
	mHintText = mTextEntered;
	mBulletinText = mTextEntered;

	mBulletinText.setPosition(position.x + 70, position.y + 70);
	mBulletinText.setString("Bulletin: Ant problem!\nAnt problem in the boiler room!\nWe have informed the janitor\nabout this, and she said\nthat she wont have time to\ndeal with it until nex t week.\nUntil then she told us not to\nleave any food or sweets around,\nto keep the ants from spreading\nto other rooms.\n//The dean");
	mHintText.setPosition(position.x + 70, position.y + 200);
	mHintText.setString("Help question: What is the most\nimportant thing in my life?");
	mMenuText.setPosition(position.x + 100, position.y + 70);
	mMenuText.setString("1. Access Audiolog, 9/9 \n\n2. Bulletin: Ant problem! \n\n3. Shut down");
	mPassInvalid.setPosition(position.x + 70, position.y + 160);
	mPassInvalid.setString("Password invalid");
	mPassword.setPosition(position.x + 70, position.y + 140);
	mPassword.setString("Password: ");
	mTextEntered.setPosition(position.x + 210, position.y + 140);

	mWelcomeText = mPassword;
	mWelcomeText.setString("Welcome dr. Locke");

	//meny bools
	mLoggin = true;
	mInvalid = false;
	mMenu = false;
	mHint = false;
	mWelcome = false;
	mBulletin = false;

	//counter
	mInvalidCounter = 0;
}


PC::~PC()
{
}

void PC::sendMessage(Entity* entity, std::string message)
{
	
}

void PC::sendSfString(Entity* entity, sf::String message)
{
	if(message.getSize() <= 5)
	{
		msfString = message;
	}
}

void PC::loggin()
{
	mTextEntered.setString(msfString);

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && msfString == "laura" && mLoggin == true)
	{
		mLoggin = false;
		mInvalid = false;
		mHint = false;
		mWelcome = true;
		mWelcomeClock.restart();
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && mLoggin == true)
	{
		mInvalidCounter++;
		if(mInvalidCounter > 5)
		{
			mHint = true;
		}

		mInvalid = true;
	}



}

void PC::menu()
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
	{

	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
	{
		mBulletin = true;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
	{
		mMenu = false;
		mLoggin = true;
	}

}


void PC::updateEntity(sf::Time dt)
{
	if(mWelcomeClock.getElapsedTime().asSeconds() > 3 && mLoggin == false)
	{
		mMenu = true;
		mWelcome = false;
	}

	if(mLoggin == true)
	{
		loggin();
	}
	else if(mMenu == true)
	{
		menu();
	}



}

void PC::drawEntity(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(mScreen, states);

	if(mLoggin == true)
	{
		target.draw(mTextEntered, states);
		target.draw(mPassword, states);
	}
	if(mInvalid == true)
	{
		target.draw(mPassInvalid, states);
	}
	if(mMenu == true && mBulletin == false)
	{
		target.draw(mMenuText, states);
	}
	if(mHint == true)
	{
		target.draw(mHintText, states);
	}
	if(mWelcome == true)
	{
		target.draw(mWelcomeText, states);
	}
	if(mBulletin == true)
	{
		target.draw(mBulletinText, states);
	}




	if(Globals::DEBUG_MODE)
	{

	}
}

void PC::getTextEntered(std::string text)
{
	mTextEntered.setString(text);
}
