#pragma once

#include "Entity.h"
#include "Animation.h"
#include "Audio.h"

class Myra : public Entity
{
public:
	Myra(float pos,
		 vector<sf::Vector2f> path, 
		 vector<float> lengths, 
		 vector<sf::Vector2f> directions,
		 float totalLength);

private:
	virtual void updateEntity(sf::Time dt);	
	virtual void drawEntity(sf::RenderTarget& target, sf::RenderStates states) const;

	void setPosition(float x);

private:
	sf::Sprite mSprite;
	vector<sf::Vector2f> mPath;
	vector<float> mLengths;
	vector<sf::Vector2f> mDirections;
	float mTotalLength;
	float mPos;

	sf::Vector2f mCurrentDirection;

	bool mIdleMoveForward;
	sf::Clock mIdleMoveTimer;
	bool mIdle;
	float mTimeForIdle;
};