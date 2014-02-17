#include "Spider.h"

Spider::Spider(sf::Vector2f position, sf::Vector2f startofRoom, sf::Vector2f sizeofRoom) :
dangleAnimation(Loading::getTexture("spiderHanging_sheet256.png"), 256, 256, 5, 10, 10),
walkingAnimation(Loading::getTexture("spiderwalking1.png"), 256, 256, 2, 8, 70)
{
	//sfVector holding starting position
	setPosition(position);
	startPosition = position;
	roomSize = sizeofRoom;
	roomStart = startofRoom;
	float colRadius = 60.f;
	float density = 4.f;
	mRigidbody.AddDynCircleBody(colRadius, getPosition(), density);
	//damping
	mRigidbody.getBody()->SetLinearDamping(3.f);
	mRigidbody.getBody()->SetFixedRotation(true);


	//Sets the direction for roofwalking to RIGHT
	RoofDirection = false;
	
	spiderman = true;
	mID = "Spider";
	mZid = EntityList::getEntityList().getEntity("Zid");

	//spoderMan should begin with walking
	activateMove = true;

	//net
	net.setFillColor(sf::Color::White);
	makeNet = false;
	inRange = true;
}


Spider::~Spider(void)
{
}

void Spider::updateEntity(sf::Time dt)
{
	dangleAnimation.updateAnimation();
	walkingAnimation.updateAnimation();

	//Zids Position in cords
	mZidPosition = Rigidbody::SfToBoxVec(mZid->getPosition());

	dangleAnimation.updateAnimation();
	mSprite = dangleAnimation.getCurrentSprite();
	// Box2d physics body
	b2Body *body = mRigidbody.getBody();


	//The range span the spider sees from the ceiling
	float range = mZidPosition.x - Rigidbody::SfToBoxFloat(getPosition().x);
	range = abs(range);
	range = Rigidbody::BoxToSfFloat(range);



	if(activateMove == true)
	{
		//defines movement for spider
		movement(range);
	}
	else if(makeNet == true)
	{
		mMakeNet(range);
	}
	else if(walkBack == true)
	{
		walkBackToTop();
	}

	//function that prepares the spoderMan to walkBack to the top
	//Mainly activates walkBackToTop
	if(getPosition().y >= roomSize.y - 30)
	{
		spiderman = true;
		activateMove = false;
		makeNet = false;
		walkBack = true;
		//Gives spoderman a specific postion due to sprite size
		body->SetTransform(b2Vec2(Rigidbody::SfToBoxFloat( getPosition().x), Rigidbody::SfToBoxFloat(-2030)), 0);
		//resets netLength
		net.setSize(sf::Vector2f(0, 0));
	}

		
	mRigidbody.update();
	setPosition(mRigidbody.getPosition());
	setRotation(mRigidbody.getRotation());
	

}

void Spider::drawEntity(sf::RenderTarget& target, sf::RenderStates states) const
{
	//net should only be drawn when spoderMan is making a net
	if(makeNet == true)
	{
		target.draw(net);
	}

	states.transform *= getTransform();
	target.draw(mSprite, states);

	if(Globals::DEBUG_MODE)
	mRigidbody.drawDebug(target, states);
}

void Spider::movement(float range)
{
	b2Body *body = mRigidbody.getBody();
	mSprite = walkingAnimation.getCurrentSprite();


	if(range < 50 && spiderman == true)
	{													 
			netStart = getPosition();
			net.setPosition(netStart.x + 32, 0);
			sf::Vector2f spiderManPosition = Rigidbody::BoxToSfVec( mZidPosition);
			spiderManPosition.y -= 500;
			body->SetTransform(b2Vec2(Rigidbody::SfToBoxFloat(getPosition().x + 32), mZidPosition.y + Rigidbody::SfToBoxFloat(500)), 0);
			spiderman = false; //The spider will scary jump no more. for this time...
			makeNet = true;
			//turns off movement()
			activateMove = false;
	
	}	
	else if(spiderman == true)
	{
		roofWalking();			
	}

}

void Spider::mMakeNet(float range)
{
	b2Body *body = mRigidbody.getBody();

	mSprite = dangleAnimation.getCurrentSprite();
	mSprite.setRotation(0);
	//length from spider to zid
	b2Vec2 direction = mZidPosition - Rigidbody::SfToBoxVec(getPosition());
	length = sqrt(direction.x * direction.x + direction.y * direction.y);
	direction.y /= length;

	if(range < 200 && inRange == true)
	{
		//MAKE STATIC NET...
		float netLength = abs(0 - getPosition().y);
		sf::Vector2f netSize(4, netLength);

		net.setSize(netSize);

		//moves spiderman down or up depending on Zids y-Position
		b2Vec2 move = Rigidbody::SfToBoxVec(getPosition());
		move.y += direction.y * 0.15;
		body->SetTransform(move, 0);
	}
	else
	{
		inRange = false;
		//Activates func makeNet();
		makeNet = true;

		//MAKE STATIC NET...
		float netLength = abs(0 - getPosition().y);
		sf::Vector2f netSize;
		netSize.y = netLength;
		netSize.x = 4;
		net.setSize(netSize);

		//moves spiderman down
		b2Vec2 move = Rigidbody::SfToBoxVec(getPosition());
		move.y += direction.y * - 0.1f;
		body->SetTransform(move, 0.f);
		

		//checks if spoderMan is back at the roof and then places him correctly there.
		if(getPosition().y <= startPosition.y)
		{
			b2Vec2 putBack;
			putBack = Rigidbody::SfToBoxVec(getPosition());
			putBack.y = Rigidbody::SfToBoxFloat(-startPosition.y);
			body->SetTransform(putBack, 0);
			activateMove = true;
			inRange = true;
			makeNet = false;
			spiderman = true;
		}
	}
}


void Spider::roofWalking()
{
	b2Body *body = mRigidbody.getBody();
	mSprite = walkingAnimation.getCurrentSprite();
	mSprite.setRotation(180);
	//Counter gravity
	body->ApplyForce(body->GetMass() * - b2Vec2(0,-10.f), body->GetWorldCenter(), true);
	
	//spoderMans roofWalking abillity
	if(getPosition().y <= startPosition.y)
	{
		b2Vec2 move = Rigidbody::SfToBoxVec(getPosition());
		if(RoofDirection)
		{
			move.x -= 0.03;
			//scales sprite to the left
			mSprite.setScale(-1, 1);
			body->SetTransform(move , 0);
			if(getPosition().x <= 0)
			{
				RoofDirection = false;
			}
		}
		if(!RoofDirection)
		{
			move.x += 0.03;			
			body->SetTransform(move , 0);
			if(getPosition().x >= roomSize.x)
			{
				RoofDirection = true;
			}
		}
	}
}


void Spider::walkBackToTop()
{
	b2Body *body = mRigidbody.getBody();
	
	if(getPosition().x > roomStart.x + 200)
	{
		mSprite = walkingAnimation.getCurrentSprite();
		b2Vec2 move = Rigidbody::SfToBoxVec(getPosition());
		move.x -= 0.05;
		mSprite.setScale(1, 1);
		body->SetTransform(move, 0);
	}
	else
	{
		mSprite = walkingAnimation.getCurrentSprite();
		mSprite.setRotation(90);
		
		b2Vec2 putBack = Rigidbody::SfToBoxVec(getPosition());
		putBack.x = Rigidbody::SfToBoxFloat(roomStart.x + 128);
		body->SetTransform(putBack, 0);

		b2Vec2 move = Rigidbody::SfToBoxVec(getPosition());
		move.x = Rigidbody::SfToBoxFloat(roomStart.x + 132);
		move.y += 0.05;
		body->SetTransform(move, 0);
	}

	//checks if spoderMan is back at startHeight and then places him acordingly to that
	if(getPosition().y <= startPosition.y)
	{
		b2Vec2 putBack;
		putBack = Rigidbody::SfToBoxVec(getPosition());
		putBack.y = Rigidbody::SfToBoxFloat(-roomStart.y - startPosition.y);
		body->SetTransform(putBack, 0);
		activateMove = true;
		walkBack = false;
	}

}
