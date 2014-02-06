#include "Animation.h"



Animation::Animation(TexturesID texture,
						unsigned int spriteWidth,
						unsigned int spriteHeight,
						unsigned int numberOfSprites,
						unsigned int numberOfRows,
						unsigned int timePerFrame,
						unsigned int spriteRow) :
	mNumberOfSprites(numberOfSprites),
	mNumberOfRows(numberOfRows),
	mTimePerFrame(timePerFrame),
	mSpriteWidth(spriteWidth),
	mSpriteHeight(spriteHeight),
	mCurrentFrame(0),
	mSprite(Loading::getLoading().getTexture(texture)),
	mEndOfAnimation(false),
	mSpriteRows(spriteRow),
	currentRowNumber(0),
	top(0),
	currentRow(0),
	left(0)
{
	mSprite.setTextureRect(sf::IntRect(0,0, spriteWidth, spriteHeight));
	mSprite.setOrigin( static_cast<float>(spriteWidth/2), static_cast<float>(spriteHeight/2) );
}

//Animation::Animation(const Animation& animation) :
//		mNumberOfSprites(animation.mNumberOfSprites),
//		mTimePerFrame(animation.mTimePerFrame),
//		mCurrentFrame(animation.mCurrentFrame),
//		mCurrentSprite(animation.mCurrentSprite),
//		mSpriteHeight(animation.mSpriteHeight),
//		mSpriteWidth(animation.mSpriteWidth),
//		mTexture(animation.mTexture),
//		mSprite(animation.mSprite),
//		mEndOfAnimation(animation.mEndOfAnimation),
//		mSpriteRow(animation.mSpriteRow),
//		test(0),
//		top(0),
//		y(0)
//{
//}

Animation::~Animation(void)
{
}

sf::Sprite Animation::getCurrentSprite() const
{
	return mSprite;
}

void Animation::setPosition(const sf::Vector2f& position) 
{
	mSprite.setPosition(position);
}

void Animation::updateAnimation()
{
	if(frameClock.getElapsedTime().asMilliseconds() > int(mTimePerFrame))
	{
		frameClock.restart();	
		left = mSpriteWidth * mCurrentFrame;
		top = mSpriteHeight * currentRow;
		mSprite.setTextureRect(sf::IntRect(left, top, mSpriteWidth, mSpriteHeight));
		if(mCurrentFrame <= mNumberOfSprites)
		{
			++mCurrentFrame;
			++currentRowNumber;
			if(currentRowNumber == mSpriteRows)
			{
				++currentRow;
				currentRowNumber = 0;
				if(currentRow == mNumberOfRows)
				{
					currentRow = 0;
					
				}
				resetAnimation();
				
			}
	}

	}		
}

int Animation::getAnimLength(){
	totalFrames = mNumberOfSprites * mTimePerFrame;
	return totalFrames;
}

void Animation::resetAnimation(){
	mCurrentFrame= 0;
}


bool Animation::endOfAnimation() const{
	return mEndOfAnimation;	//currently never changeing
}
	
	
	
	
