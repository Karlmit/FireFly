#include "PC.h"
#include <iostream>

#include "Camera.h"

PC::PC(sf::Vector2f position)
	: mAudioLoggSound(Loading::getSound("canary.wav"), true),
	mButton1(Loading::getSound("Room 2/Tangentbord/Tangent1.wav"), true),
	mButton2(Loading::getSound("Room 2/Tangentbord/Tangent2.wav"), true),
	mButton3(Loading::getSound("Room 2/Tangentbord/Tangent3.wav"), true),
	mButton4(Loading::getSound("Room 2/Tangentbord/Tangent4.wav"), true),
	mButton5(Loading::getSound("Room 2/Tangentbord/TangentSpacebar.wav"), true),
	mComputerOnSprite(Loading::getTexture("Room 2/datorskarm_gron_scale.png")),
	mComputerOffSprite(Loading::getTexture("Room 2/PC_Screen_SCALE.png"))
{
	mID = "PC";
	mComputerOnSprite.setPosition(2592, 935);
	mComputerOffSprite.setPosition(2592, 935);
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
	mShuttingDownText = mTextEntered;

	mShuttingDownText.setPosition(mTextPosition);
	mShuttingDownText.setString("Shutting Down...");
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
	mCamera = false;
	mOff = false;
	mShuttingDown = false;
	mNewPC = true;
	//counter
	mInvalidCounter = 0;
}


PC::~PC()
{
}

void PC::sendMessage(Entity* entity, std::string message)
{
	if(message == "in_PC_Zone")
	{
		mCamera = true;
	}
	if(message == "out_of_PC_Zone")
	{
		mCamera = false;
	}


}

void PC::sendSfString(Entity* entity, sf::String message)
{
	playButtonSound();
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
	if(mButtonClock.getElapsedTime().asMilliseconds() > 200)
	{
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) && mMenu == true && mBulletin == false && mShuttingDown == false)
		{
			mAudioLogg = !mAudioLogg;
			if(mAudioLogg == true)
			{
			mAudioLoggSound.play();
			}
			mButtonClock.restart();
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) && mBulletin == false && mAudioLogg == false && mShuttingDown == false)
		{
			mBulletin = true;
			mButtonClock.restart();
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3) && mBulletin == false && mAudioLogg == false && mShuttingDown == false)
		{
			mShuttingDown = true;
			mShuttingDownClock.restart();
			mButtonClock.restart();
		}
		}
		if(mButtonClock.getElapsedTime().asMilliseconds() > 200)
		{
		//INSIDE BULLETIN
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) && mBulletin == true)
		{
			mBulletin = false;
			mMenu = true;
			mButtonClock.restart();
		}
	}
		if(mShuttingDown == true && mShuttingDownClock.getElapsedTime().asSeconds() > 3)
		{
			mMenu = false;
			mLoggin = true;
			mOff = true;
		}


}


void PC::updateEntity(sf::Time dt)
{
	std::stringstream ac;
	ac.precision(2);
	ac << "Playing Audiologg 9/9... ";
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

	//Camera
	if(mCamera == true)
	{
		Camera::currentCamera().setTargetPosition(sf::Vector2f( mScreen.getPosition().x + mScreen.getSize().x/2, mScreen.getPosition().y + mScreen.getSize().y/2));
		Camera::currentCamera().setZoom(0.8f);
	}

	termometer = EntityList::getEntityList().getEntity("Termometer");
	if(mOff == true)
	{
		termometer->sendMessage(termometer, "ComputerOff");
	}
	else
	{
		termometer->sendMessage(termometer, "ComputerOn");
	}


	mNewPC = false; 

}

void PC::drawEntity(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	if(mOff == false)
	{
		target.draw(mComputerOnSprite, states);

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
		if(mMenu == true && mShuttingDown == false && mBulletin == false && mAudioLogg == false)
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
		if(mShuttingDown == true)
		{
			target.draw(mShuttingDownText, states);
		}

	}
	else
	{
		target.draw(mComputerOffSprite, states);
	}





	if(Globals::DEBUG_MODE)
	{

	}
}

void PC::getTextEntered(std::string text)
{
	mTextEntered.setString(text);
}

bool PC::newPC()
{
	return mNewPC;
}

void PC::playButtonSound()
{
	int random = rand()%5;
	if(random == 0)
	{
		mButton1.play();
	}
	else if(random == 1)
	{
		mButton2.play();
	}
	else if(random == 2)
	{
		mButton3.play();
	}
	else if(random == 3)
	{
		mButton4.play();
	}
	else if(random == 4)
	{
		mButton5.play();
	}


}
