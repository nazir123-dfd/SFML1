#include "ChessGame.h"

void ChessGame::drawMenu(sf::RenderWindow& window, sf::Font& font) {
    if (backgroundTex.getSize().x > 0) {
        sf::Sprite bgSprite(backgroundTex);
        float scaleX = windowWidth / backgroundTex.getSize().x;
        float scaleY = windowHeight / backgroundTex.getSize().y;
        float scale = std::max(scaleX, scaleY);
        bgSprite.setScale(scale, scale);
        float offsetX = (windowWidth - backgroundTex.getSize().x * scale) / 2;
        float offsetY = (windowHeight - backgroundTex.getSize().y * scale) / 2;
        bgSprite.setPosition(offsetX, offsetY);
        window.draw(bgSprite);

        sf::RectangleShape overlay(sf::Vector2f(windowWidth, windowHeight));
        overlay.setFillColor(sf::Color(0, 0, 0, 160));
        window.draw(overlay);
    }
    else {
        sf::RectangleShape bg(sf::Vector2f(windowWidth, windowHeight));
        bg.setFillColor(sf::Color(60, 45, 30));
        window.draw(bg);
    }

    sf::RectangleShape titleBox(sf::Vector2f(700, 130));
    titleBox.setPosition(windowWidth / 2 - 350, 60);
    titleBox.setFillColor(sf::Color(30, 20, 15, 230));
    titleBox.setOutlineColor(sf::Color(218, 165, 32));
    titleBox.setOutlineThickness(4);
    window.draw(titleBox);

    sf::Text title("CHESS MASTER", font, 68);
    title.setFillColor(sf::Color(255, 215, 0));
    title.setStyle(sf::Text::Bold);
    title.setPosition(windowWidth / 2 - title.getGlobalBounds().width / 2, 90);
    window.draw(title);

    sf::Text subtitle("Choose your game mode", font, 22);
    subtitle.setFillColor(sf::Color(218, 165, 32));
    subtitle.setStyle(sf::Text::Italic);
    subtitle.setPosition(windowWidth / 2 - subtitle.getGlobalBounds().width / 2, 210);
    window.draw(subtitle);

    std::vector<std::string> options = {
        "PLAYER VS PLAYER",
        "PLAYER VS AI (EASY)",
        "PLAYER VS AI (MEDIUM)",
        "PLAYER VS AI (HARD)",
        "INSTRUCTIONS"
    };

    for (int i = 0; i < options.size(); i++) {
        float btnY = 260 + i * 80;

        sf::RectangleShape btn(sf::Vector2f(420, 65));
        btn.setPosition(windowWidth / 2 - 210, btnY);
        btn.setFillColor(sf::Color(40, 26, 13, 230));
        btn.setOutlineColor(sf::Color(218, 165, 32));
        btn.setOutlineThickness(3);
        window.draw(btn);

        sf::Text text(options[i], font, 28);
        text.setFillColor(sf::Color(255, 255, 255));
        text.setStyle(sf::Text::Bold);
        text.setPosition(windowWidth / 2 - text.getGlobalBounds().width / 2, btnY + 18);
        window.draw(text);
    }
}

void ChessGame::drawInstructions(sf::RenderWindow& window, sf::Font& font) {
    if (backgroundTex.getSize().x > 0) {
        sf::Sprite bgSprite(backgroundTex);
        float scaleX = windowWidth / backgroundTex.getSize().x;
        float scaleY = windowHeight / backgroundTex.getSize().y;
        float scale = std::max(scaleX, scaleY);
        bgSprite.setScale(scale, scale);
        float offsetX = (windowWidth - backgroundTex.getSize().x * scale) / 2;
        float offsetY = (windowHeight - backgroundTex.getSize().y * scale) / 2;
        bgSprite.setPosition(offsetX, offsetY);
        window.draw(bgSprite);

        sf::RectangleShape overlay(sf::Vector2f(windowWidth, windowHeight));
        overlay.setFillColor(sf::Color(0, 0, 0, 180));
        window.draw(overlay);
    }
    else {
        sf::RectangleShape bg(sf::Vector2f(windowWidth, windowHeight));
        bg.setFillColor(sf::Color(30, 20, 15));
        window.draw(bg);
    }

    sf::RectangleShape mainPanel(sf::Vector2f(800, 620));
    mainPanel.setPosition(windowWidth / 2 - 400, windowHeight / 2 - 310);
    mainPanel.setFillColor(sf::Color(25, 18, 12, 240));
    mainPanel.setOutlineColor(sf::Color(218, 165, 32));
    mainPanel.setOutlineThickness(4);
    window.draw(mainPanel);

    sf::Text title("HOW TO PLAY", font, 56);
    title.setFillColor(sf::Color(255, 215, 0));
    title.setStyle(sf::Text::Bold);
    title.setPosition(windowWidth / 2 - title.getGlobalBounds().width / 2, windowHeight / 2 - 270);
    window.draw(title);

    std::vector<std::string> instructions = {
        "Click on a piece to select it",
        "Click on highlighted square to move",
        "Drag and drop pieces to move",
        "",
        "Press H to toggle hints",
        "Press U to undo move",
        "",
        "10 minute timer for each player",
        "Choose AI difficulty or play with a friend"
    };

    float startY = windowHeight / 2 - 180;
    int actualLine = 0;

    for (int i = 0; i < instructions.size(); i++) {
        if (instructions[i] == "") {
            sf::RectangleShape divider(sf::Vector2f(660, 2));
            divider.setPosition(windowWidth / 2 - 330, startY + actualLine * 42 + 18);
            divider.setFillColor(sf::Color(218, 165, 32, 120));
            window.draw(divider);
            actualLine++;
            continue;
        }

        sf::CircleShape bullet(5);
        bullet.setFillColor(sf::Color(218, 165, 32));
        bullet.setPosition(windowWidth / 2 - 330, startY + actualLine * 42 + 5);
        window.draw(bullet);

        sf::Text text(instructions[i], font, 22);
        text.setFillColor(sf::Color(240, 240, 240));
        text.setPosition(windowWidth / 2 - 310, startY + actualLine * 42);
        window.draw(text);
        actualLine++;
    }

    sf::RectangleShape backBtn(sf::Vector2f(280, 60));
    backBtn.setPosition(windowWidth / 2 - 140, windowHeight / 2 + 220);
    backBtn.setFillColor(sf::Color(40, 26, 13));
    backBtn.setOutlineColor(sf::Color(218, 165, 32));
    backBtn.setOutlineThickness(3);
    window.draw(backBtn);

    sf::Text backText("BACK TO MENU", font, 26);
    backText.setFillColor(sf::Color(255, 255, 255));
    backText.setStyle(sf::Text::Bold);
    backText.setPosition(windowWidth / 2 - backText.getGlobalBounds().width / 2, windowHeight / 2 + 233);
    window.draw(backText);
}

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
    }//text
}