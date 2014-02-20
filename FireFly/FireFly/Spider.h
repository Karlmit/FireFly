#pragma once
#include "Entity.h"
#include "Animation.h"
#include "EntityList.h"
#include "Audio.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RectangleShape.hpp>


class Spider : public Entity
{
public:
	Spider(sf::Vector2f position, sf::Vector2f startofRoom, sf::Vector2f sizeofRoom);
	~Spider(void);
	virtual void sendMessage(Entity* entity, std::string message);
	
private:
	Rigidbody mRigidbody;
	Animation dangleAnimation;
	Animation walkingAnimation;
	sf::Sprite mSprite;
	sf::RectangleShape net;
	void movement(float range);
	void roofWalking();
	void mMakeNet(float range);
	void walkBackToTop();
	void falltoFloor();
	virtual void updateEntity(sf::Time dt);	
	virtual void drawEntity(sf::RenderTarget& target, sf::RenderStates states) const;
	Entity* mZid;
	bool activate;
	bool RoofDirection;
	bool spiderman;
	bool makeNet;
	bool inRange;
	bool activateMove;
	bool walkBack;
	bool mRopeisCut;
	float length;
	b2Vec2 mZidPosition;
	sf::Vector2f startPosition;
	sf::Vector2f netStart;
	sf::Vector2f roomSize;
	sf::Vector2f roomStart;
	Audio walkSound;
};

