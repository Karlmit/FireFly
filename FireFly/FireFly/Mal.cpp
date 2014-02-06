#include "Mal.h"

Mal::Mal(sf::Vector2f position)
	: idleAnimation(TexturesID::Moth, 64, 64, 4, 1, 20, 4)
	,mRigidbody()
{
	//start position
	setPosition(position);

	//dynamic circle
	float colRadius = 24.f;
	float density = 2.f;
	mRigidbody.AddDynCircleBody(colRadius, getPosition(), density);

	//damping
	mRigidbody.getBody()->SetLinearDamping(3.f);
	mRigidbody.getBody()->SetFixedRotation(true);

	mRigidbody.getBody()->SetBullet(true);

	mID = "Mal";
	mZid = EntityList::getEntityList().getEntity("Zid");
	
}


Mal::~Mal(void)
{
}

void Mal::updateEntity(sf:: Time timePerFrame)
{
	idleAnimation.updateAnimation();

	mZidPosition = Rigidbody::SfToBoxVec(mZid->getPosition());
	// Box2d physics body
	b2Body *body = mRigidbody.getBody();
	
	//Defines the movement of Mal
	movement();
	//get position and rotation from Rigidbody
	mRigidbody.update();
	setPosition(mRigidbody.getPosition());
	setRotation(mRigidbody.getRotation());	
}

void  Mal::drawEntity(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(idleAnimation.getCurrentSprite(), states);

	if(Globals::DEBUG_MODE)
		mRigidbody.drawDebug(target, states);
}

void Mal::movement()
{
	b2Body *body = mRigidbody.getBody();

	//counter gravity
	body->ApplyForce(body->GetMass() * - b2Vec2(0, -10.f), body->GetWorldCenter(), true);
		
	//Gets the direction from Mal to Zid
	b2Vec2 direction = mZidPosition - Rigidbody::SfToBoxVec(getPosition());
	float length = direction.Normalize();

	//Depedning on distance to Zid Mal either follows Zid or moves passivly around
	if(length < 5)
	{	//Following Zid
		b2Vec2 force(direction.x, direction.y);
		force *= 5.f;
		body->ApplyForceToCenter(force, true);
	}
	else
	{	//Passive
		//pushes Mal to a random direction
		float x = float(-1 + rand()%3);		
		float y = float(-1 + rand()%3);
		b2Vec2 force(x, y);
		force *= 5.f;
		body->ApplyForceToCenter(force, true);
	}
}

