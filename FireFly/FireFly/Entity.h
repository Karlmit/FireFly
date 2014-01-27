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
	virtual void updateEntity() = 0;

protected:
	std::string ID;
	sf::Vector2f position;
	sf::Sprite sprite;

};

