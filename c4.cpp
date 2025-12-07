#include "ChessGame.h"

void ChessGame::drawMoveHistory(sf::RenderWindow& window, sf::Font& font) {
    int fontSize = std::max(13, (int)(cellSize * 0.20f));
    float rightX = boardOffsetX + 8 * cellSize + 50;
    float startY = boardOffsetY + 30;

    sf::RectangleShape historyBg(sf::Vector2f(220, 500));
    historyBg.setPosition(rightX, startY);
    historyBg.setFillColor(sf::Color(45, 35, 25, 240));
    historyBg.setOutlineColor(sf::Color(180, 150, 90));
    historyBg.setOutlineThickness(3);
    window.draw(historyBg);

    sf::Text historyTitle("Move History", font, fontSize + 5);
    historyTitle.setFillColor(sf::Color(255, 220, 120));
    historyTitle.setStyle(sf::Text::Bold);
    historyTitle.setPosition(rightX + 15, startY + 15);
    window.draw(historyTitle);

    sf::RectangleShape divider(sf::Vector2f(190, 2));
    divider.setPosition(rightX + 15, startY + 48);
    divider.setFillColor(sf::Color(218, 165, 32, 150));
    window.draw(divider);

    int startIdx = std::max(0, (int)moveHistory.size() - 32);
    for (int i = startIdx; i < moveHistory.size(); i++) {
        std::string notation = getMoveNotation(moveHistory[i]);
        sf::Text moveText(notation, font, fontSize);
        moveText.setFillColor(sf::Color(230, 230, 230));
        moveText.setPosition(rightX + 20, startY + 65 + (i - startIdx) * (fontSize + 6));
        window.draw(moveText);
    }
}

void ChessGame::drawControls(sf::RenderWindow& window, sf::Font& font) {
    int fontSize = std::max(14, (int)(cellSize * 0.22f));
    float leftX = boardOffsetX - 220;
    float startY = boardOffsetY + 290;

    sf::RectangleShape controlsBg(sf::Vector2f(180, 180));
    controlsBg.setPosition(leftX, startY);
    controlsBg.setFillColor(sf::Color(45, 35, 25, 240));
    controlsBg.setOutlineColor(sf::Color(180, 150, 90));
    controlsBg.setOutlineThickness(3);
    window.draw(controlsBg);

    sf::Text controlsTitle("Controls", font, fontSize + 3);
    controlsTitle.setFillColor(sf::Color(255, 220, 120));
    controlsTitle.setStyle(sf::Text::Bold);
    controlsTitle.setPosition(leftX + 15, startY + 15);
    window.draw(controlsTitle);

    sf::RectangleShape divider(sf::Vector2f(150, 2));
    divider.setPosition(leftX + 15, startY + 45);
    divider.setFillColor(sf::Color(218, 165, 32, 150));
    window.draw(divider);

    std::vector<std::string> controls = {
        "U - Undo Move",
        "H - Toggle Hints"
    };

    for (int i = 0; i < controls.size(); i++) {
        sf::Text text(controls[i], font, fontSize);
        text.setFillColor(sf::Color(230, 230, 230));
        text.setPosition(leftX + 20, startY + 60 + i * (fontSize + 14));
        window.draw(text);
    }

    if (hintsEnabled) {
        sf::Text hintStatus("Hints: ON", font, fontSize + 1);
        hintStatus.setFillColor(sf::Color(100, 255, 100));
        hintStatus.setStyle(sf::Text::Bold);
        hintStatus.setPosition(leftX + 20, startY + 120);
        window.draw(hintStatus);
    }
    else {
        sf::Text hintStatus("Hints: OFF", font, fontSize + 1);
        hintStatus.setFillColor(sf::Color(200, 100, 100));
        hintStatus.setStyle(sf::Text::Bold);
        hintStatus.setPosition(leftX + 20, startY + 120);
        window.draw(hintStatus);
    }

    if (isInCheck(currentPlayer)) {
        sf::Text checkText("CHECK!", font, fontSize + 5);
        checkText.setFillColor(sf::Color::Red);
        checkText.setStyle(sf::Text::Bold);
        checkText.setPosition(leftX + 20, startY + 145);
        window.draw(checkText);
    }
}

void ChessGame::drawGameUI(sf::RenderWindow& window, sf::Font& font) {
    drawTimer(window, font);
    drawMoveHistory(window, font);
    drawControls(window, font);

    int fontSize = std::max(15, (int)(cellSize * 0.26f));
    float rightX = boardOffsetX + 8 * cellSize + 300;
    float forfeitY = boardOffsetY + 250;

    sf::RectangleShape forfeitBtn(sf::Vector2f(160, 55));
    forfeitBtn.setPosition(rightX - 310, forfeitY);
    forfeitBtn.setFillColor(sf::Color(140, 50, 50));
    forfeitBtn.setOutlineColor(sf::Color(200, 100, 100));
    forfeitBtn.setOutlineThickness(3);
    window.draw(forfeitBtn);

    sf::Text forfeitText("FORFEIT", font, fontSize + 2);
    forfeitText.setFillColor(sf::Color::White);
    forfeitText.setStyle(sf::Text::Bold);
    forfeitText.setPosition(rightX - 270, forfeitY + 16);
    window.draw(forfeitText);
}