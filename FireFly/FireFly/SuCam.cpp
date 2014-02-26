#include "SuCam.h"
#include <iostream>


SuCam::SuCam(sf::FloatRect rect)
	: blinkAnimation(Loading::getTexture("SuCuSensorSpritesheetBlink.png"), 266, 148, 2, 5, 7)
	, openAnimation(Loading::getTexture("SuCuSensorSpritesheetOpen.png"), 266, 148, 1, 5, 7)
	, shutAnimation(Loading::getTexture("SuCuSensorSpritesheetShut.png"), 266, 148, 1, 5, 7)
	, mRigidbody()
{

	mRigidbody.AddTriggerBoxBody(rect);
	mRigidbody.getBody()->SetUserData(this);

	blinkAnimation.updateAnimation();
	mSprite=blinkAnimation.getCurrentSprite();

	setPosition(sf::Vector2f (rect.left+133, rect.top+74));
	rect = mRect;
	
	mID = "SuCam";

	zidSensed = false;
}

SuCam::~SuCam()
{
}

void SuCam::start()
{
	mZid = EntityList::getEntityList().getEntity("Zid");
}

void SuCam::updateEntity(sf::Time timePerFrame)
{
	if(blinkAnimation.mLoopOnce == true)
	{
		blinkAnimation.oneLoop();
	}
	//Get the sprite from animation
	mSprite=blinkAnimation.getCurrentSprite();

	// Gets Zids position in Box2D coords
	mZidPosition = Rigidbody::SfToBoxVec(mZid->getPosition());
}

void  SuCam::drawEntity(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (Globals::DEBUG_MODE)
		mRigidbody.drawDebug(target, states);
	states.transform *= getTransform();
	target.draw(mSprite, states);
}

void SuCam::BeginContact(b2Contact *contact, Entity* other)
{
	blinkAnimation.mLoopOnce = true;
}