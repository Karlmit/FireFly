#include "Telefonsvarare.h"


Telefonsvarare::Telefonsvarare(string textureID ,sf::Vector2f position) 
: mSprite(Loading::getTexture(textureID))
, mMessageLeft(true)
, mAudioMessage(Loading::getSound("canary.wav"), false)
{
	// Sätter origin för spriten till mitten
	sf::FloatRect bounds = mSprite.getLocalBounds();
	mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

	setPosition(position);
	mAudioMessage.setPosition(position);

	// Text
	mFont.loadFromFile("Resources/DS-DIGI.ttf");
	mMessageText.setFont(mFont);
	mMessageText.setColor(sf::Color::Yellow);
	mMessageText.setCharacterSize(26);
	mMessageText.setString("1");
	mMessageText.setPosition(sf::Vector2f(-60, -80));

	// Trigger
	sf::FloatRect rect;
	rect.left = position.x - bounds.width/2 + 40;
	rect.top = position.y - bounds.height/2 + 110;
	rect.width = bounds.width - 55;
	rect.height = bounds.height - 110;
	mRigidbody.AddTriggerBoxBody(rect);
	mRigidbody.getBody()->SetUserData(this);
}

void Telefonsvarare::updateEntity(sf::Time dt) 
{	
	
}
		
void Telefonsvarare::drawEntity(sf::RenderTarget& target, sf::RenderStates states) const
{	
	states.transform *= getTransform();
	target.draw(mSprite, states);
	target.draw(mMessageText, states);

	if (Globals::DEBUG_MODE)
		mRigidbody.drawDebug(target, states);
}

void Telefonsvarare::sendMessage(Entity* sender, string message)
{

}

void Telefonsvarare::BeginContact(b2Contact *contact, Entity* other)
{
	if (!mMessageLeft)
		return;

	if (other->getID() == "Zid")
	{
		mAudioMessage.play();
		mMessageLeft = false;
		mMessageText.setString("0");
	}
}

void Telefonsvarare::EndContact(b2Contact *contact, Entity* other)
{
}