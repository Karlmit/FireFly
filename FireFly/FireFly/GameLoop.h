#pragma once
#include "Level.h"
class GameLoop
{
public:
	static GameLoop &getGameLoop();
	void runPrototype(sf::RenderWindow *window);
private:
	GameLoop();
	~GameLoop();
	void operator=(const GameLoop &gameloop);
	static GameLoop gameloop;
	void draw(sf::RenderWindow *window);
	void update();
};

