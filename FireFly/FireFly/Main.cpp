#include <SFML/Graphics.hpp>
#include "Level.h"
#include "Player.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "FireFly 0.00001");
	Loading::getLoading().loadLevel0();
	Player player(100, 100);
	EntityList::getEntityList().addEntity(&player);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
		Level::getLevel().level0(&window);
        window.display();
    }

    return 0;
}