#include "lever.h"


lever::lever(sf::Vector2f position, std::string imageSRC)
	: mSprite(Loading::getTexture(imageSRC))
{
	sf::FloatRect rect = mSprite.getLocalBounds();		createLever(position, rect);	setPosition(position);
}


lever::~lever(void)
{
}

void lever::createLever(sf::Vector2f position, sf::FloatRect rect)
{
	std::vector<sf::FloatRect> rects;	rects.push_back(rect);
	
	firstBody.AddDynCircleBody(100, sf::Vector2f(position.x, position.y + 40), 1, false);
	secondBody.AddDynRectBody(rects, position, 1, true);
	
	b2Body *myBodyA = firstBody.getBody();
	b2Body *myBodyB = secondBody.getBody();

	b2RevoluteJointDef jointDef; 
	jointDef.bodyA = myBodyA; 
	jointDef.bodyB = myBodyB; 
	jointDef.bodyA->SetType(b2_staticBody);
	jointDef.Initialize(myBodyA, myBodyB, myBodyA->GetWorldCenter());
	jointDef.lowerAngle = -0.25f * b2_pi; // -45 degrees 
	jointDef.upperAngle = 0.25f * b2_pi; // 45 degrees 	jointDef.enableLimit = true;

	//jointDef.anchorPoint = myBodyA->GetCenterPosition(); 
	//b2RevoluteJoint* joint = (b2RevoluteJoint*)myWorld->CreateJoint(&jointDef); 
	/*... do stuff ... */
	//myWorld->DestroyJoint(joint); 
	//joint = NULL; 
}


void lever::updateEntity(sf::Time dt)
{
	firstBody.update();
	secondBody.update();

	setPosition(firstBody.getPosition());
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
}

