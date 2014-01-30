#pragma once
#include "Level.h"

#include <SFML/System/Time.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class GameLoop
{
public:
	static GameLoop &getGameLoop();
	void run();
private:
	GameLoop();
	~GameLoop();
	void operator=(const GameLoop &gameloop);
	static GameLoop gameloop;

	void draw();
	void update(sf:: Time timePerFrame);
	void processEvents();
	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
	void updateStatistics(sf::Time elapsedTime);	
	
	static const sf::Time TimePerFrame;
	
	sf::RenderWindow mWindow;
	//World mWorld;
	sf::Font mFont;
	sf::Text mStatisticsText;
	sf::Time mStatisticsUpdateTime;
	std::size_t	mStatisticsNumFrames;
};

