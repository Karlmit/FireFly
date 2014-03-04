#include "AntPath.h"
#include <iostream>
#include "EntityList.h"


const float SPEED = -50.f;



AntPath::AntPath(vector<sf::Vector2f> path)
	: mPath(path)
	, mLengths(path.size())
	, mDirections(path.size())
	, mAnt(Loading::getTexture("Ernst.png"))
	, mTotalLength(0)
{	
	// Sätter origin för spriten till mitten
	sf::FloatRect bounds = mAnt.getLocalBounds();
	mAnt.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

	
	for (unsigned i = 0; i < mPath.size()-1; i++)
	{
		mDirections.at(i) = mPath.at(i+1) - mPath.at(i);
		mLengths.at(i) = mDirections.at(i).getLength();
		mTotalLength += mLengths.at(i);
		mDirections.at(i).normalize();
	}

	
	// Creates ants
	for (int i = 0; i < 14; i++)
	{
		Entity* myra = new Myra(i*200.f  ,mPath, mLengths, mDirections, mTotalLength);
		EntityList::getEntityList().addEntity(myra, Layer::Background);
	}	
}


void AntPath::updateEntity(sf::Time dt)
{	 
}

void AntPath::drawEntity(sf::RenderTarget& target, sf::RenderStates states) const
{
	// Draw Lines	

	if (Globals::DEBUG_MODE)
	{
		sf::VertexArray lines(sf::LinesStrip, mPath.size());
		for (std::vector<sf::Vector2f>::size_type i = 0; i < mPath.size(); i++)
			lines[i].position = mPath.at(i);
		target.draw(lines);
	}
}