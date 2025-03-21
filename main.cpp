#include <SFML/Graphics.hpp>

sf::Vector2f normalise_vector(float w, float h, float dist)
{
    return sf::Vector2f(w/dist, h/dist);
}

void circle_constraint(sf::CircleShape &anchor, sf::CircleShape &target, float constraint)
{
    float width = anchor.getPosition().x - target.getPosition().x;
    float height = anchor.getPosition().y - target.getPosition().y;
    float distance = std::sqrt(width * width + height * height);
    if(distance < constraint){
        return;
    }

    // get unit vector
    sf::Vector2f unit = normalise_vector(width, height, distance);

    // multiply unit vector by constraint
    sf::Vector2f projection = sf::Vector2f(unit.x * constraint, unit.y * constraint) + target.getPosition();

    // constrain follower
    target.setPosition(projection);
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Circle Constraints");
    sf::CircleShape shape(50.f);
    shape.setFillColor(sf::Color::Green);

    sf::CircleShape follower(50.f);
    follower.setFillColor(sf::Color::Red);

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

        circle_constraint(shape, follower, 100.f);

        // DRAW
        window.clear();
        window.draw(follower);
        window.draw(shape);
        window.display();
    }

    return 0;
}