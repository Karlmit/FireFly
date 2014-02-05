#ifndef ZID_H
#define ZID_H

#include "Entity.h"
#include "Animation.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RectangleShape.hpp>



class Zid : public Entity
{
public:
	Zid(sf::Vector2f position);

private:
	virtual void	updateEntity(sf::Time dt);	
	virtual void	drawEntity(sf::RenderTarget& target, sf::RenderStates states) const;

	void movement();

private:
sf::Sprite		mSprite;
	Rigidbody		mRigidbody;
	Animation idleAnimation;
	Animation dashAnimation;
	bool zidDash;
	unsigned int dashFrameNo;
};

#endif
