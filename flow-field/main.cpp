#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>

// Constants
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int SQUARE_SIZE = 10;
const int NUM_BLUE_SQUARES = 50;

// Structure for each square's position and flow direction
struct Square {
    sf::Vector2f position;
    sf::Vector2f velocity;

    Square(sf::Vector2f pos) : position(pos), velocity(0, 0) {}
};

// Flow Field Class
class FlowField {
public:
    FlowField(int width, int height, int cellSize) : width(width), height(height), cellSize(cellSize) {
        field.resize(width / cellSize, std::vector<sf::Vector2f>(height / cellSize));
        generateField();
    }

    // Generate the flow field
    void generateField() {
        // You can adjust this to make the flow field more interesting
        for (int i = 0; i < width / cellSize; ++i) {
            for (int j = 0; j < height / cellSize; ++j) {
                field[i][j] = sf::Vector2f(rand() % 2 - 1, rand() % 2 - 1);  // Random direction
            }
        }
    }

    // Get the flow vector at a specific position
    sf::Vector2f getFlowAtPosition(sf::Vector2f position) {
        int i = position.x / cellSize;
        int j = position.y / cellSize;

        // Make sure we don't go out of bounds
        if (i < 0) i = 0;
        if (j < 0) j = 0;
        if (i >= field.size()) i = field.size() - 1;
        if (j >= field[0].size()) j = field[0].size() - 1;

        return field[i][j];
    }

private:
    int width, height, cellSize;
    std::vector<std::vector<sf::Vector2f>> field;
};

// Function to generate a random position on the screen's edge
sf::Vector2f generateRandomEdgePosition() {
    int side = rand() % 4;

    if (side == 0) { // Top
        return sf::Vector2f(rand() % WINDOW_WIDTH, 0);
    } else if (side == 1) { // Bottom
        return sf::Vector2f(rand() % WINDOW_WIDTH, WINDOW_HEIGHT);
    } else if (side == 2) { // Left
        return sf::Vector2f(0, rand() % WINDOW_HEIGHT);
    } else { // Right
        return sf::Vector2f(WINDOW_WIDTH, rand() % WINDOW_HEIGHT);
    }
}

int main() {
    srand(time(0));

    // Create window
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Flow Field Example");

    // Create the flow field
    FlowField flowField(WINDOW_WIDTH, WINDOW_HEIGHT, 20);

    // Create a green square (target)
    sf::RectangleShape greenSquare(sf::Vector2f(SQUARE_SIZE, SQUARE_SIZE));
    greenSquare.setFillColor(sf::Color::Green);

    // Create a collection of blue squares (agents)
    std::vector<Square> blueSquares;
    for (int i = 0; i < NUM_BLUE_SQUARES; ++i) {
        blueSquares.emplace_back(generateRandomEdgePosition());
    }

    // Main loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed) {
                // Move the green square to the mouse position
                if (event.mouseButton.button == sf::Mouse::Left) {
                    greenSquare.setPosition(event.mouseButton.x - SQUARE_SIZE / 2, event.mouseButton.y - SQUARE_SIZE / 2);
                    flowField.generateField(); // Regenerate the flow field on click
                }
            }
        }

        // Update the movement of the blue squares towards the green square
        for (auto& blueSquare : blueSquares) {
            // Get the flow direction based on the position of the blue square
            sf::Vector2f flow = flowField.getFlowAtPosition(blueSquare.position);

            // Move towards the green square using the flow field as a guide
            sf::Vector2f direction = greenSquare.getPosition() - blueSquare.position;
            float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);
            if (magnitude > 0) {
                direction /= magnitude; // Normalize the direction
            }

            // Update the blue square's velocity based on the flow and direction
            blueSquare.velocity = flow * 0.1f + direction * 0.5f; // Mix the flow and direction for smoother movement

            // Update position
            blueSquare.position += blueSquare.velocity;

            // Check if a blue square touches the green square
            if (std::abs(blueSquare.position.x - greenSquare.getPosition().x) < SQUARE_SIZE &&
                std::abs(blueSquare.position.y - greenSquare.getPosition().y) < SQUARE_SIZE) {
                // Reassign the blue square to a random position on the edge
                blueSquare.position = generateRandomEdgePosition();
            }
        }

        // Clear screen
        window.clear(sf::Color::White);

        // Draw the green square
        window.draw(greenSquare);

        // Draw the blue squares
        for (const auto& blueSquare : blueSquares) {
            sf::RectangleShape blueSquareShape(sf::Vector2f(SQUARE_SIZE, SQUARE_SIZE));
            blueSquareShape.setFillColor(sf::Color::Blue);
            blueSquareShape.setPosition(blueSquare.position);
            window.draw(blueSquareShape);
        }

        // Display everything
        window.display();
    }

    return 0;
}
