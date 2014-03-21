#include "ServerRoomDoor.h"


const unsigned FRAMES_PER_SECOND = 60;
const unsigned TIME_PER_FRAME = unsigned( 1000 / FRAMES_PER_SECOND );


ServerRoomDoor::ServerRoomDoor(string texture, sf::Vector2f position)
	: mSprite()
	, mAnimation(Loading::getTexture(texture), 432, 2160, 1, 10, TIME_PER_FRAME)
{
	// Sätter origin för spriten till mitten
	sf::FloatRect bounds = mSprite.getLocalBounds();
	mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

	setPosition(position);
}

void ServerRoomDoor::start()
{
	
}


void ServerRoomDoor::updateEntity(sf::Time dt)
{
	mAnimation.updatePlay();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
		mAnimation.play(true);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::N))
		mAnimation.play(false);
}

void ServerRoomDoor::sendMessage(Entity* sender ,string message)
{
	
}

void ServerRoomDoor::drawEntity(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	
	target.draw(mAnimation.getCurrentSprite(), states);

}