#pragma once
#include "Loading.h"
#include <string>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>


class Animation
{
public:
	
	Animation(TexturesID fileName,
				unsigned int spriteWidth,
				unsigned int spriteHeight,
				unsigned int numberOfSprites,
				unsigned int numberOfRows,
				unsigned int timePerFrame,
				unsigned int spriteRow);

	Animation(const Animation& animation);

	sf::Sprite getCurrentSprite() const;
	void setPosition(const sf::Vector2f& position);
	void resetAnimation();
	void updateAnimation();
	int getAnimLength();
	bool endOfAnimation() const;

	~Animation();
private:
	sf::Clock frameClock;
	sf::Sprite mSprite;
	unsigned int mSpriteWidth
		,mSpriteHeight
		,mNumberOfSprites
		,mTimePerFrame
		,mNumberOfRows
		,mCurrentFrame
		,mSpriteRows
		,mLeft
		,mCurrentColumnNumber
		,mTop
		,mCurrentRow;
	bool mEndOfAnimation;
};

