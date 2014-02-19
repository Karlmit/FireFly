#pragma once

#include "Entity.h"
#include "Animation.h"
#include "Audio.h"

class Myra : public Entity
{
public:
	Myra(float pathPercent ,vector<sf::Vector2f> path);

private:
	virtual void updateEntity(sf::Time dt);	
	virtual void drawEntity(sf::RenderTarget& target, sf::RenderStates states) const;

	void setProcPosition(float p);

private:
	sf::Sprite mSprite;
	vector<sf::Vector2f> mPath;
	vector<float> mPathNodeProc;
	float mTotalLength;
};