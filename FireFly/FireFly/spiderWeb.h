#pragma once
#include "entity.h"
class spiderWeb : public Entity
{
public:
	spiderWeb(sf::FloatRect rect);

private:
	virtual void start();
	virtual void updateEntity(sf::Time dt);
	virtual void drawEntity(sf::RenderTarget& target, sf::RenderStates& states) const;

	virtual void BeginContact(b2Contact *contact, Entity* mZid);
	virtual void EndContact(b2Contact *contact, Entity* mZid);

	Rigidbody mRigidbody;
};

