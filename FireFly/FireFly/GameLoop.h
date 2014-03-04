#pragma once
#include "Level.h"

#include <SFML/System/Time.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "Camera.h"
#include <Box2D\Box2D.h>

class GameLoop
{
public:
	GameLoop(sf::Vector2u windowSize);
	~GameLoop();

	void run();
private:	
	void operator=(const GameLoop &gameloop);

	void draw();
	void update(sf:: Time timePerFrame);
	void processEvents();
	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
	void updateStatistics(sf::Time elapsedTime);	
	
	static const sf::Time TimePerFrame;
	
	sf::RenderWindow mWindow;
	Camera mCamera;
	sf::Font mFont;
	sf::Text mStatisticsText;
	sf::Time mStatisticsUpdateTime;
	std::size_t	mStatisticsNumFrames;
	sf::String textEntered;
	Entity *pc;
	Entity *zid;
};

