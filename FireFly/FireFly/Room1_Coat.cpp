#include "Room1_Coat.h"
#include "EntityList.h"
//#include <iostream>

const float EATING_SPEED = 0.2f;

Room1_Coat::Room1_Coat(sf::Vector2f position)
	: mSprites()
	, mEatProgress(0)
	, mEating(false)
	, mCurrentSprite(0)
{
	setPosition(position);
	mID = "Room1_Coat";
	
	for (int i = 0; i < 5; i++) 
	{
		sf::Sprite sprite((Loading::getTexture("Room 1/Coat " + to_string(i+1) + ".png")));
		// Sätter origin för spriten till mitten
		sf::FloatRect bounds = sprite.getLocalBounds();
		sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
		mSprites.push_back(sprite);
	}
}

void Room1_Coat::sendMessage(Entity* sender, string message)
{
	if (message == "StartEating")
		mEating = true;
}


void Room1_Coat::updateEntity(sf::Time dt)
{
	if (mEating)
	{
		mEatProgress += EATING_SPEED * dt.asSeconds();

		mCurrentSprite = int(mEatProgress /  (1.f / mSprites.size()));
		mCurrentSprite = min(mCurrentSprite, int(mSprites.size()-1));

		if (mCurrentSprite == mSprites.size()-1)
		{
			Entity* holeCole = EntityList::getEntityList().getEntity("CoatHoleCollision");
			if (holeCole)
				holeCole->killEntity();

			mEating = false;
			for (Entity* mal : EntityList::getEntityList().getEntities("Mal"))
				mal->sendMessage(this, "CoatFinished");
		}

	}
}

void Room1_Coat::drawEntity(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(mSprites.at(mCurrentSprite), states);
}