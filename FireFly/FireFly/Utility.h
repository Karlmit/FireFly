#include <SFML\Graphics.hpp>

namespace Util
{
	sf::Vector2f randPointInCircle(float radius);
	sf::Vector2f randPointInCircle(float outerRadius, float innerRadius);
	sf::Vector2f randPointInCircle(float outerRadius, float innerRadius, float angleFrom, float angleTo);
	float randFloat();
	float randFloat(float low, float high);
	sf::Vector2f Lerp(sf::Vector2f from, sf::Vector2f to, float t );
	float Lerp(float from, float to, float t );
}
