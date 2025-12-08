#include "ChessGame.h"

void ChessGame::drawGameOver(sf::RenderWindow& window, sf::Font& font) {
    sf::RectangleShape fullOverlay(sf::Vector2f(windowWidth, windowHeight));
    fullOverlay.setFillColor(sf::Color(0, 0, 0, 180));
    window.draw(fullOverlay);

    sf::RectangleShape bg(sf::Vector2f(580, 380));
    bg.setPosition(windowWidth / 2 - 290, windowHeight / 2 - 190);
    bg.setFillColor(sf::Color(40, 30, 20));
    bg.setOutlineColor(sf::Color(210, 180, 140));
    bg.setOutlineThickness(5);
    window.draw(bg);

    std::string message;
    if (winner == NONE) {
        message = "STALEMATE!";
    }
    else if (winner == WHITE) {
        message = "WHITE WINS!";
    }
    else {
        message = "BLACK WINS!";
    }

    sf::Text title(message, font, 52);
    title.setFillColor(sf::Color::White);
    title.setStyle(sf::Text::Bold);
    title.setPosition(windowWidth / 2 - title.getGlobalBounds().width / 2, windowHeight / 2 - 110);
    window.draw(title);

    sf::Text subtext(winner == NONE ? "DRAW" : "CHECKMATE", font, 32);
    subtext.setFillColor(sf::Color(210, 180, 140));
    subtext.setPosition(windowWidth / 2 - subtext.getGlobalBounds().width / 2, windowHeight / 2 - 45);
    window.draw(subtext);

    sf::RectangleShape menuBtn(sf::Vector2f(280, 75));
    menuBtn.setPosition(windowWidth / 2 - 140, windowHeight / 2 + 40);
    menuBtn.setFillColor(sf::Color(101, 67, 33));
    menuBtn.setOutlineColor(sf::Color(210, 180, 140));
    menuBtn.setOutlineThickness(3);
    window.draw(menuBtn);

    sf::Text menuText("MAIN MENU", font, 36);
    menuText.setFillColor(sf::Color::White);
    menuText.setStyle(sf::Text::Bold);
    menuText.setPosition(windowWidth / 2 - menuText.getGlobalBounds().width / 2, windowHeight / 2 + 57);
    window.draw(menuText);
}

void ChessGame::drawPromotionMenu(sf::RenderWindow& window, sf::Font& font) {
    sf::RectangleShape overlay(sf::Vector2f(windowWidth, windowHeight));
    overlay.setFillColor(sf::Color(0, 0, 0, 200));
    window.draw(overlay);

    sf::RectangleShape bg(sf::Vector2f(380, 340));
    bg.setPosition(windowWidth / 2 - 190, windowHeight / 2 - 170);
    bg.setFillColor(sf::Color(40, 30, 20));
    bg.setOutlineColor(sf::Color(210, 180, 140));
    bg.setOutlineThickness(4);
    window.draw(bg);

    sf::Text title("Promote Pawn To:", font, 32);
    title.setFillColor(sf::Color::White);
    title.setStyle(sf::Text::Bold);
    title.setPosition(windowWidth / 2 - title.getGlobalBounds().width / 2, windowHeight / 2 - 135);
    window.draw(title);

    std::vector<std::string> pieces = { "Queen", "Rook", "Bishop", "Knight" };
    for (int i = 0; i < 4; i++) {
        sf::RectangleShape btn(sf::Vector2f(330, 52));
        btn.setPosition(windowWidth / 2 - 165, windowHeight / 2 - 65 + i * 68);
        btn.setFillColor(sf::Color(101, 67, 33));
        btn.setOutlineColor(sf::Color(210, 180, 140));
        btn.setOutlineThickness(2);
        window.draw(btn);

        sf::Text text(pieces[i], font, 28);
        text.setFillColor(sf::Color::White);
        text.setStyle(sf::Text::Bold);
        text.setPosition(windowWidth / 2 - text.getGlobalBounds().width / 2, windowHeight / 2 - 56 + i * 68);
        window.draw(text);
    }
}