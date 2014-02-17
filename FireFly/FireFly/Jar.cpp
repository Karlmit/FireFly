#include "Jar.h"
#include <iostream>
#include "EntityList.h"
#include "AudioEntity.h"
#include "MusicManager.h"



Jar::Jar(string texture, sf::Vector2f position, float density, bool dynamic)
: mRigidbody()
, mSprite(Loading::getTexture(texture, true))
, mBreakSound(Loading::getSound("BurkKross_edit.wav"), false)
, mBroken(false)
{
	// Set sound prop
	mBreakSound.getSound()->setMinDistance(600.f);
	mBreakSound.getSound()->setAttenuation(1.f);

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

	
	
	mRigidbody.AddDynRectBody(rects, position, density, dynamic);

	// Adds itself to body data for collision callbacks
	mRigidbody.getBody()->SetUserData(this);

	
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
void Jar::BeginContact(b2Contact *contact, Entity* other)
{
	if (isProperty("unbreakable"))
		return;

	if (other->getID() == "BurkDeathZone")
	{
		killEntity();
		mBreakSound.setPosition(getPosition());
		// Creates a new entity for playing break after the Jar is dead
		EntityList::getEntityList().addEntity(new AudioEntity(mBreakSound));

		if (isProperty("OnBreakMusicFade"))
			MusicManager::fadeUp(getProperty("OnBreakMusicFade"));
	}
}

