#pragma once

/*
class Entity : public sf::Transformable, public sf::Drawable
{
public:
	Entity();
	~Entity();

	//std::string getID(){return mID;}	//Used to identify 
	//sf::Vector2f returnPosition(){return mPosition;}
	virtual void updateEntity(sf:: Time timePerFrame) = 0;
	virtual void drawEntity(sf::RenderWindow *window) = 0;
	bool getAliveStatus(){return mAliveStatus;}
	void killEntity(){mAliveStatus = false;}
	sf::Sprite getSprite(){return mSprite;}

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
*/

#include <SFML\System/Time.hpp>
#include <SFML\Graphics.hpp>
#include "Globals.h"
#include "Loading.h"
#include "Rigidbody.h"
#include <memory>

class Entity : public sf::Transformable, public sf::Drawable
{
public:
	Entity();
	virtual ~Entity();

public:
	virtual void update(sf::Time dt);

	bool getAliveStatus(){return mAliveStatus;}
	void killEntity(){mAliveStatus = false;}
	std::string getID(){return mID;}
protected:
	std::string mID;
private:
	virtual void	updateEntity(sf::Time dt);
	virtual void	draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void	drawEntity(sf::RenderTarget& target, sf::RenderStates states) const;


private:
	bool mAliveStatus;	//true = the entity is alive.
	
};

