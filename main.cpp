#include <SFML/Graphics.hpp>
#include <cmath>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Maroon Heart");

    // Create a heart shape using a parametric equation
    sf::ConvexShape heart;
    int numPoints = 100;
    heart.setPointCount(numPoints);//blah blah blH

    // Maroon color (RGB: 128, 0, 0)
    sf::Color maroon(128, 0, 0);//jcfncjhbch
    heart.setFillColor(maroon);

    // Generate heart shape using parametric equations
    float scale = 15.0f;
    float centerX = 400.0f;
    float centerY = 280.0f;

    for (int i = 0; i < numPoints; i++) {
        float t = (2.0f * 3.14159f * i) / numPoints;
        float x = 16 * pow(sin(t), 3);
        float y = -(13 * cos(t) - 5 * cos(2 * t) - 2 * cos(3 * t) - cos(4 * t));

        heart.setPoint(i, sf::Vector2f(centerX + x * scale, centerY + y * scale));
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);

        // Draw heart
        window.draw(heart);

        window.display();
    }

    return 0;
}