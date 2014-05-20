#include "Telefonsvarare.h"

const unsigned FRAMES_PER_SECOND = 2;
const unsigned TIME_PER_FRAME = unsigned( 1000 / FRAMES_PER_SECOND );

const float SCALE = 0.337f;

Telefonsvarare::Telefonsvarare(sf::Vector2f position) 
: mBlinking(Loading::getTexture("Room 2/TlfnSvarareBlinkande.png"), 784, 594, 1, 2, TIME_PER_FRAME)
, mRepeat(Loading::getTexture("Room 2/TlfnSvarareRepeat.png"), 784, 594, 1, 2, TIME_PER_FRAME)
, mRunning(Loading::getTexture("Room 2/TlfnSvarareRunning.png"), 784, 594, 1, 4, TIME_PER_FRAME)
, mAudioMessage(Loading::getSound("Room 2/firefly dotter klar.wav"), false)
, mState(State::Blinking)
{
	setPosition(position + sf::Vector2f(SCALE*784/2, SCALE*594/2 - 7));
	mAudioMessage.setPosition(position);	

	// Trigger
	sf::FloatRect rect;
	rect.left = position.x + SCALE*594+5;
	rect.top = position.y - 5;
	rect.width = 50;
	rect.height = 50;
	mRigidbody.AddTriggerBoxBody(rect, false, sf::Vector2f(0,0));
	mRigidbody.getBody()->SetUserData(this);	
}

void Telefonsvarare::updateEntity(sf::Time dt) 
{	
	switch (mState)
	{
	case Telefonsvarare::State::Blinking:
		mBlinking.updateAnimation();
		break;
	case Telefonsvarare::State::Repeat:
		mRepeat.updateAnimation();
		break;
	case Telefonsvarare::State::Running:
		mRunning.updateAnimation();
		if (mAudioMessage.getSound()->getStatus() != sf::SoundSource::Status::Playing)
		{
			mState = State::Repeat;
		}
		break;
	default:
		break;
	}	
	
}
		
void Telefonsvarare::drawEntity(sf::RenderTarget& target, sf::RenderStates states) const
{	
	states.transform *= getTransform();	

	sf::Sprite sprite;
	switch (mState)
	{
	case Telefonsvarare::State::Blinking:
		sprite = mBlinking.getCurrentSprite();
		break;
	case Telefonsvarare::State::Repeat:
		sprite = mRepeat.getCurrentSprite();
		break;
	case Telefonsvarare::State::Running:
		sprite = mRunning.getCurrentSprite();
		break;
	default:
		break;
	}

	sprite.setScale(SCALE, SCALE);
	target.draw(sprite, states);

	if (Globals::DEBUG_MODE)
		mRigidbody.drawDebug(target, states);
}

void Telefonsvarare::sendMessage(Entity* sender, string message)
{

}

void Telefonsvarare::BeginContact(b2Contact *contact, Entity* other)
{
	if (mState == State::Running)
		return;

	if (other->getID() == "Zid")
	{
		mState = State::Running;
		mAudioMessage.play();
	}
}

void Telefonsvarare::EndContact(b2Contact *contact, Entity* other)
{
}