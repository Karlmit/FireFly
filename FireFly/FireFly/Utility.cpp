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

sf::Vector2f Util::randPointInCircle(float outerRadius, float innerRadius)
{
	float angle = randFloat()*3.14159265359f*2.f;

	float x = cos(angle)*outerRadius;
	float y = sin(angle)*outerRadius;

	sf::Vector2f vec = sf::Vector2f(x, y);
	vec *= randFloat(innerRadius/outerRadius, 1.f);
	return vec;
}

sf::Vector2f Util::randPointInCircle(float outerRadius, float innerRadius, float angleFrom, float angleTo)
{
	float pi2 = 3.14159265359f*2.f;
	float angle = randFloat(angleFrom/pi2,  angleTo/pi2)*pi2;

	float x = cos(angle)*outerRadius;
	float y = sin(angle)*outerRadius;

	sf::Vector2f vec = sf::Vector2f(x, y);
	vec *= randFloat(innerRadius/outerRadius, 1.f);
	return vec;
}

float Util::randFloat()
{
	return static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
}
float Util::randFloat(float low, float high)
{
	return low + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(high-low)));
}

sf::Vector2f Util::Lerp(sf::Vector2f from, sf::Vector2f to, float t )
{
	return from + (to - from) * t;
}

float Util::Lerp(float from, float to, float t )
{
	return from + (to - from) * t;
}