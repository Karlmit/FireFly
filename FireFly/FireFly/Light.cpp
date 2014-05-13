//Light.cpp - Firely

#include "Light.h"
#include "Box2dWorld.h"
#include "RayCastCallback.h"
#include <iostream>
#include "Utility.h"
#include "EntityList.h"

const float MIN_LIGHT = 2.f;



Light::Light(sf::Color color, sf::Vector2f position, float radius, float angleSpread, 
			 float angle, std::string mID, bool dynamic, bool shadows) // Constructor, creates a light with the attributes given to it.
{
	
	this->dynamic = dynamic; 
	this->color = color;
	this->setPosition(position);
	this->radius = radius;
	this->normal_radius = radius;
	this->targetRadius = radius;
	this->angleSpread = angleSpread;
	this->angle = angle;
	this->lightKilled = false;
	this->shadows = shadows;
	
	if(angleSpread > 360)
		angleSpread = 360;
	this->mID = mID;

	sneakMode = true;

	//createLight();
	
}

void Light::start()
{
	mZid = EntityList::getEntityList().getEntity("Zid");
}

Light::~Light()
{
	
}

void Light::sendMessage(Entity* sender, string message, int value)
{
	if (lightKilled)
		return;

	if (message == "ChangeRadius")
	{
		//float radiusStep = 30.f;
		//targetRadius = max (0.f, targetRadius + radiusStep * value);

		if (value > 0)
		{
			targetRadius = normal_radius;
			sneakMode = false;
		}
		if (value < 0)
		{
			targetRadius = 0;
			sneakMode = true;
		}
	}

	if (message == "KillLight")
	{
		targetRadius = float(value);
		lightKilled = true;
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
	
	/*
	Entity* zid = EntityList::getEntityList().getEntity("Zid");
	if (zid != nullptr)
		currentVertex.position = getPosition() - zid->getPosition() - sf::Vector2f(-3000, 3000);
	else
		currentVertex.position = getPosition();
	*/

	//sf::Vector2f zidRel = sf::Vector2f(getPosition().x - mZid->getPosition().x, getPosition().y - mZid->getPosition().y);
	//sf::Vector2f myRelativePosition = getPosition() + sf::Vector2f(-mZid->getPosition().x+WIDTH_OF_LIGHTMAP/2, -mZid->getPosition().y+HEIGHT_OF_LIGHTMAP/2);
	//sf::Vector2f myRelativePosition = sf::Vector2f(WIDTH_OF_LIGHTMAP/2, HEIGHT_OF_LIGHTMAP/2);
	sf::Vector2f myRelativePosition = getPosition();

	currentVertex.position = myRelativePosition;

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

		if(dynamic && !mUnmoved && shadows)
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
	
		sf::Vector2f end = myRelativePosition;
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
	if ((mLastPosition - getPosition()).getLengthSqr() < 0.05f)
	{
		mUnmoved = true;
	}
	else
	{
		mUnmoved = false;
	}

	mLastPosition = getPosition();

	if (lightKilled && radius > 65)
	{
		float radiusDamping = 0.55f;
		radius = Util::Lerp(radius, targetRadius, dt.asSeconds() * radiusDamping);
	}
	else if (lightKilled && radius <= 65)
	{
		float radiusDamping = 3.8f;
		radius = Util::Lerp(radius, targetRadius, dt.asSeconds() * radiusDamping);
	}
	else
	{
		float radiusDamping = 3.f;
		radius = Util::Lerp(radius, targetRadius, dt.asSeconds() * radiusDamping);
	}
	

	
	if (radius > MIN_LIGHT && !mUnmoved || abs(targetRadius - radius) > 0.5f)
		createLight();

}

void Light::drawEntity(sf::RenderTarget& target, sf::RenderStates states) const
{ 
	if (radius > MIN_LIGHT)
	{
		states.blendMode = sf::BlendMultiply;
		target.draw(fanLight, states);

		states.blendMode = sf::BlendAdd;
		target.draw(fanColor, states);

		states.blendMode = sf::BlendMultiply;
		target.draw(outlineLight, states);

		states.blendMode = sf::BlendAdd;
		target.draw(outLineColor, states);
	}
}

bool Light::getSneakMode()
{
	return sneakMode;
}


