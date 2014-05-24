#include "Entity.h"
#include "sfeMovie\Movie.hpp"

class Movie : public Entity
{
public:
	static void init(sf::RenderWindow* window);
private:
	static sf::RenderWindow* sWindow;

public:
	Movie(string movieFile);

private:
	virtual void start();
	virtual void updateEntity(sf::Time dt);	
	virtual void drawEntity(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	sfe::Movie mSfeMovie;
};