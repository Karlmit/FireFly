#pragma once
#include "Level.h"

#include <SFML/System/Time.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "PC.h"
#include "Zid.h"
#include "Light.h"

#include "Camera.h"
#include <Box2D\Box2D.h>

#include "SimpleMenu.h"

class GameLoop
{
public:
	GameLoop		(sf::Vector2u windowSize);
	~GameLoop();

	void run();
private:	
	void operator=(const GameLoop &gameloop);

	void draw();
	void update(sf:: Time timePerFrame);
	void processEvents();
	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
	void updateStatistics(sf::Time elapsedTime);
	void preloadLevels(string startLevel);
	
	static const sf::Time TimePerFrame;
	
	sf::RenderWindow mWindow;
	Camera mCamera;
	sf::Font mFont;
	sf::Text mStatisticsText;
	sf::Time mStatisticsUpdateTime;
	std::size_t	mStatisticsNumFrames;
	sf::String textEntered;
	Entity* pc;
	Entity* zid;
	sf::Sprite cursorSprite;
	Entity* mZidsLight;
	sf::Texture hivemind;
	sf::Sprite hivemindProjection;
	Zid* zidCast;
	Light* lightCast;
	SimpleMenu mSimpleMenu;
};

