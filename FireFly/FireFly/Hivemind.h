#include "Entity.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>



class Hivemind : public Entity
{
public:
	Hivemind(sf::Vector2f position, sf::Texture texture);
	~Hivemind();

private:
	virtual void drawEntity(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void updateEntity(sf::Time dt);
	sf::Sprite hivemindProjection;
	bool project;
};