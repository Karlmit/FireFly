#include "GameLoop.h"
#include "Box2dWorld.h"

GameLoop GameLoop::gameloop;

const sf::Time GameLoop::TimePerFrame = sf::seconds(1.f/60.f);

GameLoop::GameLoop()
	: mWindow(sf::VideoMode(1600, 900), "Firefly", sf::Style::Default),
	mCamera(&mWindow),
	mFont(),
	mStatisticsText(),
	mStatisticsUpdateTime(),
	mStatisticsNumFrames(0)
{
	mWindow.setVerticalSyncEnabled(true);
	mFont.loadFromFile("Resources/Sansation.ttf");
	mStatisticsText.setFont(mFont);
	mStatisticsText.setPosition(5.f, 5.f);
	mStatisticsText.setCharacterSize(12);

	
}


GameLoop::~GameLoop()
{
}

GameLoop &GameLoop::getGameLoop()
{
	return gameloop;
}

void GameLoop::run()
{
	// Temp load first level
	Level::getLevel().startLevel0();

	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (mWindow.isOpen())
	{
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;

			processEvents();
			update(TimePerFrame);

		}

		updateStatistics(elapsedTime);
		draw();
	}
}

void GameLoop::processEvents()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::KeyPressed:
				handlePlayerInput(event.key.code, true);
				break;

			case sf::Event::KeyReleased:
				handlePlayerInput(event.key.code, false);
				break;

			case sf::Event::Closed:
				mWindow.close();
				break;
		}
	}
}


void GameLoop::draw()
{
	mWindow.clear(sf::Color::Black);

	mWindow.setView(mCamera.getView());
	EntityList::getEntityList().draw(mWindow);	// Draws all entities

	mWindow.setView(mWindow.getDefaultView());
	mWindow.draw(mStatisticsText);

	mWindow.display();
}

void GameLoop::update(sf:: Time timePerFrame)
{
	// Update camera
	mCamera.update(timePerFrame);

	// Update entities
	EntityList::getEntityList().updateList(); //deletes dead entities
	EntityList::getEntityList().update(TimePerFrame);	// Updates all entities

	// Box2d physics step
	float32 timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;
	Box2dWorld::instance().Step(timeStep, velocityIterations, positionIterations);
}

void GameLoop::updateStatistics(sf::Time elapsedTime)
{
	mStatisticsUpdateTime += elapsedTime;
	mStatisticsNumFrames += 1;

	if (mStatisticsUpdateTime >= sf::seconds(1.0f))
	{
		mStatisticsText.setString( 
			"Frames / Second = " + std::to_string(mStatisticsNumFrames));// + "\n" +
			//"Time / Update = " + std::to_string(mStatisticsUpdateTime.asMicroseconds() / mStatisticsNumFrames) + "us");
							 
		mStatisticsUpdateTime -= sf::seconds(1.0f);
		mStatisticsNumFrames = 0; 
	}
}

void GameLoop::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	if (key == sf::Keyboard::Escape && isPressed == true)
		mWindow.close();

	if (key == sf::Keyboard::F12 && isPressed)
		Globals::DEBUG_MODE = !Globals::DEBUG_MODE;
}

