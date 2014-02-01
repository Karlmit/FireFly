#include "Entity.h"


Entity::Entity()
:mAliveStatus(true)
{

}

Entity::~Entity() {
}

/*
void Entity::addRigidbody(Rigidbody *rigidbody) {
	mRigidbody = std::unique_ptr<Rigidbody>(rigidbody);
}
*/

void Entity::update(sf::Time dt) 
{
	/*
	if (mRigidbody) {
		mRigidbody->update();
				
		setPosition(mRigidbody->getPosition());
		setRotation(mRigidbody->getRotation());
	}
	*/

	// Called on child classes
	updateEntity(dt);
}

void Entity::updateEntity(sf::Time dt)
{	
	// Do nothing
}


void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const 
{
	// Draw rigidbody debug
	/*
	if (mRigidbody)
		mRigidbody->drawDebug(target, states);
		*/

	// Apply transform of current node
	//states.transform *= getTransform();

	// Called on child classes
	drawEntity(target, states);
}

void Entity::drawEntity(sf::RenderTarget&, sf::RenderStates) const
{
	// Do nothing by default
}

