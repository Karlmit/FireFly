#include "Rigidbody.h"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include "Box2dWorld.h"
#include <iostream>

// SFML units is in pixels and box2d in meters.
const float PIXELS_PER_METER = 100.f;


// Conversion functions between sfml units and box2d units
b2Vec2 Rigidbody::SfToBoxVec(const sf::Vector2f& vec) 
{
	return b2Vec2(vec.x / PIXELS_PER_METER, -vec.y / PIXELS_PER_METER);
}

b2Vec2 Rigidbody::SfToBoxVec(float x, float y) 
{
	return b2Vec2(x / PIXELS_PER_METER, -y / PIXELS_PER_METER);
}

sf::Vector2f Rigidbody::BoxToSfVec(const b2Vec2& vec)
{
	return sf::Vector2f(vec.x, -vec.y) * PIXELS_PER_METER;
}

sf::Vector2f Rigidbody::BoxToSfVec(float32 x, float32 y)
{
	return sf::Vector2f(x, -y) * PIXELS_PER_METER;
}

float Rigidbody::SfToBoxAngle(float degrees)
{
	return -degrees * 0.0174533f;
}

float Rigidbody::BoxToSfAngle(float rads)
{
	return -rads * 57.29578f;
}

float32 Rigidbody::SfToBoxFloat(float val)
{
	return val / PIXELS_PER_METER;
}

float Rigidbody::BoxToSfFloat(float32 val)
{
	return val * PIXELS_PER_METER;
}

// End of conversion functions //

//
// Creates a rectangle rigidbody
//
Rigidbody::Rigidbody(sf::FloatRect rect, bool isStatic)
: mB2World(&Box2dWorld::instance())
, mStatic(isStatic)
{

	// Sets the entity transform postion
	//setPosition(rect.left, rect.top);

	if (mStatic) 
	{

		// Box 2d body creation
		// Define the ground body.
		b2BodyDef groundBodyDef;
		groundBodyDef.position = SfToBoxVec(rect.left, rect.top);

		mBody  = mB2World->CreateBody(&groundBodyDef);

		// Define the ground box shape.
		b2PolygonShape groundBox;
		// The extents are the half-widths of the box.
		groundBox.SetAsBox(SfToBoxFloat(rect.width/2) , SfToBoxFloat(rect.height/2));
		// Add the ground fixture to the ground body.
		mBody->CreateFixture(&groundBox, 0.0f);


		// Debug shape visuals
		mRectShape.setOutlineColor(sf::Color::Red);

	}
	else 
	{
		// Define the dynamic body. We set its position and call the body factory.
		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;
		bodyDef.position = SfToBoxVec(rect.left, rect.top);
		mBody = mB2World->CreateBody(&bodyDef);
		// Define another box shape for our dynamic body.
		b2PolygonShape dynamicBox;
		dynamicBox.SetAsBox(SfToBoxFloat(rect.width/2) , SfToBoxFloat(rect.height/2));
		// Define the dynamic body fixture.
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &dynamicBox;
		// Set the box density to be non-zero, so it will be dynamic.
		fixtureDef.density = 1.0f;
		// Override the default friction.
		fixtureDef.friction = 0.3f;
		//
		fixtureDef.restitution = 0.f;
		//

		// Add the shape to the body.
		mBody->CreateFixture(&fixtureDef);


		// Test second shape ///////////////
		/* WORKS !!!
		dynamicBox.SetAsBox(rect.width/(2*PIXELS_PER_METER), rect.height/(2*PIXELS_PER_METER), SfToBoxVec(300.f, 0), 0);
		fixtureDef.shape = &dynamicBox;

		mBody->CreateFixture(&fixtureDef);
		*/
		///////////////////////////////////////////


		// Debug shape visuals
		mRectShape.setOutlineColor(sf::Color::Green);
	}

	// Debug shape visuals
	// Set the shape origin in the centre
	mRectShape.setSize(sf::Vector2f(rect.width, rect.height));
	mRectShape.setOrigin(sf::Vector2f(rect.width/2, rect.height/2));
	mRectShape.setFillColor(sf::Color::Transparent);
	mRectShape.setOutlineThickness(-4);

	
	update();
} 

Rigidbody::Rigidbody(float radius, sf::Vector2f position, bool isStatic) 
: mB2World(&Box2dWorld::instance())
, mStatic(isStatic)
{

}

/*
Rigidbody::Rigidbody(b2Body* body) 
: mB2World(&Box2dWorld::instance())
, mBody(body)
{
	// No debug with this version
}
*/

// The destructor makes sure to remove the body from the box2d simulation
Rigidbody::~Rigidbody() {
	// Removes the body from box2d	
	mB2World->DestroyBody(mBody);
}


// Updates the transform on the rigidbody with sfml units
void Rigidbody::update() 
{	
	// (Possible just update the transform directly with a reference to parent enitity)
	b2Vec2 b2Position = mBody->GetPosition();	
	float32 b2Angle = mBody->GetAngle();
	
	setPosition(BoxToSfVec(b2Position));
	setRotation(BoxToSfAngle(b2Angle));

}

// Draw debug shapes
void Rigidbody::drawDebug(sf::RenderTarget& target, sf::RenderStates states) const
{	
	// Apply transform of current rigidbody transform
	states.transform = getTransform();
	
	target.draw(mRectShape, states);
}

// Return the body
b2Body* Rigidbody::getBody() {
	return mBody;	
}