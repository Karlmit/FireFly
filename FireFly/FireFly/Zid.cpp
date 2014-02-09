#include "Zid.h"
#include "Loading.h"

#include <SFML/Window/Mouse.hpp>
#include "Box2dWorld.h"
#include "Camera.h"

#include <iostream>

Zid::Zid(sf::Vector2f position)
: mSprite(Loading::getTexture("zid.png"))
,idleAnimation(Loading::getTexture("testspide.png", true), 128, 128, 150, 15, 10, 10)
,dashAnimation(Loading::getTexture("explosionAnim.png"), 64, 64, 25, 5, 2, 5)
,dashSound(Loading::getSound("canary.wav"), true)
,mRigidbody()
{
	// Sätter origin för spriten till mitten
	sf::FloatRect bounds = mSprite.getLocalBounds();
	mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

	// Sätter startposition
	setPosition(position);

	// Sätter camerans start position
	Camera::currentCamera().setPosition(position);
	Camera::currentCamera().setTargetPosition(position);

	// Adds a dynamic circle body to zid
	float colRadius = 24.f;
	float density = 3.f;
	mRigidbody.AddDynCircleBody(colRadius, getPosition(), density);

	// Damping for slowing zid down when not moving
	mRigidbody.getBody()->SetLinearDamping(2.f);
	mRigidbody.getBody()->SetFixedRotation(true);

	// Set zid as bullet to prevent going through stuff
	mRigidbody.getBody()->SetBullet(true);

	mID = "Zid";
	dashFrameNo = 0;
} 



void Zid::updateEntity(sf::Time dt) 
{
	// S?ger att allt ljud som Zid g?r ska h?ras fr?n Zid.
	sf::Listener::setPosition(getPosition().x, 1, getPosition().y);
	
	if(zidDash == true)
	{
		if(dashFrameNo < dashAnimation.getAnimLength())
		{
			dashFrameNo++;
			dashAnimation.updateAnimation();
			mSprite = dashAnimation.getCurrentSprite();
		}
		else
		{
		dashFrameNo = 0;
		zidDash = false;
		idleAnimation.updateAnimation();
		mSprite = idleAnimation.getCurrentSprite();
		}
	}
	else
	{
		dashFrameNo = 0;
		zidDash = false;
		idleAnimation.updateAnimation();
		mSprite = idleAnimation.getCurrentSprite();
	}

	

	// Box2d physics body
	b2Body* body = mRigidbody.getBody();

	
	// Checks mouse input and apply force on the rigidbody based on that
	movement();
	
	
//	sf::Vector2f mousePos = Camera::currentCamera().getMousePosition();
//	b2Vec2 mouse = Rigidbody::SfToBoxVec(mousePos);
//	b2Vec2 viewDirection = mouse - Rigidbody::SfToBoxVec(getPosition());
//	//float length = viewDirection.Normalize();

	// Change direction on the sprite based on velocity
	
	if (body->GetLinearVelocity().x < -0.1f) 
	{
		mDirLeft = true;
		mSprite.setScale(-1.f, 1.f);
	}
	else if (body->GetLinearVelocity().x > 0.1f)
	{
		mDirLeft = false;
		mSprite.setScale(1.f, 1.f);
	}
	else if(body->GetLinearVelocity().x >= -0.1f && 0.1f >= body->GetLinearVelocity().x)
	{
		if(mDirLeft == true)
		{
			mSprite.setScale(-1.f, 1.f);
		}
		else
		{
			mSprite.setScale(1.f, 1.f);
		}
	}


	// Set the camera to follow zid
	Camera::currentCamera().setTargetPosition(getPosition());

	// Get the position and rotation from the rigidbody
	mRigidbody.update();				
	setPosition(mRigidbody.getPosition());
	setRotation(mRigidbody.getRotation());
}
		
void Zid::drawEntity(sf::RenderTarget& target, sf::RenderStates states) const
{	
	states.transform *= getTransform();
	//target.draw(idleAnimation.getCurrentSprite(), states);
	target.draw(mSprite, states);

	// Rigidbody debug draw
	if (Globals::DEBUG_MODE)
		mRigidbody.drawDebug(target, states);
}

void Zid::movement()
{
	// Box2d physics body
	b2Body* body = mRigidbody.getBody();


	// Counter gravity
	body->ApplyForce(body->GetMass() * - b2Vec2(0,-10.f), body->GetWorldCenter(), true);

	
	// Apply force to go to the mouse position when pressing left mouse button
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) == true) {
		sf::Vector2f mousePos = Camera::currentCamera().getMousePosition();

		b2Vec2 mouse = Rigidbody::SfToBoxVec(mousePos);
		b2Vec2 force = mouse - Rigidbody::SfToBoxVec(getPosition());
		float length = force.Normalize();

		if (length > 0.5f) {
			
			force *= 12.f;
			body->ApplyForceToCenter(force, true);
		}	
	}

	// Apply impulse for the right mouse button
	static bool mouseRightDownLast = false;
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right) == true) 
	{
		if (mouseRightDownLast) {
			//mouseRightDownLast = false;
		}
		else {
			mouseRightDownLast = true;

			sf::Vector2f mousePos = Camera::currentCamera().getMousePosition();

			b2Vec2 mouse = Rigidbody::SfToBoxVec(mousePos);
			b2Vec2 force = mouse - Rigidbody::SfToBoxVec(getPosition());
			float length = force.Normalize();
			force *= 10.f;

			body->ApplyLinearImpulse(force , body->GetWorldCenter(), true);
			zidDash = true;

			//Temporary until a real dashsound
			//dashSound.play();
		}
			
	}
	else {
		mouseRightDownLast = false;
	}


	// Debug teleport ability with F11 and mouse position
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F11))
	{
		body->SetTransform(Rigidbody::SfToBoxVec(Camera::currentCamera().getMousePosition()), 0);
	}

}
