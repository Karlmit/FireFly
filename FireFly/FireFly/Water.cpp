#include "Water.h"


Water::Water(sf::Vector2f position, float width, float height)
{
	mPosition = position;
	mWidth = width;
	mHeight = height;

	drop1 = true;
	drop2 = true;
	drop3 = true;

}


Water::~Water(void)
{
}

void Water::sendMessage(Entity* entity, std::string message)
{

}


void Water::updateEntity(sf::Time dt)
{
	if(mDroppClock.getElapsedTime().asMilliseconds() > 1000 && drop1 == true)
	{
		drop1 = false;
		//Spawn dropps here
		WaterDrop* waterdrop = new WaterDrop(mPosition.x + 10, mPosition.y, mPosition.y + mHeight, mWidth, mHeight);
		EntityList::getEntityList().addEntity(waterdrop);
		mDroppClock.restart();
	}
	if(mDroppClock.getElapsedTime().asMilliseconds() > 2000 && drop2 == true)
	{
		drop2 = false;
		//Spawn dropps here
		WaterDrop* waterdrop = new WaterDrop(mPosition.x + mWidth - 20, mPosition.y, mPosition.y + mHeight, mWidth, mHeight);
		EntityList::getEntityList().addEntity(waterdrop);
		mDroppClock.restart();
	}
	if(mDroppClock.getElapsedTime().asMilliseconds() > 3000 && drop3 == true)
	{
		drop3 = false;
		//Spawn dropps here
		WaterDrop* waterdrop = new WaterDrop(mPosition.x + mWidth/2, mPosition.y, mPosition.y + mHeight, mWidth, mHeight);
		EntityList::getEntityList().addEntity(waterdrop);
		mDroppClock.restart();
	}



}

void Water::drawEntity(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(mSprite, states);

}
