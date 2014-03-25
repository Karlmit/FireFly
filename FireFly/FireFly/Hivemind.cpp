#include "Hivemind.h"

////////////////////////////////////////////////////////////////////////
//Single image constructor.
//rect - What area the zone that triggers the hivemind will occupy.
//texture - What image to use. Entered via filename.
//textureWidth - How many pixels wide the image is.
//textureHeight - How many pixels high the image is.
//All variables are supplied from Tiled's object properties.
////////////////////////////////////////////////////////////////////////
Hivemind::Hivemind(sf::FloatRect rect,
				   const std::string texture) :
	mRigidbody(),
	scale(0),
	scaledUp(true),
	scaledDown(true),
	badScaling(false),
	fadeTime(false),
	mSprite(Loading::getTexture(texture, true)),
	mScaleSpeed(100),
	opacity(200)
{
	//Sets the image and area for the hivemind image.
	mSprite.setTextureRect(sf::IntRect(0.f,0.f, mSprite.getLocalBounds().width, mSprite.getLocalBounds().height));
	mSprite.setOrigin(static_cast<float>(mSprite.getLocalBounds().width/2), static_cast<float>(mSprite.getLocalBounds().height/2));
	mSprite.setPosition(546, 307);
	mSprite.setScale(0,0);
	mSprite.setColor(sf::Color(255,255,255,200));

	//Sets the area where the hivemind image will play.
	mRigidbody.AddTriggerBoxBody(rect, false, sf::Vector2f(0,0));
	mRigidbody.getBody()->SetUserData(this);


}

void Hivemind::start()
{
	mZid = EntityList::getEntityList().getEntity("Zid");
}

void Hivemind::drawEntity(sf::RenderTarget& target, sf::RenderStates states) const
{
	// Rigidbody debug draw
	if (Globals::DEBUG_MODE)
		mRigidbody.drawDebug(target, states);

	
	target.draw(mSprite);
}

void Hivemind::updateEntity(sf::Time dt)
{

		if(badScaling == false && scaledUp == false)
		{
			scaledUp = true;
			badScaling = true;
		}
		spawn();

		if(scaledDown == false)
		{
			despawn();
		}
}

//
//Displays the image. The scale speed decides how many frames it will take to scale up.
//
void Hivemind::spawn()
{
	if(scaledDown == false)
	{
		scaledUp = true;
	}
	if(scaledUp == false)
	{
		if(scale < 1) //Makes the sprite invisible the first frame it's out
		{
			++scale;
			mSprite.setScale(0,0);
		}
		else if(scale < mScaleSpeed && scale > 0) //Scales the sprite up gradually
		{
			++scale;
			mSprite.setScale(((1.f/mScaleSpeed)*scale),((1.f/mScaleSpeed)*scale));
		}
		else //Claims that the scaling of the sprite is done, making sure to set it at the correct scaling.
		{
			if(scaledUp == false)
			{
				std::cout << "Done scaling up!" << endl;
				fadeTime = true;
				opacity = 200;
			}
			mSprite.setScale(1,1);
			scale = mScaleSpeed;
			scaledUp = true;

		}
	}
	if(fadeTime == true)
	{
		if(opacity > 0 && opacity <= 200)
		{
			opacity = opacity - 2;
			mSprite.setColor(sf::Color(255,255,255,opacity));
		}
		else
		{
			opacity = 0;
			mSprite.setColor(sf::Color(255,255,255,opacity));
			fadeTime = false;
			mSprite.setScale(0,0);
			std::cout << "garshunk" << endl;
		}
	}
}

//
//Removes the image. The scale speed decides how many frames it will take to scale down.
//
void Hivemind::despawn()
{
	if(opacity < 10)
	{
		mSprite.setScale(0,0);
	}
	if(scale >= mScaleSpeed) //Does nothing the first frame it's out
	{
		--scale;
		mSprite.setScale(1,1);
	}
	else if(scale < mScaleSpeed && scale > 0) //Scales the sprite down gradually
	{
		--scale;
		mSprite.setScale(((1.f/mScaleSpeed)*scale),((1.f/mScaleSpeed)*scale));
	}
	else //Claims that the scaling of the sprite is done, making sure to set it at the correct scaling.
	{
		mSprite.setScale(0,0);
		scale = 0;
		scaledDown = true;
		std::cout << "Done scaling down!" << endl;
		fadeTime = false;
		opacity = 255;
		mSprite.setColor(sf::Color(255,255,255,255));
	}
}

void Hivemind::BeginContact(b2Contact *contact, Entity* mZid)
{
	std::cout << "ping" << endl;
	scaledUp = false;
}

void Hivemind::EndContact(b2Contact *contact, Entity* mZid)
{
	std::cout << "pong" << endl;
	scaledDown = false;
}