#include <SFML/Graphics.hpp>
#include "GameLoop.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "FireFly 0.00001");
	Level::getLevel().loadLevel0();
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
		GameLoop::getGameLoop().runPrototype(&window);
        window.clear();
        window.display();
    }

    return 0;
}