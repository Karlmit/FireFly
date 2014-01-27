#pragma once
#include <string>
#include <SFML\Graphics.hpp>
#include "Loading.h"

class Entity
{
public:
	Entity();
	~Entity();
	std::string returnID(){return ID;}	//Used to identify 
	sf::Vector2f returnPosition(){return position;}
	virtual void updateEntity() = 0;
	virtual void drawEntity(sf::RenderWindow *window) = 0;
	std::string getID(){return ID;}
	virtual bool getAliveStatus(){return aliveStatus;}
	void killEntity(){aliveStatus = false;}

protected:
	std::string ID;
	sf::Vector2f position;	
	sf::Sprite sprite;	//in each entity asign position and texture.
	bool aliveStatus;	//true = the entity is alive.
	sf::FloatRect rectangle; //In each identity declare with and height. Used for collision.

};

