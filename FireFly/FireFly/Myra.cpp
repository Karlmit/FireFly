#include "Myra.h"
#include "Utility.h"
#include <iostream>

Myra::Myra(float pathPercent ,vector<sf::Vector2f> path)
	: mSprite(Loading::getTexture("Ernst.png"))
	, mPath(path)
	, mPathNodeProc()
	, mTotalLength(0)
{
	assert(pathPercent >= 0 ||pathPercent <= 1);
	assert(path.size() >= 2);

	// Sätter origin för spriten till mitten
	sf::FloatRect bounds = mSprite.getLocalBounds();
	mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);


	vector<float> pathLengths;
	mTotalLength= 0;
	for (vector<sf::Vector2f>::size_type i = 0; i < (path.size()-1); i++)
	{		
		if (i == 0)
		{
			float length = (path.at(i) - path.at(i+1)).getLength();
			pathLengths.push_back(length);
			mTotalLength += length;
		}
		else 
		{
			float length = (path.at(i) - path.at(i+1)).getLength();
			pathLengths.push_back(length + pathLengths.at(i-1));
			mTotalLength += length;
		}
	}

	mPathNodeProc.push_back(0);
	for (float length : pathLengths)
	{
		mPathNodeProc.push_back(length/mTotalLength);
	}	
	

	setProcPosition(pathPercent);

}

void Myra::setProcPosition(float p)
{
	int node = 0;
	for (vector<sf::Vector2f>::size_type i = 0; i < mPathNodeProc.size(); i++)
	{	
		if (p >= mPathNodeProc.at(i))
			node = i;					
	}

	if (node == mPath.size()-1)
	{
		setPosition(mPath.at(node));
	}
	else
	{
		float per = (mPath.at(node+1) - mPath.at(node)).getLength() / mTotalLength;
		setPosition(Util::Lerp(mPath.at(node), mPath.at(node+1), p));
	}
}

void Myra::updateEntity(sf::Time dt)
{
	static int count = 0;
	if (count == 10)
	{
		std::cout << getPosition().x << "\t" << getPosition().y << endl;
		count = 0;
	}
	count++;
}

void Myra::drawEntity(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(mSprite, states);
}