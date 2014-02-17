#pragma once

#include "Entity.h"

class FadeToBlack : public Entity
{
public:
	FadeToBlack(float delay, bool fadeTo = false, string nextMap = "");
private:
	virtual void updateEntity(sf::Time dt);	
	virtual void drawEntity(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	float mDelay;
	bool mFadeTo;
	sf::Clock mTimer;
	sf::Color mColor;
	sf::RectangleShape mRectShape;
	string mNextMap;
};
