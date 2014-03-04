#pragma once

#include "Entity.h"
#include "Audio.h"

class Telefonsvarare : public Entity
{
public:
	Telefonsvarare(string textureID ,sf::Vector2f position);

private:
	virtual void updateEntity(sf::Time dt);	
	virtual void drawEntity(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void sendMessage(Entity* sender, string message);

	virtual void BeginContact(b2Contact *contact, Entity* other); 
	virtual void EndContact(b2Contact *contact, Entity* other);

private:
	sf::Sprite mSprite;
	bool mMessageLeft;
	Audio mAudioMessage;
	sf::Font mFont;
	sf::Text mMessageText;
	Rigidbody mRigidbody;
};