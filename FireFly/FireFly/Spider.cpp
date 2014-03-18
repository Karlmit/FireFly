#include "Spider.h"

const float ATTACK_SPEED = -0.08f;

Spider::Spider(sf::Vector2f position, sf::Vector2f startofRoom, sf::Vector2f sizeofRoom) :
dangleAnimation(Loading::getTexture("spiderHanging_sheet256.png"), 256, 256, 5, 10, 10),
walkingAnimation(Loading::getTexture("spiderwalking1.png"), 256, 256, 2, 8, 65),
walkSound(Loading::getSound("Spiderlegs.wav"), false)
{
	//positions
	//setPosition(position);
	startPosition = position;
	roomStart = startofRoom;
	roomSize.x = startofRoom.x + sizeofRoom.x;
	roomSize.y = startofRoom.y + sizeofRoom.y;
	float colRadius = 60.f;
	float density = 4.f;
	mRigidbody.AddDynCircleBody(colRadius, getPosition(), density, true);
	//sound
	walkSound.getSound()->setMinDistance(200);
	walkSound.getSound()->setLoop(true);
	walkSound.play();

	activate = false;
	//sfVector holding starting position
	
	//setPosition(position);
	mRigidbody.getBody()->SetTransform(Rigidbody::SfToBoxVec(position), 0);
	isonFloor = true;
	spiderman = true;
	mID = "spoderMan";
	mZid = EntityList::getEntityList().getEntity("Zid");

	//spoderMan should begin with walking
	mSugar = false;
	//net
	net.setFillColor(sf::Color::White);
	makeNet = false;
	inRange = true;
	mRopeisCut = false;
	activateMove = true;
	mRigidbody.update();
	setPosition(mRigidbody.getPosition());

	mRigidbody.getBody()->SetUserData(this);
}


Spider::~Spider(void)
{
}

void Spider::sendMessage(Entity* entity, std::string message)
{
	
	if(message == "activate")
	{
		mSugar = true;
	}
	if(isProperty("Sugar") == true)
	{
		if(message == "deactivate")
		{
			mSugar = false;
		}
	}
	
	if(message == "spiderisinRoom" && mSugar == true)
	{
		activate = true;
	}

	if(isProperty("room1") == true && message == "activate")
	{
		activate = true;
	}
	
	if(message == "Deactivate")
	{
		activate = false;
	}

}


void Spider::updateEntity(sf::Time dt)
{
	if(activate == true)
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
		else if(mRopeisCut == true)
		{
			falltoFloor();
		}


		//function that prepares the spoderMan to walkBack to the top
		//Mainly activates walkBackToTop
		if(getPosition().y >= roomSize.y && isonFloor == true)
		{
			spiderman = true;
			activateMove = false;
			makeNet = false;
			walkBack = true;
			//Gives spoderman a specific postion due to sprite size
			body->SetTransform(b2Vec2(Rigidbody::SfToBoxFloat(getPosition().x), Rigidbody::SfToBoxFloat(-(roomSize.y - 128))), 0);
			//resets netLength
			net.setSize(sf::Vector2f(0, 0));

			//Rope is not cut anymore
			mRopeisCut = false;
		}

			
		mRigidbody.update();
		setPosition(mRigidbody.getPosition());
		setRotation(mRigidbody.getRotation());
		//sound
		walkSound.setPosition(getPosition());
	}
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

	//Converts mZidPosition to sfVector
	sf::Vector2f zidPosition = Rigidbody::BoxToSfVec(mZidPosition);

	if(range < 50 && spiderman == true && zidPosition.y > roomStart.y)
	{				
		
			netStart = getPosition();
			net.setPosition(netStart.x + 32, netStart.y - 128);
			float roofToZid = abs(roomStart.y - zidPosition.y);
			body->SetTransform(b2Vec2(Rigidbody::SfToBoxFloat(getPosition().x + 32), Rigidbody::SfToBoxFloat(-(getPosition().y - 64))), 0);

			if(roofToZid > 500)//Zid is not close enough to ceiling to see him jump
			{		
				body->SetTransform(b2Vec2(Rigidbody::SfToBoxFloat(getPosition().x + 32), mZidPosition.y + Rigidbody::SfToBoxFloat(500)), 0);
			}
			spiderman = false; //The spider will scary jump no more. for this time...
			makeNet = true;
			//turns off movement
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
	
	sf::Vector2f zid = Rigidbody::BoxToSfVec(mZidPosition);

	float overSpoderMan = getPosition().y - zid.y;
	//activates func to move spider up the net
	if(zid.y < getPosition().y && range < 40)
		{
			inRange = false;
			makeNet = false;
			mRopeisCut = true;
		}

	//Checks if Zid is to far away from spider
	if(overSpoderMan > 200)
	{
		inRange = false;
	}

	if(range < 200 && inRange == true)
	{
		//MAKE STATIC NET...
		float netLength = abs(netStart.y - getPosition().y);
		sf::Vector2f netSize(4, netLength + 64);
		net.setSize(netSize);

		//moves spoderman down
		b2Vec2 move = Rigidbody::SfToBoxVec(getPosition());
		move.y += ATTACK_SPEED;
		body->SetTransform(move, 0);

		
	}
	else if(mRopeisCut == false)
	{
		inRange = false;
		//Activates func makeNet();
		makeNet = true;

		//MAKE STATIC NET...
		float netLength = abs(netStart.y - getPosition().y);
		sf::Vector2f netSize;
		netSize.y = netLength + 128;
		netSize.x = 4;
		net.setSize(netSize);

		//moves spoderman down
		b2Vec2 move = Rigidbody::SfToBoxVec(getPosition());
		move.y += 0.45f * 0.1f;
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
		b2Vec2 move = b2Vec2(Rigidbody::SfToBoxFloat(getPosition().x), Rigidbody::SfToBoxFloat(-startPosition.y));
		if(RoofDirection)
		{
			move.x -= 0.03f;
			//scales sprite to the left
			mSprite.setScale(-1, 1);
			body->SetTransform(move , 0);
			if(getPosition().x <= roomStart.x)
			{
				RoofDirection = false;
			}
		}
		if(!RoofDirection)
		{
			move.x += 0.03f;			
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
		move.x -= 0.05f;
		mSprite.setScale(1, 1);
		body->SetTransform(move, 0);
		isonFloor = true;
	}
	else
	{
		mSprite = walkingAnimation.getCurrentSprite();
		mSprite.setRotation(90);
		
		b2Vec2 putBack = Rigidbody::SfToBoxVec(getPosition());
		putBack.x = Rigidbody::SfToBoxFloat(roomStart.x + 132);
		body->SetTransform(putBack, 0);

		b2Vec2 move = Rigidbody::SfToBoxVec(getPosition());
		move.x = Rigidbody::SfToBoxFloat(roomStart.x + 132);
		move.y += 0.05f;
		body->SetTransform(move, 0);
		isonFloor = false;
	}

	//checks if spoderMan is back at startHeight and then places him acordingly to that
	if(getPosition().y <= startPosition.y)
	{
		body->SetTransform(b2Vec2(Rigidbody::SfToBoxFloat(getPosition().x), Rigidbody::SfToBoxFloat(-(startPosition.y))), 0);
		activateMove = true;
		walkBack = false;
	}
}

void Spider::falltoFloor()
{
	b2Body *body = mRigidbody.getBody();
	mSprite = dangleAnimation.getCurrentSprite();

	b2Vec2 fallingSpeed = Rigidbody::SfToBoxVec(getPosition());
	fallingSpeed.y -= Rigidbody::SfToBoxFloat(10);
	body->SetTransform(fallingSpeed, 0);
	isonFloor = true;
}