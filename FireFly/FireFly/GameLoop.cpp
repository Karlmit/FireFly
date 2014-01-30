#include "GameLoop.h"


GameLoop GameLoop::gameloop;

const sf::Time GameLoop::TimePerFrame = sf::seconds(1.f/60.f);

GameLoop::GameLoop()
	: mWindow(sf::VideoMode(800, 600), "FireFly", sf::Style::Default),
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
	mWindow.clear(sf::Color::Magenta);
	for(EntityList::entityList::iterator i = EntityList::getEntityList().listedEntities.begin(); i != EntityList::getEntityList().listedEntities.end(); i++)
	{
		mWindow.draw((*i)->getSprite());
	}
	mWindow.draw(mStatisticsText);
	mWindow.setView(mWindow.getDefaultView());
	mWindow.display();
}

void GameLoop::update(sf:: Time timePerFrame)
{
	EntityList::getEntityList().updateList(); //deletes dead entities
	for(EntityList::entityList::iterator i = EntityList::getEntityList().listedEntities.begin(); i != EntityList::getEntityList().listedEntities.end(); i++)
	{
		(*i)->updateEntity(timePerFrame);

	}
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
}

