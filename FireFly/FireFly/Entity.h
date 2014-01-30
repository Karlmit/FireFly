#pragma once
#include <string>
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include "Loading.h"

class Entity
{
public:
	Entity();
	~Entity();
	std::string getID(){return mID;}	//Used to identify 
	sf::Vector2f returnPosition(){return mPosition;}
	virtual void updateEntity() = 0;
	virtual void drawEntity(sf::RenderWindow *window) = 0;
	bool getAliveStatus(){return mAliveStatus;}
	void killEntity(){mAliveStatus = false;}

protected:
	std::string mID;
	sf::Vector2f mPosition;
	sf::Sprite mSprite;	//in each entity, assign position and texture.
	bool mAliveStatus;	//true = the entity is alive.
	sf::FloatRect mRectangle; //In each identity declare width and height. Used for collision.
	sf::Texture mTexture; //store loaded texture here
	sf::SoundBuffer mBuffer; //stores loaded buffer
	sf::Sound mSound;
};

