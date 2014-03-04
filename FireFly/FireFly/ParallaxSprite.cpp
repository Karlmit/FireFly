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
	// Temp
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		mPos.x -= 10.f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		mPos.x += 10.f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		mPos.y -= 10.f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		mPos.y += 10.f;

	static int count = 0;
	if (count == 0)
		cout << mPos.x << "," << mPos.y << endl;
	count = (count + 1) % 100;


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
