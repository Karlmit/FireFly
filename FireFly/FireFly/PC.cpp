#include "PC.h"
#include <iostream>

PC::PC(sf::Vector2f position)
	: mAudioLoggSound(Loading::getSound("canary.wav"), true)
{
	mID = "PC";
	mScreen.setSize(sf::Vector2f(595, 360));
	mScreen.setFillColor(sf::Color::Black);
	mScreen.setPosition(position);
	mTextPosition.x = position.x + 15;
	mTextPosition.y = position.y + 25;

	mFont.loadFromFile("Resources/PressStart2P.ttf");
	
	mTextEntered.setFont(mFont);
	mTextEntered.setCharacterSize(13);
	mTextEntered.setColor(sf::Color::Cyan);
	mPassword = mTextEntered;
	mPassInvalid = mTextEntered;
	mMenuText = mTextEntered;
	mHintText = mTextEntered;
	mBulletinText = mTextEntered;
	mAudioLoggText = mTextEntered;

	mAudioLoggText.setPosition(mTextPosition);
	mBulletinText.setPosition(mTextPosition.x, mTextPosition.y);
	mBulletinText.setString("Bulletin: Ant problem!\n\nAnt problem in the boiler room!\nWe have informed the janitor\nabout this, and she said that\nshe wont have time to deal\nwith it until next week.\nUntil then she told us not to \nleave any food or sweets around,\nto keep the ants from spreading\nto other rooms.\n//The dean\n\n\n1. Back");
	mHintText.setPosition(mTextPosition.x, mTextPosition.y + 40);
	mHintText.setString("Help question: What is the most\nimportant thing in my life?");
	mMenuText.setPosition(mTextPosition.x, mTextPosition.y);
	mMenuText.setString("1. Access Audiolog, 9/9 \n\n2. Bulletin: Ant problem! \n\n3. Shut down");
	mPassInvalid.setPosition(mTextPosition.x, mTextPosition.y + 20);
	mPassInvalid.setString("Password invalid");
	mPassword.setPosition(mTextPosition.x, mTextPosition.y);
	mPassword.setString("Password: ");
	mTextEntered.setPosition(mTextPosition.x + 120, mTextPosition.y);

	mWelcomeText = mPassword;
	mWelcomeText.setString("Welcome dr. Locke");

	//meny bools
	mLoggin = true;
	mInvalid = false;
	mMenu = false;
	mHint = false;
	mWelcome = false;
	mBulletin = false;
	mAudioLogg = false;

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
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) && mMenu == true)
	{
		mAudioLogg = true;
		mAudioLoggSound.play();
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

	//INSIDE BULLETIN
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) && mBulletin == true)
	{
		mBulletin = false;
		mMenu = true;
	}
	//INSIDE AUDIOLOGG
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) && mAudioLogg == true)
	{
		mAudioLogg = false;
		mMenu = true;
	}


}


void PC::updateEntity(sf::Time dt)
{
	//oss.clear();
	//oss << mAudioLoggSound.getSound()->getPlayingOffset().asSeconds();
	//std::string AudioLogg = to_string(mAudioLoggSound.getSound()->getPlayingOffset().asSeconds());
	std::stringstream ac;
	ac.precision(2);
	ac << "Playing Audiologg 9/9: ";
	ac << fixed << mAudioLoggSound.getSound()->getPlayingOffset().asSeconds();
	ac << " / " << mAudioLoggSound.getSound()->getBuffer()->getDuration().asSeconds();
	ac << "\n\n\n 1. back";
	mAudioLoggText.setString(ac.str());

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
	if(mMenu == true && mBulletin == false && mAudioLogg == false)
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
	if(mAudioLogg == true)
	{
		target.draw(mAudioLoggText, states);
	}





	if(Globals::DEBUG_MODE)
	{

	}
}

void PC::getTextEntered(std::string text)
{
	mTextEntered.setString(text);
}
