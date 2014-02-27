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

float Util::randFloat(float low1, float high1, float low2, float high2)
{
	float range = (high1 - low1) + (high2 - low2);

	float randomFloat =  randFloat(0, range);

	if (randomFloat < (high1 - low1))
		return low1 + randomFloat;
	else
		return low2 + randomFloat - (high1 - low1);

}

bool Util::randBool()
{
	if (rand() % 2 == 0)
		return false;
	else 
		return true;
}

sf::Vector2f Util::Lerp(sf::Vector2f from, sf::Vector2f to, float t )
{
	return from + (to - from) * t;
}

float Util::Lerp(float from, float to, float t )
{
	return from + (to - from) * t;
}

