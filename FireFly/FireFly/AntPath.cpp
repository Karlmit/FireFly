#include "AntPath.h"
#include <iostream>


const float SPEED = -50.f;



AntPath::AntPath(vector<sf::Vector2f> path)
	: mPath(path)
	, mLengths(path.size())
	, mDirections(path.size())
	, mAnt(Loading::getTexture("Ernst.png"))
{	
	// Sätter origin för spriten till mitten
	sf::FloatRect bounds = mAnt.getLocalBounds();
	mAnt.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

	
	for (unsigned i = 0; i < mPath.size()-1; i++)
	{
		mDirections.at(i) = mPath.at(i+1) - mPath.at(i);
		mLengths.at(i) = mDirections.at(i).getLength();
		mDirections.at(i).normalize();
	}

}


void AntPath::updateEntity(sf::Time dt)
{
	//mAnt.setPosition
	/*
	static float pos = 0.f;

	static sf::Vector2f Position;

    static float mPos = 1000.f;
	mPos = mPos  + dt.asSeconds() * SPEED;
	float StagePos = mPos;
    int StageIndex = 0;

 

	if (StageIndex != mPath.size()-1 && StagePos >= 0)
	{
		StagePos += SPEED * dt.asSeconds();
		while (StagePos > mLengths[StageIndex])
		{
			StagePos -= mLengths[StageIndex]; 
			StageIndex++;              
			if (StageIndex == mPath.size()-1) 
			{
				Position = mPath[StageIndex];
				return;
			}
		}
		Position = mPath[StageIndex] + mDirections[StageIndex] * StagePos;
	}
	*/

	/*
	else
	{
		if (StageIndex < 0)
		{
			StagePos += SPEED * dt.asSeconds();
			while (StagePos > mLengths[StageIndex])
			{
				StagePos -= mLengths[StageIndex]; 
				StageIndex++;              
				if (StageIndex == mPath.size()-1) 
				{
					Position = mPath[StageIndex];
					return;
				}
			}
			Position = mPath[StageIndex] + mDirections[StageIndex] * StagePos;
		}
		else
			StageIndex = 0
	}
	*/
     
	//mAnt.setPosition(Position);


	 
}

void AntPath::drawEntity(sf::RenderTarget& target, sf::RenderStates states) const
{
	//states.transform *= getTransform();
	//target.draw(mAnt);

	// Draw Lines	
	sf::VertexArray lines(sf::LinesStrip, mPath.size());
	for (std::vector<sf::Vector2f>::size_type i = 0; i < mPath.size(); i++)
		lines[i].position = mPath.at(i);
	target.draw(lines);
}