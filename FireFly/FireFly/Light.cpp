//Light.cpp - Firely

#include "Light.h"

#include <iostream>

Light::Light(sf::Color color, sf::Vector2f position, float radius, float angleSpread, float angle, std::string mID) // Constructor, creates a light with the attributes given to it.
{
	dynamic = true; 
	this->color = color;
	this->setPosition(position);
	this->radius = radius;
	this->angleSpread = angleSpread;
	this->angle = angle;
	
	if(angleSpread > 360)
		angleSpread = 360;
	this->mID = mID;
	Block * block = new Block(sf::FloatRect(1000,1000,20,20), true);
	blockList.push_back(block);
	
	createLight();
}

Light::~Light()
{
	
}

float Light::getDistance(sf::Vector2f Point1, sf::Vector2f Point2)					
{																																																			
	float a = Point2.x - Point1.x;																				
	float b = Point2.y - Point1.y;																
                                                                                                                                                                                                        
	float c = sqrt((a*a) + (b*b));
    
	return c;																											
}


sf::Vector2f Light::getCenter(sf::FloatRect &refRect)
{
	return sf::Vector2f(refRect.left + (refRect.width /2), refRect.top + (refRect.height /2));
}

bool Light::findShortestDistance::lightHitsBlock(Light * pLight, Block * pBlock, const float currentAngle, float &refLength)
{
	if(pBlock->allowBlock)
	{
		float distance = pLight->getDistance(pLight->getPosition(), pLight->getCenter(pBlock->blockArea));

		if(pLight->radius >= distance)
		{
			float radians = currentAngle * (3.14f /180);

			sf::Vector2f pointPosition = pLight->getPosition();
			pointPosition.x += cos(radians) * distance;
			pointPosition.y += sin(radians) * distance;

			if((*pBlock).blockArea.contains(pointPosition))
			{
				if(start || distance < shortest)
				{
					start = false;
					shortest = distance;
					refLength = distance;
				}
				return true;
			}
		}
	}
	return false;
}

Light::findShortestDistance::findShortestDistance() 
{
	start = false;
	shortest = 0;
}

void Light::createLightMap()
{
	
}

void Light::createLight()
{
	sf::VertexArray triangleFan(sf::TrianglesFan);
	sf::VertexArray triangleFan2(sf::TrianglesFan);
	sf::Vertex currentVertex;
	
	currentVertex.position = getPosition();
	currentVertex.color = sf::Color(color.r,color.g,color.b,0);
	
	triangleFan.append(currentVertex);

	currentVertex.color = color;

	triangleFan2.append(currentVertex);
	
	float currentAngle = angle - (angleSpread / 2);
	float dynamicLength;
	float addTo = 5.0f / radius;
    
	for (currentAngle; currentAngle < angle + (angleSpread / 2); 
		currentAngle += addTo * (180/3.1415926f))
	{ 
		dynamicLength = radius;
		findDistance.start = true;
		findDistance.shortest = 0;
	
		
		if(dynamic)
		{
			//add collision code 
		}
        
		float radians = currentAngle * (3.1415926f/180);
	
		sf::Vector2f end = getPosition();
		end.x += cos(radians) * dynamicLength;
		end.y += sin(radians) * dynamicLength;
		 
        currentVertex.position = end;
		currentVertex.color = sf::Color(color.r, color.g, color.b, 255*(dynamicLength/radius));
		
        triangleFan.append(currentVertex);

		currentVertex.color = sf::Color(color.r, color.g, color.b, color.a*(1-(dynamicLength/radius)));
		triangleFan2.append(currentVertex);
	}
	
	if(angleSpread >= 360)
	{
		triangleFan.append(triangleFan[1]);
		triangleFan2.append(triangleFan2[1]);
	}

	fanColor = triangleFan2;
	fanLight = triangleFan;
}


void Light::updateEntity(sf::Time dt)
{
	createLight();

}

void Light::drawEntity(sf::RenderTarget& target, sf::RenderStates states) const
{ 
	target.draw(fanLight, sf::BlendMultiply);
	target.draw(fanColor, sf::BlendAlpha);
}


