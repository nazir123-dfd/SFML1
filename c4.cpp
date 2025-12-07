#include "ChessGame.h"

void ChessGame::drawMoveHistory(sf::RenderWindow& window, sf::Font& font) {
    int fontSize = std::max(14, (int)(cellSize * 0.22f));
    float rightX = boardOffsetX + 8 * cellSize + 60;
    float startY = boardOffsetY + 20;

    sf::RectangleShape historyBg(sf::Vector2f(240, 550));
    historyBg.setPosition(rightX, startY);
    historyBg.setFillColor(sf::Color(40, 30, 25, 250));
    historyBg.setOutlineColor(sf::Color(180, 150, 90));
    historyBg.setOutlineThickness(3);
    window.draw(historyBg);

    sf::Text historyTitle("Move History", font, fontSize + 6);
    historyTitle.setFillColor(sf::Color(255, 220, 120));
    historyTitle.setStyle(sf::Text::Bold);
    historyTitle.setPosition(rightX + 20, startY + 18);
    window.draw(historyTitle);

    sf::RectangleShape divider(sf::Vector2f(200, 2));
    divider.setPosition(rightX + 20, startY + 52);
    divider.setFillColor(sf::Color(218, 165, 32, 150));
    window.draw(divider);

    int startIdx = std::max(0, (int)moveHistory.size() - 36);
    for (int i = startIdx; i < moveHistory.size(); i++) {
        std::string notation = getMoveNotation(moveHistory[i]);
        sf::Text moveText(notation, font, fontSize - 1);
        moveText.setFillColor(sf::Color(230, 230, 230));
        moveText.setPosition(rightX + 25, startY + 70 + (i - startIdx) * (fontSize + 5));
        window.draw(moveText);
    }
}

void ChessGame::drawControls(sf::RenderWindow& window, sf::Font& font) {
    int fontSize = std::max(15, (int)(cellSize * 0.24f));
    float leftX = boardOffsetX - 240;
    float startY = boardOffsetY + 390;

    sf::RectangleShape controlsBg(sf::Vector2f(200, 160));
    controlsBg.setPosition(leftX, startY);
    controlsBg.setFillColor(sf::Color(40, 30, 25, 250));
    controlsBg.setOutlineColor(sf::Color(180, 150, 90));
    controlsBg.setOutlineThickness(3);
    window.draw(controlsBg);

    sf::Text controlsTitle("Controls", font, fontSize + 3);
    controlsTitle.setFillColor(sf::Color(255, 220, 120));
    controlsTitle.setStyle(sf::Text::Bold);
    controlsTitle.setPosition(leftX + 20, startY + 18);
    window.draw(controlsTitle);

    sf::RectangleShape divider(sf::Vector2f(160, 2));
    divider.setPosition(leftX + 20, startY + 48);
    divider.setFillColor(sf::Color(218, 165, 32, 150));
    window.draw(divider);

    std::vector<std::string> controls = {
        "U - Undo Move",
        "H - Toggle Hints"
    };

    for (int i = 0; i < controls.size(); i++) {
        sf::Text text(controls[i], font, fontSize);
        text.setFillColor(sf::Color(230, 230, 230));
        text.setPosition(leftX + 25, startY + 65 + i * (fontSize + 14));
        window.draw(text);
    }

    if (isInCheck(currentPlayer)) {
        sf::Text checkText("CHECK!", font, fontSize + 4);
        checkText.setFillColor(sf::Color::Red);
        checkText.setStyle(sf::Text::Bold);
        checkText.setPosition(leftX + 25, startY + 115);
        window.draw(checkText);
    }
    else if (hintsEnabled) {
        sf::Text hintStatus("Hints: ON", font, fontSize + 1);
        hintStatus.setFillColor(sf::Color(100, 255, 100));
        hintStatus.setStyle(sf::Text::Bold);
        hintStatus.setPosition(leftX + 25, startY + 115);
        window.draw(hintStatus);
    }
}

void ChessGame::drawGameUI(sf::RenderWindow& window, sf::Font& font) {
    drawTimer(window, font);
    drawMoveHistory(window, font);
    drawControls(window, font);

    int fontSize = std::max(16, (int)(cellSize * 0.28f));
    float centerX = boardOffsetX + (8 * cellSize) / 2;
    float forfeitY = boardOffsetY + 8 * cellSize + 50;

    sf::RectangleShape forfeitBtn(sf::Vector2f(180, 55));
    forfeitBtn.setPosition(centerX - 90, forfeitY);
    forfeitBtn.setFillColor(sf::Color(140, 50, 50));
    forfeitBtn.setOutlineColor(sf::Color(200, 100, 100));
    forfeitBtn.setOutlineThickness(3);
    window.draw(forfeitBtn);

    sf::Text forfeitText("FORFEIT", font, fontSize + 3);
    forfeitText.setFillColor(sf::Color::White);
    forfeitText.setStyle(sf::Text::Bold);
    forfeitText.setPosition(centerX - forfeitText.getGlobalBounds().width / 2, forfeitY + 15);
    window.draw(forfeitText);
}