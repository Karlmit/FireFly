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
	
	Animation(const sf::Texture& texture,
				unsigned int spriteWidth,
				unsigned int spriteHeight,
				unsigned int numberOfRows,
				unsigned int numberOfColumns,
				unsigned int timePerFrame);

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
		,mNumberOfColumns
		,mLeft
		,mCurrentColumn
		,mTop
		,mCurrentRow;
	bool mEndOfAnimation;
};

