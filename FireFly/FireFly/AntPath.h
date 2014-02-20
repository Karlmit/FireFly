#pragma once

#include "Entity.h"
#include "Animation.h"
#include "Audio.h"

#include "Myra.h"


class AntPath : public Entity
{
public:
	AntPath(vector<sf::Vector2f> path);

private:
	virtual void updateEntity(sf::Time dt);	
	virtual void drawEntity(sf::RenderTarget& target, sf::RenderStates states) const;


private:
	vector<sf::Vector2f> mPath;
	vector<float> mLengths;
	vector<sf::Vector2f> mDirections;
	sf::Sprite mAnt;
	vector<Myra> mMyroror;
};