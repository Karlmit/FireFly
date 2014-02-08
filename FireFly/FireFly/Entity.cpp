#include "Entity.h"


Entity::Entity()
:mAliveStatus(true)
{
}

Entity::~Entity() {
}


void Entity::start()
{
}

void Entity::update(sf::Time dt) 
{
	// Called on child classes
	updateEntity(dt);
}

void Entity::updateEntity(sf::Time dt)
{	
	// Do nothing
}


void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const 
{
	// Called on child classes
	drawEntity(target, states);
}

void Entity::drawEntity(sf::RenderTarget&, sf::RenderStates) const
{
	// Do nothing by default
}

