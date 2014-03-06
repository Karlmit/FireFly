#pragma once

#include "Entity.h"
#include "Animation.h"
#include "Audio.h"
#include "Tween.h"
#include "Zid.h"
#include "FadeToBlack.h"
#include "Level.h"

class JaktSpindel : public Entity
{
public:
	JaktSpindel(float pos,
		 vector<sf::Vector2f> path, 
		 vector<float> lengths, 
		 vector<sf::Vector2f> directions,
		 float totalLength);

	virtual void sendMessage(Entity* entity, std::string message);

private:
	virtual void start();
	virtual void updateEntity(sf::Time dt);	
	virtual void drawEntity(sf::RenderTarget& target, sf::RenderStates states) const;

	void attack();
	void setPosition(float x);
	sf::Vector2f calcPosition(float x);

private:
	sf::Sprite mSprite;
	Animation walkAnimation;
	Animation attackAnimation;
	vector<sf::Vector2f> mPath;
	vector<float> mLengths;
	vector<sf::Vector2f> mDirections;
	float mTotalLength;

	float mPos;
	float mSpeed;

	// Sugar
	Zid* mZid; 


	//attack
	bool mAttack;
	bool mRestartLevel;
	FadeToBlack *fadetoblack;

	//start
	bool mActivate;

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