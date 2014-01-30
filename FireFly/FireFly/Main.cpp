//#include <SFML/Graphics.hpp>
#include "GameLoop.h"
#include <iostream>
#include <stdexcept>


int main()
{
	Level::getLevel().startLevel0();
	try
	{
		GameLoop::getGameLoop().run();
	}
	catch (std::exception& e)
	{
		std::cout << "\nEXCEPTION: " << e.what() << std::endl;
	}

}

//int main()
//{
//    sf::RenderWindow window(sf::VideoMode(800, 600), "FireFly 0.00001");
//	window.setFramerateLimit(60);
//	Level::getLevel().startLevel0();
//    while (window.isOpen())
//    {
//        sf::Event event;
//        while (window.pollEvent(event))
//        {
//            if (event.type == sf::Event::Closed)
//                window.close();
//        }
//		
//        window.clear(sf::Color::Magenta);
//		GameLoop::getGameLoop().runPrototype(&window);
//        window.display();
//    }
//
//    return 0;
//}