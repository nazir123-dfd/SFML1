#include "ChessGame.h"

void ChessGame::drawMoveHistory(sf::RenderWindow& window, sf::Font& font) {
    int fontSize = std::max(13, (int)(cellSize * 0.21f));
    float rightX = boardOffsetX + 8 * cellSize + 30;
    float startY = boardOffsetY + 20;

    sf::RectangleShape historyBg(sf::Vector2f(240, 650));
    historyBg.setPosition(rightX, startY);
    historyBg.setFillColor(sf::Color(35, 28, 22, 240));
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

    int maxMoves = 32;
    int startIdx = std::max(0, (int)moveHistory.size() - maxMoves);

    for (int i = startIdx; i < moveHistory.size(); i++) {
        std::string notation = getMoveNotation(moveHistory[i]);

        sf::RectangleShape moveBg(sf::Vector2f(200, fontSize + 8));
        moveBg.setPosition(rightX + 20, startY + 70 + (i - startIdx) * (fontSize + 10));

        if (i == moveHistory.size() - 1) {
            moveBg.setFillColor(sf::Color(80, 60, 40, 100));
        }
        else if ((i - startIdx) % 2 == 0) {
            moveBg.setFillColor(sf::Color(50, 40, 30, 50));
        }
        else {
            moveBg.setFillColor(sf::Color(45, 35, 25, 30));
        }
        window.draw(moveBg);

        int moveNum = (i / 2) + 1;
        bool isWhiteMove = (i % 2 == 0);

        std::stringstream ss;
        if (isWhiteMove) {
            ss << moveNum << ". " << notation;
        }
        else {
            ss << "    " << notation;
        }

        sf::Text moveText(ss.str(), font, fontSize);
        moveText.setFillColor(sf::Color(230, 230, 230));
        moveText.setPosition(rightX + 28, startY + 72 + (i - startIdx) * (fontSize + 10));
        window.draw(moveText);
    }
}

void ChessGame::drawControls(sf::RenderWindow& window, sf::Font& font) {
    int fontSize = std::max(14, (int)(cellSize * 0.22f));
    float leftX = 30;
    float startY = boardOffsetY + 200;

    sf::RectangleShape controlsBg(sf::Vector2f(140, 200));
    controlsBg.setPosition(leftX, startY);
    controlsBg.setFillColor(sf::Color(35, 28, 22, 240));
    controlsBg.setOutlineColor(sf::Color(180, 150, 90));
    controlsBg.setOutlineThickness(3);
    window.draw(controlsBg);

    sf::Text controlsTitle("Controls", font, fontSize + 3);
    controlsTitle.setFillColor(sf::Color(255, 220, 120));
    controlsTitle.setStyle(sf::Text::Bold);
    controlsTitle.setPosition(leftX + 15, startY + 15);
    window.draw(controlsTitle);

    sf::RectangleShape divider(sf::Vector2f(110, 2));
    divider.setPosition(leftX + 15, startY + 45);
    divider.setFillColor(sf::Color(218, 165, 32, 150));
    window.draw(divider);

    std::vector<std::string> controls = {
        "U - Undo",
        "H - Hints"
    };

    for (int i = 0; i < controls.size(); i++) {
        sf::Text text(controls[i], font, fontSize - 1);
        text.setFillColor(sf::Color(230, 230, 230));
        text.setPosition(leftX + 18, startY + 60 + i * (fontSize + 12));
        window.draw(text);
    }

    if (isInCheck(currentPlayer)) {
        sf::RectangleShape checkBox(sf::Vector2f(110, 35));
        checkBox.setPosition(leftX + 15, startY + 140);
        checkBox.setFillColor(sf::Color(180, 30, 30, 200));
        checkBox.setOutlineColor(sf::Color::Red);
        checkBox.setOutlineThickness(2);
        window.draw(checkBox);

        sf::Text checkText("CHECK!", font, fontSize + 2);
        checkText.setFillColor(sf::Color::White);
        checkText.setStyle(sf::Text::Bold);
        checkText.setPosition(leftX + 25, startY + 147);
        window.draw(checkText);
    }
    else if (hintsEnabled) {
        sf::RectangleShape hintBox(sf::Vector2f(110, 35));
        hintBox.setPosition(leftX + 15, startY + 140);
        hintBox.setFillColor(sf::Color(30, 120, 30, 150));
        hintBox.setOutlineColor(sf::Color(50, 200, 50));
        hintBox.setOutlineThickness(2);
        window.draw(hintBox);

        sf::Text hintStatus("Hints: ON", font, fontSize);
        hintStatus.setFillColor(sf::Color(180, 255, 180));
        hintStatus.setStyle(sf::Text::Bold);
        hintStatus.setPosition(leftX + 22, startY + 147);
        window.draw(hintStatus);
    }
}

void ChessGame::drawGameUI(sf::RenderWindow& window, sf::Font& font) {
    drawCompactTimer(window, font);
    drawMoveHistory(window, font);
    drawControls(window, font);

    int fontSize = std::max(16, (int)(cellSize * 0.28f));
    float leftX = 30;
    float forfeitY = boardOffsetY + 430;

    sf::RectangleShape forfeitBtn(sf::Vector2f(140, 50));
    forfeitBtn.setPosition(leftX, forfeitY);
    forfeitBtn.setFillColor(sf::Color(140, 50, 50));
    forfeitBtn.setOutlineColor(sf::Color(200, 100, 100));
    forfeitBtn.setOutlineThickness(3);
    window.draw(forfeitBtn);

    sf::Text forfeitText("FORFEIT", font, fontSize + 1);
    forfeitText.setFillColor(sf::Color::White);
    forfeitText.setStyle(sf::Text::Bold);
    float textX = leftX + 70 - forfeitText.getGlobalBounds().width / 2;
    forfeitText.setPosition(textX, forfeitY + 13);
    window.draw(forfeitText);
}