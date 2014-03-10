//Light.cpp - Firely

#include "Light.h"
#include "Box2dWorld.h"
#include "RayCastCallback.h"
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
	
	createLight();
}

Light::~Light()
{
	
}

void Light::sendMessage(Entity* sender, string message, int value)
{
	if (message == "ChangeRadius")
	{
		float radiusStep = 30.f;
		radius = max (50.f, radius + radiusStep * value);
	}
}

float Light::getDistance(sf::Vector2f Point1, sf::Vector2f Point2)					
{																																																			
	float a = Point2.x - Point1.x;																				
	float b = Point2.y - Point1.y;																
                                                                                                                                                                                                        
	float c = sqrt((a*a) + (b*b));
    
	return c;																											
}


void Light::createLightMap()
{
	
}

void Light::createLight()
{
	

	sf::VertexArray triangleFan(sf::TrianglesFan);
	sf::VertexArray triangleFan2(sf::TrianglesFan);

	sf::VertexArray circleOutline(sf::TrianglesStrip);
	sf::VertexArray circleOutline2(sf::TrianglesStrip);

	sf::Vertex currentVertex;
	
	currentVertex.position = getPosition();
	currentVertex.color = sf::Color(color.r,color.g,color.b,0);
	
	triangleFan.append(currentVertex);

	currentVertex.color = color;

	triangleFan2.append(currentVertex);
	
	float currentAngle = angle - (angleSpread / 2);
	float dynamicLength;
	float addTo = 15.0f / radius;

    
	for (currentAngle; currentAngle < angle + (angleSpread / 2); 
		currentAngle += addTo * (180/3.1415926f))
	{ 
		dynamicLength = radius;
        
		float radians = currentAngle * (3.1415926f/180);

		if(dynamic)
		{
			RayCastCallback ray;
			b2Vec2 from = Rigidbody::SfToBoxVec(getPosition());
			b2Vec2 to = from + Rigidbody::SfToBoxVec(cos(radians) * radius, sin(radians) * radius);
			Box2dWorld::instance().RayCast(&ray, from, to);
			 
			if (ray.hit)
			{
				dynamicLength = Rigidbody::BoxToSfFloat( (Rigidbody::SfToBoxVec(getPosition()) - ray.point).Length() );
			}
		}
	
		sf::Vector2f end = getPosition();
		end.x += cos(radians) * dynamicLength;
		end.y += sin(radians) * dynamicLength;
		 
        currentVertex.position = end;
		currentVertex.color = sf::Color(255, 255, 255, uint8(255*(dynamicLength/radius)));
		
        triangleFan.append(currentVertex);
		circleOutline.append(currentVertex);
		

		currentVertex.color = sf::Color(color.r, color.g, color.b, uint8(color.a*(1-(dynamicLength/radius))));

		triangleFan2.append(currentVertex);

		circleOutline2.append(currentVertex);

		if(dynamicLength != radius)
		{
			end.x += cos(radians) * 50;
			end.y += sin(radians) * 50;

			currentVertex.position = end;

			currentVertex.color = sf::Color(color.r, color.g, color.b, 255);
		
			circleOutline.append(currentVertex);

			currentVertex.color = sf::Color(color.r, color.g, color.b, 0);

			circleOutline2.append(currentVertex);
		}
	}
	
	if(angleSpread >= 360)
	{
		triangleFan.append(triangleFan[1]);
		triangleFan2.append(triangleFan2[1]);

		circleOutline.append(circleOutline[0]);
		circleOutline.append(circleOutline[1]);

		circleOutline2.append(circleOutline2[0]);
		circleOutline2.append(circleOutline2[1]);
	}

	fanColor = triangleFan2;
	fanLight = triangleFan;
	outLineColor = circleOutline2;
	outlineLight = circleOutline;
}


void Light::updateEntity(sf::Time dt)
{
	//static float realRadius = radius;
	//static bool growLight = true;
	//
	//if(growLight)
	//{
	//	radius += 0.5;
	//}
	//else
	//{
	//	radius -= 0.5;
	//}
	//
	//if(radius >= realRadius+5)
	//{
	//	growLight = false;
	//}
	//else if(radius <= realRadius-5)
	//{
	//	growLight = true;
	//}
	if (radius > 50)
		createLight();

}

void Light::drawEntity(sf::RenderTarget& target, sf::RenderStates states) const
{ 
	if (radius > 50)
	{
		target.draw(fanLight, sf::BlendMultiply);
		target.draw(fanColor, sf::BlendAdd);
		target.draw(outlineLight, sf::BlendMultiply);
		target.draw(outLineColor, sf::BlendAdd);
	}
}


