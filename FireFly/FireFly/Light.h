//Light.h - Firefly

#pragma once

#include "Entity.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <list>
#include "Block.h"

class Light : public Entity
{
public:
	Light(sf::Color color, sf::Vector2f position, float radius, float angleSpread, 
		float angle, std::string mID, bool dynamic, bool shadows = true); // Creates a light with the attributes given to it.
	~Light();
	void createLight();

	virtual void sendMessage(Entity* sender, string message, int value);
	virtual void start();
	
	bool getSneakMode();

private:
	
	sf::Color color;							// The lighs color.						
	float radius;								// How far the light will shine.
	float normal_radius;
	float targetRadius;							// Go to this value for radius
	float angleSpread;							// Spread of the light
	float angle;								// Where the light is pointing 
	bool dynamic;
	bool lightKilled;
	bool sneakMode;
	sf::Vector2f mLastPosition;
	bool mUnmoved;	// The light hasn't moved since last update
	Entity* mZid;
	bool shadows;

	void createLightMap();

	virtual void drawEntity(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void updateEntity(sf::Time dt);		//Virtual update function derived from entity			
	
	float getDistance(sf::Vector2f refPoint1, sf::Vector2f refPoint2);

	sf::VertexArray fanLight;
	sf::VertexArray fanColor;
	sf::VertexArray outlineLight;
	sf::VertexArray outLineColor;
	
};