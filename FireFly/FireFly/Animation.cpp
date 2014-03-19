#include "Animation.h"


//The constructor gives others control over what is shown, and defines a sprite and an origin from the info provided
Animation::Animation(const sf::Texture& texture, //Loads an image from file
						unsigned int spriteWidth, //Width of a single sprite
						unsigned int spriteHeight, //Height of a single sprite
						unsigned int numberOfRows, //Rows in the animation
						unsigned int numberOfColumns, //Columns in the animation (also sprites if numberOfRows = 1)
						unsigned int timePerFrame) : //How long each frame is shown on the screen (in milliseconds, may vary depending on how often you call upon "updateAnimation()"
	mNumberOfRows(numberOfRows),
	mTimePerFrame(timePerFrame),
	mSpriteWidth(spriteWidth),
	mSpriteHeight(spriteHeight),
	mSprite(texture),
	mEndOfAnimation(false),
	mLoopOnce(false),
	mNumberOfColumns(numberOfColumns),
	mCurrentRow(0), //used in updates
	mCurrentColumn(0), //used in updates
	mTop(0), //used in updates
	mLeft(0), //used in updates
	mAnimFrame(0), //Used in oneLoop()
	mPlaying(false),
	mForward(true)
{
	mSprite.setTextureRect(sf::IntRect(0,0, spriteWidth, spriteHeight));
	mSprite.setOrigin( static_cast<float>(spriteWidth/2), static_cast<float>(spriteHeight/2) );
}



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
		mEndOfAnimation = false;
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
				mEndOfAnimation = true;
				resetAnimation();
			}
		}
	}		
}

bool Animation::updatePlay()
{	
	if (mPlaying == false)
		return false;
		

	//Makes sure that the animation is updated every Xth frame, as defined in the constructor.
	if(mForward && frameClock.getElapsedTime().asMilliseconds() > int(mTimePerFrame))
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
				mCurrentColumn = mNumberOfColumns-1;
				mCurrentRow = mNumberOfRows-1;
				mPlaying = false;
				return true;
			}
		}
	}

	if (!mForward && frameClock.getElapsedTime().asMilliseconds() > int(mTimePerFrame))
	{
		frameClock.restart();
		mLeft = mSpriteWidth * mCurrentColumn;
		mTop = mSpriteHeight * mCurrentRow;
		mSprite.setTextureRect(sf::IntRect(mLeft, mTop, mSpriteWidth, mSpriteHeight));
		--mCurrentColumn; //Makes the viewer see the next image in the row of sprites.
		//Changes the row of the sprite sheet once it hits the end of a row.
		if(mCurrentColumn == -1)
		{
			--mCurrentRow;
			mCurrentColumn = mNumberOfColumns-1;		

			//Makes sure to reset the animation once the last row is fully shown.
			if(mCurrentRow == -1)
			{
				mCurrentColumn = 0;
				mCurrentRow = 0;
				mPlaying = false;
				return true;
			}
		}
	}

	return false;
}

void Animation::play(bool forward)
{
	mPlaying = true;
	mForward = forward;
}

int Animation::getAnimLength()
{
	return mNumberOfColumns * mNumberOfRows;
}

void Animation::oneLoop()
{
	mAnimFrame++;
	updateAnimation();

	if(mEndOfAnimation == true)
	{
		resetAnimation();
		mLoopOnce = false;
	}
}

//Currently used to reset the updateAnimation class.
void Animation::resetAnimation()
{
	mCurrentColumn = 0;
	mCurrentRow = 0;
	mAnimFrame = 0;
}

void Animation::resetPlayAnimation()
{
	mCurrentColumn = 0;
	mCurrentRow = 0;
	mAnimFrame = 0;

	mPlaying = false;
	mForward = true;
	mSprite.setTextureRect(sf::IntRect(0,0, mSpriteWidth, mSpriteHeight));
}


//Function to monitor if an animation has ended.

bool Animation::endOfAnimation() const
{
	return mEndOfAnimation;
}
	
	
	
	
