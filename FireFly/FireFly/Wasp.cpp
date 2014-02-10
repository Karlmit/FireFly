#include "Wasp.h"
#include "Utility.h"


Wasp::Wasp(sf::Vector2f position)
	: idleAnimation(Loading::getTexture("placerholderAnimation.png"), 60, 60, 6, 5, 5)
	,mRigidbody()
{
}


Wasp::~Wasp(void)
{
}
