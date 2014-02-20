#include "Myra.h"
#include "Utility.h"
#include <iostream>

const float SPEED = 40.f;

Myra::Myra(vector<sf::Vector2f> path, vector<float> lengths, vector<sf::Vector2f> directions)
	: mSprite(Loading::getTexture("Ernst.png"))
	, mPath(path)
	, mLengths(lengths)
	, mDirections(directions)
{
	// Sätter origin för spriten till mitten
	sf::FloatRect bounds = mSprite.getLocalBounds();
	mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);



}



void Myra::updateEntity(sf::Time dt)
{
	/*
	static int count = 0;
	if (count == 10)
	{
		std::cout << getPosition().x << "\t" << getPosition().y << endl;
		count = 0;
	}
	count++;
	*/
	static sf::Vector2f Position;
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

	setPosition(Position);

}

void Myra::drawEntity(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(mSprite, states);
}