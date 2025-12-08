#include "ChessGame.h"

void ChessGame::drawMenu(sf::RenderWindow& window, sf::Font& font) {
    if (backgroundTex.getSize().x > 0) {
        sf::Sprite bgSprite(backgroundTex);
        float scaleX = (float)windowWidth / backgroundTex.getSize().x;
        float scaleY = (float)windowHeight / backgroundTex.getSize().y;
        float scale = std::max(scaleX, scaleY);
        bgSprite.setScale(scale, scale);
        float offsetX = (windowWidth - backgroundTex.getSize().x * scale) / 2.0f;
        float offsetY = (windowHeight - backgroundTex.getSize().y * scale) / 2.0f;
        bgSprite.setPosition(offsetX, offsetY);
        window.draw(bgSprite);

        sf::RectangleShape overlay(sf::Vector2f((float)windowWidth, (float)windowHeight));
        overlay.setFillColor(sf::Color(0, 0, 0, 140));
        window.draw(overlay);
    }
    else {
        sf::RectangleShape bg(sf::Vector2f((float)windowWidth, (float)windowHeight));
        bg.setFillColor(sf::Color(50, 50, 50));
        window.draw(bg);
    }

    float centerX = windowWidth / 2.0f;

    sf::RectangleShape titleBox(sf::Vector2f(620, 100));
    titleBox.setPosition(centerX - 310, 50);
    titleBox.setFillColor(sf::Color(20, 20, 15, 200));
    titleBox.setOutlineColor(sf::Color(218, 165, 32));
    titleBox.setOutlineThickness(4);
    window.draw(titleBox);

    sf::Text title("CHESS MASTER", font, 60);
    title.setFillColor(sf::Color(218, 165, 32));
    title.setStyle(sf::Text::Bold);
    title.setPosition(centerX - title.getGlobalBounds().width / 2, 70);
    window.draw(title);

    sf::CircleShape leftDot1(8);
    leftDot1.setFillColor(sf::Color(218, 165, 32));
    leftDot1.setPosition(centerX - 330, 92);
    window.draw(leftDot1);

    sf::CircleShape rightDot1(8);
    rightDot1.setFillColor(sf::Color(218, 165, 32));
    rightDot1.setPosition(centerX + 314, 92);
    window.draw(rightDot1);

    sf::CircleShape leftDot2(6);
    leftDot2.setFillColor(sf::Color(160, 130, 70));
    leftDot2.setPosition(centerX - 320, 118);
    window.draw(leftDot2);

    sf::CircleShape rightDot2(6);
    rightDot2.setFillColor(sf::Color(160, 130, 70));
    rightDot2.setPosition(centerX + 314, 118);
    window.draw(rightDot2);

    sf::Text subtitle("Choose your game mode", font, 20);
    subtitle.setFillColor(sf::Color(218, 165, 32));
    subtitle.setStyle(sf::Text::Italic);
    subtitle.setPosition(centerX - subtitle.getGlobalBounds().width / 2, 165);
    window.draw(subtitle);

    std::vector<std::string> options = {
        "PLAYER VS PLAYER",
        "PLAYER VS AI (EASY)",
        "PLAYER VS AI (MEDIUM)",
        "PLAYER VS AI (HARD)",
        "INSTRUCTIONS"
    };

    for (int i = 0; i < options.size(); i++) {
        float btnY = 210 + i * 62;

        sf::RectangleShape btn(sf::Vector2f(320, 52));
        btn.setPosition(centerX - 160, btnY);
        btn.setFillColor(sf::Color(40, 30, 20, 220));
        btn.setOutlineColor(sf::Color(218, 165, 32));
        btn.setOutlineThickness(2);
        window.draw(btn);

        sf::Text text(options[i], font, 24);
        text.setFillColor(sf::Color(240, 240, 240));
        text.setStyle(sf::Text::Bold);
        text.setPosition(centerX - text.getGlobalBounds().width / 2, btnY + 13);
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