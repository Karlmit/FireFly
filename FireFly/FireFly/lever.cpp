#include "lever.h"


lever::lever(sf::Vector2f position, std::string imageSRC)
	: mSprite(Loading::getTexture(imageSRC))
{
	sf::FloatRect rect = mSprite.getLocalBounds();
	
	createLever(position, rect);
	setPosition(position);
}


lever::~lever(void)
{
}

void lever::createLever(sf::Vector2f position, sf::FloatRect rect)
{
	std::vector<sf::FloatRect> rects;
	rects.push_back(rect);
	
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	b2Vec2 boxPosition = Rigidbody::SfToBoxVec(position);
	bodyDef.position.Set(boxPosition.x, boxPosition.y);

	b2BodyDef baseBodyDef;
	baseBodyDef.type = b2_staticBody;
	baseBodyDef.position.Set(boxPosition.x, boxPosition.y - Rigidbody::SfToBoxFloat(rect.height/2));

	b2FixtureDef fixtureDef;
	fixtureDef.density = 0.5f;
	b2PolygonShape polygonShape;
	polygonShape.SetAsBox(Rigidbody::SfToBoxFloat(rect.width), Rigidbody::SfToBoxFloat(rect.height));
	fixtureDef.shape = &polygonShape;

	b2FixtureDef baseFixtureDef;
	baseFixtureDef.density = 1.f;
	baseFixtureDef.shape = &polygonShape;

	//Shape for rendering, I dont need to render shapes thou
	shape.setSize(sf::Vector2f(rect.width, rect.height));
	shape.setFillColor(sf::Color::Red);

	baseBody = Box2dWorld::instance().CreateBody(&baseBodyDef);
	baseBody->CreateFixture(&baseFixtureDef);

	leverBody = Box2dWorld::instance().CreateBody(&bodyDef);
	leverBody->CreateFixture(&fixtureDef);

	b2RevoluteJointDef revoluteDef;
	revoluteDef.localAnchorA.Set(0.07f, 0.f);
	revoluteDef.localAnchorB.Set(-0.07f, 0.f);
	revoluteDef.collideConnected = true;



	//b2Body *myBodyA = firstBody.getBody();
	//
	//firstBody.AddDynCircleBody(100, sf::Vector2f(position.x, position.y), 1, false);
	//firstBody.getBody()->CreateFixture(&baseFixtureDef);
	//myBodyA = Box2dWorld::instance().CreateBody(&baseBodyDef);
	////b2Body VECTOR?
	

	revoluteDef.bodyA = leverBody;
	revoluteDef.bodyB = baseBody;
	revoluteDef.localAnchorA.Set(0.07f, 0.f);
	revoluteDef.localAnchorB.Set(-0.07f, 0.f);
	Box2dWorld::instance().CreateJoint(&revoluteDef);


	mLinkList.push_back(leverBody);
	mLinkList.push_back(baseBody);

	//firstBody.AddDynCircleBody(100, sf::Vector2f(position.x, position.y), 1, false);
	//secondBody.AddDynRectBody(rects, position, 1, true);
	//
	//
	//b2Body *myBodyB = secondBody.getBody();
	//
	//b2RevoluteJointDef jointDef; 
	//jointDef.bodyA = myBodyA; 
	//jointDef.bodyB = myBodyB; 
	//jointDef.bodyA->SetType(b2_staticBody);
	//jointDef.Initialize(myBodyA, myBodyB, myBodyA->GetWorldCenter());
	//jointDef.lowerAngle = -0.25f * b2_pi; // -45 degrees 
	//jointDef.upperAngle = 0.25f * b2_pi; // 45 degrees 
	//jointDef.enableLimit = true;
	//jointDef.collideConnected = true;
	//jointDef.localAnchorA = Rigidbody::SfToBoxVec(position);
	//jointDef.localAnchorB = Rigidbody::SfToBoxVec(position);
	//
	////jointDef.anchorPoint = myBodyA->GetCenterPosition(); 
	//b2RevoluteJoint* joint = (b2RevoluteJoint*)Box2dWorld::instance().CreateJoint(&jointDef);
	///*... do stuff ... */
	////myWorld->DestroyJoint(joint); 
	////joint = NULL; 
}


void lever::updateEntity(sf::Time dt)
{
	//firstBody.update();
	//secondBody.update();
	mSpriteList.clear();
	for(b2Body *b : mLinkList)
	{
		shape.setPosition(Rigidbody::BoxToSfVec(b->GetPosition()));
		//shape.setRotation(Rigidbody::BoxToSfAngle(b->GetAngle()));
		mSpriteList.push_back(shape);
	}



	mSprite.setPosition(Rigidbody::BoxToSfVec(leverBody->GetPosition()));
	setPosition(Rigidbody::BoxToSfVec(leverBody->GetPosition()));
}

void lever::drawEntity(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(mSprite, states);
	if(Globals::DEBUG_MODE)
	{
		firstBody.drawDebug(target, states);
		secondBody.drawDebug(target, states);
	}

	for(sf::RectangleShape s : mSpriteList)
	{
		target.draw(s, states);
	}

}

