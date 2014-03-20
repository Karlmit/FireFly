#include "ServerRoomEyeScreen.h"

const unsigned FRAMES_PER_SECOND = 24;
const unsigned TIME_PER_FRAME = unsigned( 1000 / FRAMES_PER_SECOND );



ServerRoomEyeScreen::ServerRoomEyeScreen( sf::Vector2f position)
	: mSprite()
	, mOpenAnimation(Loading::getTexture("Room 3/SuCu_screen_spritesheet.png"), 657, 649, 1, 12, TIME_PER_FRAME)
	, mGlitchAnimation(Loading::getTexture("Room 3/SuCu_kortslutning 1_spritesheet.png"), 662, 649, 1, 11, TIME_PER_FRAME)
	, mCloseAnimation(Loading::getTexture("Room 3/SuCu_kortslutning 2_spritesheet.png"), 662, 649, 1, 7, TIME_PER_FRAME)
	, mState(State::Inactive)
{
	setPosition(position);	
	mID = "ServerRoomEyeScreen";
}

void ServerRoomEyeScreen::start()
{
	
}


void ServerRoomEyeScreen::updateEntity(sf::Time dt)
{
	switch (mState)
	{
	case ServerRoomEyeScreen::State::Inactive:
		// Nothing
		break;
	case ServerRoomEyeScreen::State::Open:
		mOpenAnimation.updatePlay();
		break;
	case ServerRoomEyeScreen::State::Glitch:
		mGlitchAnimation.updateAnimation();
		break;
	case ServerRoomEyeScreen::State::Close:
		mCloseAnimation.updatePlay();
		break;
	default:
		break;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		sendMessage(this, "Glitch");
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		sendMessage(this, "ScreenOff");
	
}

void ServerRoomEyeScreen::sendMessage(Entity* sender ,string message)
{
	if (message == "ScreenOn" && mState == State::Inactive)
	{
		mOpenAnimation.play(true);
		mState = State::Open;
	}
	else if (message == "Glitch" && mState == State::Open)
	{
		mState = State::Glitch;
	}
	else if (message == "ScreenOff" && mState == State::Glitch)
	{
		mCloseAnimation.play(true);
		mState = State::Close;
	}
}

void ServerRoomEyeScreen::drawEntity(sf::RenderTarget& target, sf::RenderStates states) const
{	
	states.transform *= getTransform();	
	
	switch (mState)
	{
	case ServerRoomEyeScreen::State::Inactive:
		// Nothing
		break;
	case ServerRoomEyeScreen::State::Open:
		target.draw(mOpenAnimation.getCurrentSprite(), states);
		break;
	case ServerRoomEyeScreen::State::Glitch:
		target.draw(mGlitchAnimation.getCurrentSprite(), states);
		break;
	case ServerRoomEyeScreen::State::Close:
		target.draw(mCloseAnimation.getCurrentSprite(), states);
		break;
	default:
		break;
	}
		
}