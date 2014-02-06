//#include <SFML/Graphics.hpp>
#include "GameLoop.h"
#include <iostream>
#include <stdexcept>



int main()
{	
	try
	{	
		// Creates the window relative to desktop resolution
		// Temporary, should probably be in fullscreen for release
		sf::Vector2u windowSize;
		windowSize.x = unsigned(sf::VideoMode::getDesktopMode().width*0.8f);
		windowSize.y = unsigned(sf::VideoMode::getDesktopMode().height*0.8f);
		// Creates the GameLoop
		GameLoop gameLoop(windowSize);

		gameLoop.run();
	}
	catch (std::exception& e)
	{
		std::cout << "\nEXCEPTION: " << e.what() << std::endl;
		char c;
		std::cin >> c;
	}
}
