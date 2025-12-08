#include <SFML/Graphics.hpp>
#include "ChessGame.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(1200, 800), "Chess Game", sf::Style::Default);
    window.setFramerateLimit(60);

    sf::Font font;
    if (!font.loadFromFile("C:/Windows/Fonts/times.ttf")) {
        return -1;
    }

    ChessGame game;

    while (window.isOpen()) {
        sf::Event event;
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::Resized) {
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
                game.resize(event.size.width, event.size.height);
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    game.handleMousePress(mousePos);
                }
            }

            if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    game.handleMouseRelease(mousePos);
                }
            }

            if (event.type == sf::Event::KeyPressed) {
                game.handleKeyPress(event.key.code);
            }
        }

        game.update();
        game.render(window, font, mousePos);
    }

    return 0;
}