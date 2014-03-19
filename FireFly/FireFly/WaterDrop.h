#pragma once
#include "Entity.h"


class WaterDrop : public Entity
{
public:
	WaterDrop(sf::Vector2f position, float endPosition, float spawntime);
	~WaterDrop();
	virtual void sendMessage(Entity* entity, std::string message);
private:
	virtual void updateEntity(sf::Time dt);	
	virtual void drawEntity(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::Vector2f mPosition;
	sf::Sprite mSprite;

	Rigidbody mRigidbody;
	float mEndPosition;
	sf::Clock mSpawnClock;
	float mSpawnTime;
	bool mActivate;


};

