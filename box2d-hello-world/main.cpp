#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <iostream>

int main() {
    // Create SFML window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML & Box2D");

    // Load font
    sf::Font font;
    if (!font.loadFromFile("/System/Library/Fonts/Supplemental/Arial.ttf")) {
        std::cerr << "Could not load font!\n";
        return -1;
    }

    // Create text
    sf::Text text("Hello, SFML & Box2D!", font, 30);
    text.setFillColor(sf::Color::White);
    text.setPosition(200, 250);

    // Set up Box2D world
    b2WorldDef worldDef = b2DefaultWorldDef();
    worldDef.gravity = (b2Vec2){0.0f, -10.0f};
    b2WorldId worldId = b2CreateWorld(&worldDef);

    // Create a Box2D ground body
    b2BodyDef groundBodyDef = b2DefaultBodyDef();
    groundBodyDef.position = (b2Vec2){0.0f, -10.0f};
    b2BodyId groundId = b2CreateBody(worldId, &groundBodyDef);
    
    b2Polygon groundBox = b2MakeBox(50.0f, 10.0f);
    b2ShapeDef groundShapeDef = b2DefaultShapeDef();
    b2CreatePolygonShape(groundId, &groundShapeDef, &groundBox);

    // Create a dynamic body
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(0.0f, 4.0f);
    b2Body* body = world.CreateBody(&bodyDef);

    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(1.0f, 1.0f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    body->CreateFixture(&fixtureDef);

    sf::Clock clock;

    // Main loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Box2D physics step
        float timeStep = clock.restart().asSeconds();
        int32 velocityIterations = 6;
        int32 positionIterations = 2;
        world.Step(timeStep, velocityIterations, positionIterations);

        // Update SFML scene
        window.clear();
        window.draw(text);
        window.display();
    }

    return 0;
}
