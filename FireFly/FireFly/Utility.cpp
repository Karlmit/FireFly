#include "Utility.h"
#include <cmath>
using namespace std;

sf::Vector2f Util::randPointInCircle(float radius)
{
	float angle = randFloat()*3.14159265359f*2.f;

	float x = cos(angle)*radius;
	float y = sin(angle)*radius;

	sf::Vector2f vec = sf::Vector2f(x, y);
	vec *= randFloat();
	return vec;
}

float Util::randFloat()
{
	return static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
}

sf::Vector2f Util::Lerp(sf::Vector2f from, sf::Vector2f to, float t )
{
	return from + (to - from) * t;
}

float Util::Lerp(float from, float to, float t )
{
	return from + (to - from) * t;
}