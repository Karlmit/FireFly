#pragma once


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
	virtual void start();
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

