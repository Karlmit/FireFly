#pragma once
#include "Entity.h"
#include "Animation.h"
#include "EntityList.h"
#include "Audio.h"
#include "EntitySprite.h"
#include "PC.h"
#include <iostream>
#include "Log.h"

#include <sstream>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML\Graphics\RectangleShape.hpp>
#include <SFML\Graphics\Font.hpp>

class PC : public Entity
{
public:
	PC(sf::Vector2f position);
	~PC();
	virtual void sendMessage(Entity* entity, std::string message);
	virtual void sendSfString(Entity* entity, sf::String message);
	void getTextEntered(std::string text);
	bool newPC();
private:
	virtual void updateEntity(sf::Time dt);	
	virtual void drawEntity(sf::RenderTarget& target, sf::RenderStates states) const;
	void playButtonSound();
	void loggin();
	void menu();

	sf::Vector2f mPosition;
	sf::Vector2f mTextPosition;
	//Sprites
	sf::Sprite mComputerOnSprite;
	sf::Sprite mComputerOffSprite;
	//Entities
	Entity *termometer;
	Entity *mEntitySprite;

	//Inside Zone check
	bool inPcZone;

	sf::RectangleShape mScreen;
	sf::String msfString;
	sf::Font mFont;
	sf::Text mTextEntered;
	sf::Text mPassword;
	sf::Text mPassInvalid;
	sf::Text mMenuText;
	sf::Text mBulletinText;
	sf::Text mHintText;
	sf::Text mWelcomeText;
	sf::Text mAudioLoggText;
	sf::Text mShuttingDownText;
	sf::Text mSucuText;
	std::string mSucuMessage;
	std::string mMessage;
	int currentChar;
	int mMaxChar;

	//meny bools
	bool mHint;
	bool mLoggin;
	bool mInvalid;
	bool mMenu;
	bool mWelcome;
	bool mBulletin;
	bool mAudioLogg;
	bool mCamera;
	bool mOff;
	bool mShuttingDown;
	bool mNewPC;
	bool mAnimation;
	bool mSucu;
	//invalid counter
	int mInvalidCounter;
	
	//Clocks and timers
	sf::Clock mWelcomeClock;
	sf::Time mAudioLoggTime;
	sf::Clock mButtonClock;
	sf::Clock mShuttingDownClock;
	sf::Clock mMessageClock;

	//sounds
	Audio mAudioLoggSound;
	Audio mButton1;
	Audio mButton2;
	Audio mButton3;
	Audio mButton4;
	Audio mButton5;
	Audio mBlip1;
	Audio mPCOn;
	Audio mPCOff;
	
	//string stream
	std::ostringstream oss;
	//animation
	Animation sucu;
	sf::Sprite mSprite;
};