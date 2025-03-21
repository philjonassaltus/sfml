#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Circle Constraints");
    sf::CircleShape shape(50.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // UPDATE
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            shape.move(-0.1f, 0.f);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            shape.move(0.1f, 0.f);
        }

         if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            shape.move(0.f, -0.1f);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            shape.move(0.f, 0.1f);
        }


        // DRAW

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}