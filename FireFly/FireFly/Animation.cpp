#include "Animation.h"


//The constructor gives others control over what is shown, and defines a sprite and an origin from the info provided
Animation::Animation(const sf::Texture& texture, //Loads an image from file
						unsigned int spriteWidth, //Width of a single sprite
						unsigned int spriteHeight, //Height of a single sprite
						unsigned int numberOfRows, //Rows in the animation
						unsigned int numberOfColumns, //Columns in the animation (also sprites if rows are only one)
						unsigned int timePerFrame) : //How long each frame is shown on the screen (in milliseconds, may vary depending on how often you call upon "updateAnimation()"
	mNumberOfRows(numberOfRows),
	mTimePerFrame(timePerFrame),
	mSpriteWidth(spriteWidth),
	mSpriteHeight(spriteHeight),
	mSprite(texture),
//	mEndOfAnimation(false), // not in use
	mNumberOfColumns(numberOfColumns),
	mCurrentRow(0), //used in updates
	mCurrentColumn(0), //used in updates
	mTop(0), //used in updates
	mLeft(0) //used in updates
{
	mSprite.setTextureRect(sf::IntRect(0,0, spriteWidth, spriteHeight));
	mSprite.setOrigin( static_cast<float>(spriteWidth/2), static_cast<float>(spriteHeight/2) );
}

//Copy constructor (not in use)
//
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
//		mNumberOfColumns(animation.mNumberOfColumns),
//		test(0),
//		top(0),
//		y(0)
//{
//}

Animation::~Animation(void)
{
}

//Gets the sprite shown at the moment
sf::Sprite Animation::getCurrentSprite() const
{
	//mSprite.setScale(2, 2);
	return mSprite;
}

void Animation::setPosition(const sf::Vector2f& position) 
{
	mSprite.setPosition(position);
}

//The function that "animates" a sprite sheet when called upon very often.
void Animation::updateAnimation()
{
	//Makes sure that the animation is updated every Xth frame, as defined in the constructor.
	if(frameClock.getElapsedTime().asMilliseconds() > int(mTimePerFrame))
	{
		frameClock.restart();	
		mLeft = mSpriteWidth * mCurrentColumn;
		mTop = mSpriteHeight * mCurrentRow;
		mSprite.setTextureRect(sf::IntRect(mLeft, mTop, mSpriteWidth, mSpriteHeight));
		++mCurrentColumn; //Makes the viewer see the next image in the row of sprites.
		//Changes the row of the sprite sheet once it hits the end of a row.
		if(mCurrentColumn == mNumberOfColumns)
		{
			++mCurrentRow;
			mCurrentColumn = 0;
			//Makes sure to reset the animation once the last row is fully shown.
			if(mCurrentRow == mNumberOfRows)
			{
				resetAnimation();
			}
		}
	}		
}

int Animation::getAnimLength(){
	return mNumberOfColumns * mNumberOfRows;
}

//Currently used to reset the updateAnimation class.
void Animation::resetAnimation(){
	mCurrentColumn = 0;
	mCurrentRow = 0;
}


//Function to monitor if an animation has ended. (not in use)
//
//bool Animation::endOfAnimation() const{
//	return mEndOfAnimation;	//currently always "false"
//}
	
	
	
	
