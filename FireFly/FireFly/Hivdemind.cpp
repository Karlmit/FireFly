#include "Hivemind.h"

Hivemind::Hivemind(sf::Vector2f position, sf::Texture texture)
{
	this->setPosition(position);
	//this->hivemindProjection.setTexture(texture);
	sf::RectangleShape rect = sf::RectangleShape(sf::Vector2f(100,100));
	rect.setFillColor(sf::Color::Red);
	sf::RenderTexture rTex;
	rTex.create(100,100);
	rTex.draw(rect);
	sf::Texture tempTex = rTex.getTexture();
	hivemindProjection.setTexture(tempTex);
	project = false;
}

Hivemind::~Hivemind()
{
}

void Hivemind::drawEntity(sf::RenderTarget& target, sf::RenderStates states) const
{ 
	if(project)
	{
		target.draw(hivemindProjection);
	}
}

void Hivemind::updateEntity(sf::Time dt)
{
	
}