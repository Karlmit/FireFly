#include "Zid.h"
#include "Loading.h"

#include <SFML/Window/Mouse.hpp>
#include "Box2dWorld.h"
#include "Camera.h"

#include <iostream>

Zid::Zid()
: mSprite(Loading::getLoading().getTexture(TexturesID::Zid))
, mRigidbody()
{
	// Sätter origin för spriten till mitten
	sf::FloatRect bounds = mSprite.getLocalBounds();
	mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

	float colRadius = 24.f;
	float density = 3.f;
	mRigidbody.AddDynCircleBody(colRadius, getPosition(), density);

	// Damping for slowing zid down when not moving
	mRigidbody.getBody()->SetLinearDamping(2.f);
	mRigidbody.getBody()->SetFixedRotation(true);
} 




void Zid::updateEntity(sf::Time dt) 
{
	// Box2d physics body
	b2Body* body = mRigidbody.getBody();

	
	// Checks mouse input and apply force on the rigidbody based on that
	movement();
	
	// Change direction on the sprite based on velocity
	if (body->GetLinearVelocity().x < -0.1f) 
	{
		mSprite.setScale(-1.f, 1.f);
	}
	else if (body->GetLinearVelocity().x > 0.1f)
	{
		mSprite.setScale(1.f, 1.f);
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
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right) == true) {

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
		}
			
	}
	else {
		mouseRightDownLast = false;
	}
}
