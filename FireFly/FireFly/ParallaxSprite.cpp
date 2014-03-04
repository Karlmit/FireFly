#include "ParallaxSprite.h"
#include "Camera.h"
#include <iostream>

ParallaxSprite::ParallaxSprite(string textureID ,sf::Vector2f position) 
: mSprite(Loading::getTexture(textureID))
, mSpeedFactor(0.2f)
{
	// Sätter origin för spriten till mitten
	sf::FloatRect bounds = mSprite.getLocalBounds();
	mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

	mPos = position;
	setPosition(position);

	mPos = sf::Vector2f(2970, 600);
}

void ParallaxSprite::updateEntity(sf::Time dt) 
{

	sf::Vector2f pos;
	pos.x = mPos.x -  Camera::currentCamera().getPosition().x * mSpeedFactor;
	pos.y = mPos.y;// + Camera::currentCamera().getPosition().y * mSpeedFactor;
	setPosition(pos);
	
}
		
void ParallaxSprite::drawEntity(sf::RenderTarget& target, sf::RenderStates states) const
{	
	states.transform *= getTransform();
	target.draw(mSprite, states);
}
