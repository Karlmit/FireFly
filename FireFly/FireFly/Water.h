#pragma once
#include "Entity.h"
#include "EntityList.h"
#include "Log.h"
#include "WaterDrop.h"


class Water : public Entity
{
public:
	Water(sf::Vector2f position, float width, float height);
	~Water(void);
	virtual void sendMessage(Entity* entity, std::string message);
private:
	virtual void updateEntity(sf::Time dt);	
	virtual void drawEntity(sf::RenderTarget& target, sf::RenderStates states) const;
	
	sf::Vector2f mPosition;
	sf::Sprite mSprite;
	sf::Clock mDroppClock;

	bool drop1, drop2, drop3;

	float mWidth;
	float mHeight;
};

