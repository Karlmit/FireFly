#include "CameraScreen.h"

const unsigned FRAMES_PER_SECOND = 30;
const unsigned TIME_PER_FRAME = unsigned( 1000 / FRAMES_PER_SECOND );

const unsigned ACTIVE_TIME = 700;

CameraScreen::CameraScreen(string openTexture, string activeTexture, sf::Vector2f position)
	: mSprite()
	, mOpenScreenAnimation(Loading::getTexture("Room 3/SuCU_camerascreen_spritesheet.png"), 485, 679, 1, 5, TIME_PER_FRAME)
	, mOpenAnimation(Loading::getTexture(openTexture), 476, 676, 1, 4, TIME_PER_FRAME)
	, mActiveAnimation(Loading::getTexture(activeTexture), 476, 676, 1, 3, ACTIVE_TIME)
	, mOpenScreenDone(false)
	, mOpenDone(false)
	, mTurnOn(false)
{
	setPosition(position + sf::Vector2f(476/2, 676/2));
}

void CameraScreen::start()
{
	
}


void CameraScreen::updateEntity(sf::Time dt)
{
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::J))
		sendMessage(this, "TurnOn");
	
	if (mOpenScreenDone == false)
	{
		mOpenScreenDone = mOpenScreenAnimation.updatePlay();

		
	}
	else if (mOpenDone == false)
	{
		mOpenDone = mOpenAnimation.updatePlay();
		mOpenAnimation.play(true);
	}
	else
	{
		mActiveAnimation.updateAnimation();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
	{
		mOpenScreenAnimation.resetPlayAnimation();
		mOpenAnimation.resetPlayAnimation();
		mOpenScreenDone = false;
		mOpenDone = false;
		mTurnOn = false;
	}
	
}

void CameraScreen::sendMessage(Entity* sender ,string message)
{
	if (message == "ScreenOn" && mTurnOn == false)
	{
		mOpenScreenAnimation.play(true);
		mTurnOn = true;
	}

}

void CameraScreen::drawEntity(sf::RenderTarget& target, sf::RenderStates states) const
{	
	states.transform *= getTransform();	
	
	target.draw(mOpenScreenAnimation.getCurrentSprite(), states);
	if (mOpenScreenDone)
		target.draw(mOpenAnimation.getCurrentSprite(), states);
	
	if (mOpenDone)
		target.draw(mActiveAnimation.getCurrentSprite(), states);
		
}