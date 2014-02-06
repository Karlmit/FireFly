#include <SFML\Graphics.hpp>

namespace Util
{
	sf::Vector2f randPointInCircle(float radius);
	float randFloat();
	sf::Vector2f Lerp(sf::Vector2f from, sf::Vector2f to, float t );
	float Lerp(float from, float to, float t );
}