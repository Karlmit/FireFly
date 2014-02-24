#pragma once

#include "DBTweener\dbtweener.h"
#include <SFML\System.hpp>
#include <vector>
using std::vector;

class Tween
{
public:
	Tween();

	void addTween(CDBTweener::CEquation *pEquation, CDBTweener::EEasing eEasing, float fDuration, float *fpValue, float fTarget);
	void clearTweens();
	bool update(sf::Time dt);
	void restart();

private:
	vector<CDBTweener::CTween> mTweens;
	vector<float> mDurations;
	float mTotalTime;
	sf::Clock mTimer;

};