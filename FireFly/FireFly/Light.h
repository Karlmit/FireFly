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
	Light(sf::Color color, sf::Vector2f position, float radius, float angleSpread, float angle, std::string mID); // Creates a light with the attributes given to it.
	~Light();
	void createLight();

private:
	
	sf::Color color;							// The lighs color.						
	float radius;								// How far the light will shine.
	float angleSpread;							// Spread of the light
	float angle;								// Where the light is pointing 
	bool dynamic;

	void createLightMap();

	virtual void drawEntity(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void updateEntity(sf::Time dt);		//Virtual update function derived from entity			
	
	float getDistance(sf::Vector2f refPoint1, sf::Vector2f refPoint2);

	sf::VertexArray fanLight;
	sf::VertexArray fanColor;
	sf::VertexArray outlineLight;
	sf::VertexArray outLineColor;
	
};