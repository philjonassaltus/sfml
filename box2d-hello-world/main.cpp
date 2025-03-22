#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <iostream>

// Scale factor for Box2D to SFML conversion
const float SCALE = 30.0f;

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
    text.setPosition(200, 50);

    // Set up Box2D world
    b2WorldDef worldDef = b2DefaultWorldDef();
    worldDef.gravity = (b2Vec2){0.0f, 10.0f};
    b2WorldId worldId = b2CreateWorld(&worldDef);

    // Create a Box2D ground body
    b2BodyDef groundBodyDef = b2DefaultBodyDef();
    groundBodyDef.position = (b2Vec2){400.0f / SCALE, 550.0f / SCALE};  // Centered in window
    b2BodyId groundId = b2CreateBody(worldId, &groundBodyDef);

    b2Polygon groundBox = b2MakeBox(400.0f / SCALE, 10.0f / SCALE);
    b2ShapeDef groundShapeDef = b2DefaultShapeDef();
    b2CreatePolygonShape(groundId, &groundShapeDef, &groundBox);

    // Create an SFML rectangle for the ground
    sf::RectangleShape groundRect(sf::Vector2f(800, 20));
    groundRect.setFillColor(sf::Color::Green);
    groundRect.setOrigin(400, 10);
    groundRect.setPosition(400, 550);

    // Create a dynamic body
    b2BodyDef bodyDef = b2DefaultBodyDef();
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = (b2Vec2){400.0f / SCALE, 200.0f / SCALE};
    b2BodyId bodyId = b2CreateBody(worldId, &bodyDef);

    b2Polygon dynamicBox = b2MakeBox(30.0f / SCALE, 30.0f / SCALE);
    b2ShapeDef shapeDef = b2DefaultShapeDef();
    shapeDef.density = 1.0f;
    shapeDef.friction = 0.3f;
    b2CreatePolygonShape(bodyId, &shapeDef, &dynamicBox);

    // Create an SFML rectangle for the Box2D dynamic body
    sf::RectangleShape box(sf::Vector2f(60, 60));
    box.setFillColor(sf::Color::Blue);
    box.setOrigin(30, 30);

    // Physics step settings
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

        // Get body position and rotation
        b2Vec2 position = b2Body_GetPosition(bodyId);
        b2Rot rotation = b2Body_GetRotation(bodyId);

        // Update SFML rectangle position & rotation
        box.setPosition(position.x * SCALE, position.y * SCALE);
        box.setRotation(b2Rot_GetAngle(rotation) * 180.0f / b2_pi);

        // Render scene
        window.clear();
        window.draw(text);
        window.draw(groundRect);
        window.draw(box);
        window.display();
    }

    b2DestroyWorld(worldId);
    return 0;
}
