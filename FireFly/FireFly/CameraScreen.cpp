#include "CameraScreen.h"

const unsigned FRAMES_PER_SECOND = 30;
const unsigned TIME_PER_FRAME = unsigned( 1000 / FRAMES_PER_SECOND );

const unsigned ACTIVE_TIME = 1000;

CameraScreen::CameraScreen(string openTexture, string activeTexture, sf::Vector2f position)
	: mSprite()
	, mOpenScreenAnimation(Loading::getTexture("Room 3/SuCU_camerascreen_spritesheet.png"), 485, 679, 1, 5, TIME_PER_FRAME)
	, mOpenAnimation(Loading::getTexture(openTexture), 476, 676, 1, 4, TIME_PER_FRAME)
	, mActiveAnimation(Loading::getTexture(activeTexture), 476, 676, 1, 3, ACTIVE_TIME)
	, mNoActiveAnimation(false)
	, mState(State::Inactive)
{
	setPosition(position + sf::Vector2f(476/2, 676/2));
	
	if (activeTexture == "Room 3/sucu_camera_office.png" || activeTexture == "Room 3/sucu_camera_cafe_not active.png")
		mNoActiveAnimation = true;
}

void CameraScreen::start()
{
	
}


void CameraScreen::updateEntity(sf::Time dt)
{
	
	switch (mState)
	{
	case CameraScreen::State::Inactive:
		// Do nothing
		break;

	case CameraScreen::State::Open1:
		if (mOpenScreenAnimation.updatePlay())
		{
			mState = State::Open2;
			mOpenAnimation.play(true);
		}
		break;

	case CameraScreen::State::Open2:
		if (mOpenAnimation.updatePlay())
			mState = State::Active;
		break;

	case CameraScreen::State::Active:
		if (!mNoActiveAnimation)
			mActiveAnimation.updateAnimation();
		break;

	case CameraScreen::State::Glitch:
		break;

	case CameraScreen::State::Close:
		break;

	default:
		break;
	}
	


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
	{
		mOpenScreenAnimation.resetPlayAnimation();
		mOpenAnimation.resetPlayAnimation();
		mState = State::Inactive;
	}
	
}

void CameraScreen::sendMessage(Entity* sender ,string message)
{
	if (message == "ScreenOn" && mState == State::Inactive)
	{
		mOpenScreenAnimation.play(true);
		mState = State::Open1;
	}
}

void CameraScreen::drawEntity(sf::RenderTarget& target, sf::RenderStates states) const
{	
	states.transform *= getTransform();	
	
	target.draw(mOpenScreenAnimation.getCurrentSprite(), states);

	switch (mState)
	{
	case CameraScreen::State::Inactive:
		break;
	case CameraScreen::State::Open1:
		break;
	case CameraScreen::State::Open2:
		target.draw(mOpenAnimation.getCurrentSprite(), states);
		break;
	case CameraScreen::State::Active:
		target.draw(mActiveAnimation.getCurrentSprite(), states);
		break;
	case CameraScreen::State::Glitch:
		break;
	case CameraScreen::State::Close:
		break;
	default:
		break;
	}
		
}