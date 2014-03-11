#include "PC.h"
#include <iostream>

#include "Camera.h"

PC::PC(sf::Vector2f position)
	: mAudioLoggSound(Loading::getSound("Room 2/AudioLogg.wav"), true),
	mButton1(Loading::getSound("Room 2/Tangentbord/Tangent1.wav"), true),
	mButton2(Loading::getSound("Room 2/Tangentbord/Tangent2.wav"), true),
	mButton3(Loading::getSound("Room 2/Tangentbord/Tangent3.wav"), true),
	mButton4(Loading::getSound("Room 2/Tangentbord/Tangent4.wav"), true),
	mButton5(Loading::getSound("Room 2/Tangentbord/TangentSpacebar.wav"), true),
	mBlip1(Loading::getSound("Room 2/Datorblips/Blip1.wav"), true),
	mBlip2(Loading::getSound("Room 2/Datorblips/Blip2.wav"), true),
	mComputerOnSprite(Loading::getTexture("Room 2/datorskarm_gron_scale.png")),
	mComputerOffSprite(Loading::getTexture("Room 2/PC_Screen_SCALE.png")),
	sucu(Loading::getTexture("Room 2/SuCu_computereye_spritesheet.png"), 600, 361, 1, 9, 100),
	mKeyboardHintSprite(Loading::getTexture("Room 2/use_the_keyboard.png"))
{
	mID = "PC";
	mPosition = position;
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
	mSucuText = mTextEntered;

	mSucuText.setPosition(mTextPosition.x, mTextPosition.y + 240);
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
	mAnimation = false;
	mSucu = false;
	mKeyboardHint = false;
	//counter
	mInvalidCounter = 0;

	//animation
	sucu.mLoopOnce = true;
	sucu.setPosition(position);
	mSucuMessage = "Hello object Zid. I have monitored your\nprogress and believe we can help each other.\nYou may visit me in the server room at your\nearliest convinience.\n\n 1. Continue";
	mMessage = "";
	mMaxChar = mSucuMessage.size() - 1;
	currentChar = 0;

	//Keyboard Hint
	mKeyboardHintSprite.setPosition(position.x + 615, position.y - 20);
}


PC::~PC()
{
}

void PC::sendMessage(Entity* entity, std::string message)
{
	if(message == "in_PC_Zone")
	{
		mCamera = true;
		mKeyboardHint = true;
	}
	if(message == "out_of_PC_Zone")
	{
		mCamera = false;
		mKeyboardHint = false;
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
		mBlip1.play();
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
		if(mShuttingDown == true)	// && mShuttingDownClock.getElapsedTime().asSeconds() > 3)
		{
			//Display shutting down text before sucu animation
			if(mShuttingDownClock.getElapsedTime().asSeconds() > 3)
			{
				mAnimation = true;
			}

			if(mAnimation == true)
			{
				if(sucu.mLoopOnce == true)
				{
					sucu.oneLoop();
				}
				mSprite = sucu.getCurrentSprite();
				mSprite.setOrigin(0, 0);
			}

			if(sucu.endOfAnimation() == true)
			{
				mSucu = true;
				if(mMessageClock.getElapsedTime().asMilliseconds() > 20)
				{
					if(currentChar <= mMaxChar)
					{
						mMessage += mSucuMessage.at(currentChar);
						currentChar++;
					}
					mSucuText.setString(mMessage);
					mMessageClock.restart();
				}
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
			{
				mMenu = false;
				mLoggin = true;
				mOff = true;
				mSucu = false;
				mAnimation = false;
				mBlip2.play();
				
			}
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
		if(mMenu == true && mShuttingDown == false && mBulletin == false && mAudioLogg == false && mAnimation == false)
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
		if(mShuttingDown == true && mAnimation == false)
		{
			target.draw(mShuttingDownText, states);
		}
		if(mAnimation == true)
		{
			target.draw(mSprite, states);
		}
		if(mSucu == true)
		{
			target.draw(mSucuText, states);
		}


	}
	else
	{
		target.draw(mComputerOffSprite, states);
	}

	if(mKeyboardHint == true)
	{
		target.draw(mKeyboardHintSprite);
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
