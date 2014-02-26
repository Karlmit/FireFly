#pragma once
#include "Entity.h"
#include "Animation.h"
#include "EntityList.h"
#include "Audio.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML\Graphics\RectangleShape.hpp>
#include <SFML\Graphics\Font.hpp>

class PC : public Entity
{
public:
	PC(sf::Vector2f position);
	~PC();
	virtual void sendMessage(Entity* entity, std::string message);
	virtual void sendSfString(Entity* entity, sf::String message);
	void getTextEntered(std::string text);
private:
	virtual void updateEntity(sf::Time dt);	
	virtual void drawEntity(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::RectangleShape mScreen;
	sf::String msfString;
	sf::Font mFont;
	sf::Text mText;
	sf::Event mEvent;
};