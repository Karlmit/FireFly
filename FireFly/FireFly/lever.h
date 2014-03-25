#pragma once
#include "Entity.h"
#include "Box2dWorld.h"
#include <list>

class lever : public Entity
{
public:
	lever(sf::Vector2f position, std::string imageSRC);
	~lever();
	virtual void updateEntity(sf::Time dt);	
	virtual void drawEntity(sf::RenderTarget& target, sf::RenderStates states) const;
private:
	sf::Sprite mSprite;
	Rigidbody firstBody;
	Rigidbody secondBody;
	void createLever(sf::Vector2f position, sf::FloatRect rect);
	b2Body* leverBody;
	b2Body* baseBody;
	typedef std::list <sf::RectangleShape> spriteList;
	spriteList mSpriteList;
	typedef std::list <b2Body*> linkList;
	linkList mLinkList;
	sf::RectangleShape shape;
};

