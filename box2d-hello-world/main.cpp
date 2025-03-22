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
    b2BodyDef bodyDef = b2DefaultBodyDef();
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = (b2Vec2){0.0f, 4.0f};
    b2BodyId bodyId = b2CreateBody(worldId, &bodyDef);

    b2Polygon dynamicBox = b2MakeBox(1.0f, 1.0f);
    b2ShapeDef shapeDef = b2DefaultShapeDef();
    shapeDef.density = 1.0f;
    shapeDef.friction = 0.3f;
    b2CreatePolygonShape(bodyId, &shapeDef, &dynamicBox);

    int subStepCount = 4;

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
        b2World_Step(worldId, timeStep, subStepCount);
        b2Vec2 position = b2Body_GetPosition(bodyId);
        b2Rot rotation = b2Body_GetRotation(bodyId);
        printf("%4.2f %4.2f %4.2f\n", position.x, position.y, b2Rot_GetAngle(rotation));

        // Update SFML scene
        window.clear();
        window.draw(text);
        window.display();
    }

    b2DestroyWorld(worldId);
    return 0;
}
