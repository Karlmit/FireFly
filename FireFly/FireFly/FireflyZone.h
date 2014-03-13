#pragma once

#include "Entity.h"
#include "FireflyNPC.h"


class FireflyZone : public Entity
{
public:
	FireflyZone(sf::FloatRect rect);
private:
	virtual void start();
	virtual void drawEntity(sf::RenderTarget& target, sf::RenderStates states) const;

	virtual void BeginContact(b2Contact *contact, Entity* mZid); 
	virtual void EndContact(b2Contact *contact, Entity* mZid);

	Rigidbody mRigidbody;
	Entity* mZid;
	FireflyNPC* dora;

};

