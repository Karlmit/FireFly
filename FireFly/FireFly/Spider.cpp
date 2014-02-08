#include "Spider.h"


Spider::Spider(sf::Vector2f position) :
	idleAnimation(Loading::getTexture("Resources/testspide.png", true), 128, 128, 150, 15, 10, 10)
{
	setPosition(position);

	float colRadius = 48.f;
	float density = 4.f;
	mRigidbody.AddDynCircleBody(colRadius, getPosition(), density);

	//damping
	mRigidbody.getBody()->SetLinearDamping(3.f);
	mRigidbody.getBody()->SetFixedRotation(true);

	
	mID = "Spider";
	mZid = EntityList::getEntityList().getEntity("Zid");
}


Spider::~Spider(void)
{
}

void Spider::updateEntity(sf::Time dt)
{
	idleAnimation.updateAnimation();

	mZidPosition = Rigidbody::SfToBoxVec(mZid->getPosition());

	idleAnimation.updateAnimation();
	mSprite = idleAnimation.getCurrentSprite();
	// Box2d physics body
	b2Body *body = mRigidbody.getBody();
	//degines movement for spider
	movement();

	if (body->GetLinearVelocity().x < 0) 
	{
		direction = true;
		mSprite.setScale(-1.f, 1.f);
	}
	else if (body->GetLinearVelocity().x > 0)
	{
		direction = false;
		mSprite.setScale(1.f, 1.f);
	}
	else if(body->GetLinearVelocity().x == 0)
	{
		if(direction == true)
		{
			mSprite.setScale(-1.f, 1.f);
		}
		else
		{
			mSprite.setScale(1.f, 1.f);
		}
	}
	mRigidbody.update();
	setPosition(mRigidbody.getPosition());
	setRotation(mRigidbody.getRotation());
}

void Spider::drawEntity(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(mSprite, states);

	if(Globals::DEBUG_MODE)
	mRigidbody.drawDebug(target, states);
}

void Spider::movement()
{
	b2Body *body = mRigidbody.getBody();

}
