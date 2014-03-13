#pragma once

#include "Entity.h"
#include "Animation.h"
#include "Audio.h"
#include "Tween.h"
#include "Zid.h"

class Myra : public Entity
{
public:
	Myra(float pos,
		 vector<sf::Vector2f> path, 
		 vector<float> lengths, 
		 vector<sf::Vector2f> directions,
		 float totalLength);

private:
	virtual void start();
	virtual void updateEntity(sf::Time dt);	
	virtual void drawEntity(sf::RenderTarget& target, sf::RenderStates states) const;

	void idleMovement(sf::Time dt);
	void setPosition(float x);
	sf::Vector2f calcPosition(float x);

private:
	sf::Sprite mSprite;
	vector<sf::Vector2f> mPath;
	vector<float> mLengths;
	vector<sf::Vector2f> mDirections;
	float mTotalLength;
	Animation mWalking;

	float mPos;
	float mSpeed;

	// Sugar
	Zid* mZid; 
	bool mZidIsSweet;
	bool mZidDroppedSugar;
	sf::Clock mDroppedSugarZid;
	bool mDroppedInBoiler;

	// Rotation //
	Tween mSuperTweenRotation;
	float mRotation;
	float mTargetRotation;
	sf::Vector2f mCurrentDirection;
		
	// Idle //
	bool mIdle;
	bool mMoveForward;
	sf::Clock mIdleMoveTimer;
	bool mIdleMove;
	float mTimeForIdle;
};