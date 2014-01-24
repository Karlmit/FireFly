#pragma once
#include <string>
#include <SFML\Graphics.hpp>

class Entity
{
public:
	Entity(void);
	~Entity(void);
	std::string returnID(){return ID;}
	sf::Vector2f returnPosition(){return position;}
	

protected:
	std::string ID;
	sf::Vector2f position;
	sf::Sprite sprite;

};

