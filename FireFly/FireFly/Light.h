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

	sf::RenderTexture rLightMap;
	sf::Sprite sLightMap;
	sf::Texture tLightMap;
	void createLightMap();
	sf::Vector2f getCenter(sf::FloatRect &refRect);

	virtual void drawEntity(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void updateEntity(sf::Time dt);		//Virtual update function derived from entity			
	
	float getDistance(sf::Vector2f refPoint1, sf::Vector2f refPoint2);

	sf::VertexArray fanLight;
	sf::VertexArray fanColor;
	struct findShortestDistance																			// A struct for finding the shortest intersection between a light and a block.
	{
		findShortestDistance();																			
		float shortest;
		bool lightHitsBlock(Light * pLight, Block *pBlock, const float currrentAngle, float &refLength);	// Function checking whether a light and block intersects
		bool start;																						// To get the first distance to refer off of.
	};
	
	std::list<Block*> blockList; //not included in final project
	
	findShortestDistance findDistance;
};