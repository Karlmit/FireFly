#include "Jar.h"
#include <iostream>

Jar::Jar(string texture, sf::Vector2f position)
: mRigidbody()
, mSprite(Loading::getTexture(texture))
{
	// Sätter origin för spriten till mitten
	sf::FloatRect bounds = mSprite.getLocalBounds();
	mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);


	// Skapar rectanglar för kollision för Burken
	float glassWidthAdjust = 25.f;
	float glassHeightAdjust = 4.f;

	bounds.left += glassWidthAdjust;
	bounds.top += glassHeightAdjust;
	bounds.width = bounds.width - 2*glassWidthAdjust;
	bounds.height = bounds.height - 2*glassHeightAdjust;
	
	float width = 20.f;
	std::vector<sf::FloatRect> rects;
	//Left
	rects.push_back(sf::FloatRect(-bounds.width/2, -bounds.height/2, width, bounds.height));
	//Top
	rects.push_back(sf::FloatRect(-bounds.width/2, -bounds.height/2, bounds.width, width));
	//Bottom
	rects.push_back(sf::FloatRect(-bounds.width/2, bounds.height/2-width, bounds.width, width));
	//Right
	rects.push_back(sf::FloatRect(bounds.width/2-width, -bounds.height/2, width, bounds.height));

	float density = 2.f;
	mRigidbody.AddDynRectBody(rects, position, density);

	// Adds itself to body data for collision callbacks
	mRigidbody.getBody()->SetUserData(static_cast<b2ContactListener*>(this));
}


void Jar::updateEntity(sf::Time dt) 
{
	// Get the position and rotation from the rigidbody
	mRigidbody.update();				
	setPosition(mRigidbody.getPosition());
	setRotation(mRigidbody.getRotation());
}
		
void Jar::drawEntity(sf::RenderTarget& target, sf::RenderStates states) const
{	
	states.transform *= getTransform();
	target.draw(mSprite, states);

	// Rigidbody debug draw
	if (Globals::DEBUG_MODE)
		mRigidbody.drawDebug(target, states);
}

// Start of AABB boxes overlapping
void Jar::BeginContact(b2Contact *contact)
{
	if (contact->GetFixtureA()->GetBody() == mRigidbody.getBody())
	{
		//std::cout << mRigidbody.getBody()->GetLinearVelocity().Length() << " ";
	}
	else
	{
		//std::cout << mRigidbody.getBody()->GetLinearVelocity().Length() << " ";
	}
}

// Post box2d solving col. Checks impulse of strength of impact
void Jar::PostSolve(b2Contact *contact, const b2ContactImpulse *impulse)
{
	float imp = max(impulse->normalImpulses[0], impulse->normalImpulses[1]);

	if (imp > 20.f)
	{
		cout << imp << " Destroying jar." << endl;
		killEntity();
	}
}