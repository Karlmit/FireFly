#include <SFML/Graphics.hpp>
#include "Level.h"

Level level;

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "FireFly 0.00001");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

		level.level0(&window);
        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}