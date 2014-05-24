#include "Movie.h"

sf::RenderWindow* Movie::sWindow = nullptr;

void Movie::init( sf::RenderWindow* window )
{
	sWindow = window;
}

Movie::Movie(string movieFile)
	: mSfeMovie()
{
	if (!mSfeMovie.openFromFile("Resources/" + movieFile))
		throw runtime_error("Couldn't open movie " + movieFile);
	mSfeMovie.resizeToFrame(0, 0, sWindow->getSize().x, sWindow->getSize().y);
	mSfeMovie.play();
}

void Movie::start()
{
}

void Movie::updateEntity(sf::Time dt)
{
	
}

void Movie::drawEntity(sf::RenderTarget& target, sf::RenderStates states) const
{	
	target.draw(mSfeMovie);
}