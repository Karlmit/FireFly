#include "EntitySprite.h"

EntitySprite::EntitySprite(Textures::ID  textureID) 
: mSprite(Loading::getLoading().GetTexture(textureID))
{
	// Sätter origin för spriten till mitten
	sf::FloatRect bounds = mSprite.getLocalBounds();
	mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

EntitySprite::EntitySprite(Textures::ID  textureID ,sf::Vector2f position) 
: mSprite(Loading::getLoading().GetTexture(textureID))
{
	// Sätter origin för spriten till mitten
	sf::FloatRect bounds = mSprite.getLocalBounds();
	mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

	setPosition(position);
}

void EntitySprite::updateEntity(sf::Time dt) 
{
	
}
		
void EntitySprite::drawEntity(sf::RenderTarget& target, sf::RenderStates states) const
{	
	states.transform *= getTransform();
	target.draw(mSprite, states);
}