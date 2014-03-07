#pragma once
#include "Entity.h"
#include "EntityList.h"

class BalkPort : public Entity
{
public:
	BalkPort(string texture, sf::Vector2f position, float width, float height);
	virtual void sendMessage(Entity* entity, std::string message);
private:
	Rigidbody mRigidbody;
	virtual void updateEntity(sf::Time dt);	
	virtual void drawEntity(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::Sprite mSprite;
	sf::FloatRect mFloatRect;

	bool mActivate;


};

