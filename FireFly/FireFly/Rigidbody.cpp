#include "Rigidbody.h"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include "Box2dWorld.h"
#include <iostream>

// SFML units is in pixels and box2d in meters.
const float PIXELS_PER_METER = 100.f;

std::vector<std::vector<sf::Vector2f>> Rigidbody::collisionList;

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
// Creates an empty rigidbody. 
// Call AddBody to add a box2d body to it.
//
Rigidbody::Rigidbody()
: mB2World(&Box2dWorld::instance())
,mBody(nullptr)
{
}

// The destructor makes sure to remove the body from the box2d simulation
Rigidbody::~Rigidbody() {
	// Removes the body from box2d
	if (mBody)
		mB2World->DestroyBody(mBody);
}

//
// Add a static chain collider
//
void Rigidbody::AddStaticLineBody(const std::vector<sf::Vector2f>& pointList, bool loop)
{
	if (mBody)
		throw std::logic_error("Rigidbody::AddStaticLineBody - Tried to add a body more than once.");


	// Define the ground body.
	b2BodyDef groundBodyDef;
	groundBodyDef.position = SfToBoxVec(0, 0);

	// Creates body
	mBody  = mB2World->CreateBody(&groundBodyDef);

	// Convert the list of sfml points to box2d points
	std::vector<b2Vec2> pointListb2Vec;
	for (sf::Vector2f sf : pointList)
		pointListb2Vec.push_back(SfToBoxVec(sf));
	b2Vec2 *vs = &pointListb2Vec[0];

	// Make a chain shape of the points
	b2ChainShape chain;
	if (loop)
		chain.CreateLoop(vs, pointList.size());
	else
		chain.CreateChain(vs, pointList.size());	

	// Add the chain to the body
	mBody->CreateFixture(&chain, 0);

	collisionList.push_back(pointList);

	// Debug shape visuals
	if (loop)
	{		
		mLinePointList = pointList;
		mLinePointList.push_back(pointList.at(0));
	}
	else
		mLinePointList = pointList;
}

void Rigidbody::AddDynCircleBody(float radius, sf::Vector2f position, float32 density )
{
	if (mBody)
		throw std::logic_error("Rigidbody::AddDynCircleBody - Tried to add a body more than once.");

	
	// Define the dynamic body. We set its position and call the body factory.
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = SfToBoxVec(position);
	mBody = mB2World->CreateBody(&bodyDef);

	b2CircleShape dynamicCircle;
	dynamicCircle.m_radius = SfToBoxFloat(radius);

	// Define another box shape for our dynamic body.
	//b2PolygonShape dynamicBox;
	//dynamicBox.SetAsBox(SfToBoxFloat(rect.width/2) , SfToBoxFloat(rect.height/2));


	// Define the dynamic body fixture.
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicCircle;
	// Set the box density to be non-zero, so it will be dynamic.
	fixtureDef.density = density;
	// Override the default friction.
	fixtureDef.friction = 0.3f;
	//
	fixtureDef.restitution = 0.f;
	//

	// Add the shape to the body.
	mBody->CreateFixture(&fixtureDef);

	// Debug draw
		
	mCircleShape.setRadius(radius);
	mCircleShape.setFillColor(sf::Color::Transparent);
	mCircleShape.setOutlineColor(sf::Color::Green);
	mCircleShape.setOutlineThickness(1.f);
	mCircleShape.setPosition(-radius, -radius);
}

//
// Adds dynamic rectangles to a body
//
void Rigidbody::AddDynRectBody(std::vector<sf::FloatRect> rects, sf::Vector2f position, float density, bool dynamic)
{
	// Define the dynamic body. We set its position and call the body factory.
	b2BodyDef bodyDef;
	if (dynamic)
		bodyDef.type = b2_dynamicBody;
	else
		bodyDef.type = b2_staticBody;
	bodyDef.position = SfToBoxVec(position);
	mBody = mB2World->CreateBody(&bodyDef);
		
	
	for (sf::FloatRect rect : rects) {
		// Define another box shape for our dynamic body.
		b2PolygonShape dynamicBox;
		b2Vec2 center = SfToBoxVec(rect.left+rect.width/2, rect.top+rect.height/2);
		dynamicBox.SetAsBox(SfToBoxFloat(rect.width/2) , SfToBoxFloat(rect.height/2), center, 0);
		// Define the dynamic body fixture.
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &dynamicBox;
		// Set the box density to be non-zero, so it will be dynamic.
		fixtureDef.density = density;
		// Override the default friction.
		fixtureDef.friction = 0.3f;
		//
		fixtureDef.restitution = 0.f;
		//

		// Add the shape to the body.
		mBody->CreateFixture(&fixtureDef);
	}

	int i = 0;
	for (sf::FloatRect rect : rects) {
		sf::RectangleShape rectShape;
		rectShape.setSize(sf::Vector2f(rect.width, rect.height));
		rectShape.setPosition(sf::Vector2f(rect.left, rect.top));
		rectShape.setFillColor(sf::Color::Transparent);
		rectShape.setOutlineThickness(-4);
		mRectShapes.push_back(rectShape);
		i++;
	}		
}

void Rigidbody::AddTriggerBoxBody(sf::FloatRect rect)
{
	// Define the dynamic body. We set its position and call the body factory.
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position = SfToBoxVec(sf::Vector2f(rect.left+rect.width/2, rect.top+rect.height/2));
	mBody = mB2World->CreateBody(&bodyDef);

	// Define another box shape for our trigger body.
	b2PolygonShape dynamicBox;
	//b2Vec2 center = SfToBoxVec(rect.left+rect.width/2, rect.top+rect.height/2);
	//dynamicBox.SetAsBox(SfToBoxFloat(rect.width/2) , SfToBoxFloat(rect.height/2), center, 0);
	dynamicBox.SetAsBox(SfToBoxFloat(rect.width/2) , SfToBoxFloat(rect.height/2));
	// Define the trigger body fixture.
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.isSensor = true;

	// Add to the body
	mBody->CreateFixture(&fixtureDef);

	// Add debug visual
	sf::RectangleShape rectShape;
	rectShape.setSize(sf::Vector2f(rect.width, rect.height));
	rectShape.setPosition(sf::Vector2f(rect.left, rect.top));
	sf::Color color;
	color = sf::Color::Blue;
	color.a = 60;
	rectShape.setFillColor(color);
	rectShape.setOutlineThickness(-4);
	rectShape.setOutlineColor(sf::Color::Blue);
	mRectShapes.push_back(rectShape);
}


// Updates the transform on the rigidbody with sfml units
void Rigidbody::update() 
{	
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
	
	
	// Draw Rectangle
	for (sf::RectangleShape mRectShape : mRectShapes)
		target.draw(mRectShape, states);
	
	
	// Draw Circle
	// Crashes the program for som reason when running the exe directly and turn on debug draw in the beginning
	// Only runs it if in debug mode so not to crash the release version.
#ifdef _DEBUG
	target.draw(mCircleShape, states);
#endif
	
	// Draw Lines	
	sf::VertexArray lines(sf::LinesStrip, mLinePointList.size());
	for (std::vector<sf::Vector2f>::size_type i = 0; i < mLinePointList.size(); i++)
		lines[i].position = mLinePointList.at(i);
	target.draw(lines, states);
	
	

}

// Return the body
b2Body* Rigidbody::getBody() {
	return mBody;	
}