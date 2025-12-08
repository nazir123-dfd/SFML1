#include "ChessGame.h"

void ChessGame::drawMoveHistory(sf::RenderWindow& window, sf::Font& font) {
    int fontSize = std::max(13, (int)(cellSize * 0.21f));
    float rightX = boardOffsetX + 8 * cellSize + 30;
    float startY = boardOffsetY + 20;
    float boxHeight = windowHeight - startY - 30;

    sf::RectangleShape historyBg(sf::Vector2f(340, boxHeight));
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

    sf::RectangleShape divider(sf::Vector2f(300, 2));
    divider.setPosition(rightX + 20, startY + 52);
    divider.setFillColor(sf::Color(218, 165, 32, 150));
    window.draw(divider);

    sf::Text whiteHeader("White", font, fontSize);
    whiteHeader.setFillColor(sf::Color(200, 200, 200));
    whiteHeader.setStyle(sf::Text::Bold);
    whiteHeader.setPosition(rightX + 50, startY + 60);
    window.draw(whiteHeader);

    sf::Text blackHeader("Black", font, fontSize);
    blackHeader.setFillColor(sf::Color(200, 200, 200));
    blackHeader.setStyle(sf::Text::Bold);
    blackHeader.setPosition(rightX + 200, startY + 60);
    window.draw(blackHeader);

    float contentStartY = startY + 85;
    float contentHeight = boxHeight - 85;
    int maxVisibleRows = (int)(contentHeight / (fontSize + 10));

    int totalMoves = moveHistory.size();
    int totalMovePairs = (totalMoves + 1) / 2;

    int maxScroll = std::max(0, totalMovePairs - maxVisibleRows);
    scrollOffset = std::min(scrollOffset, maxScroll);
    scrollOffset = std::max(0, scrollOffset);

    for (int pairIdx = scrollOffset; pairIdx < totalMovePairs && pairIdx < scrollOffset + maxVisibleRows; pairIdx++) {
        int whiteIdx = pairIdx * 2;
        int blackIdx = pairIdx * 2 + 1;
        int displayRow = pairIdx - scrollOffset;

        float rowY = contentStartY + displayRow * (fontSize + 10);

        if (rowY + fontSize + 8 > startY + boxHeight) break;

        sf::RectangleShape rowBg(sf::Vector2f(300, fontSize + 8));
        rowBg.setPosition(rightX + 20, rowY);

        if (pairIdx == totalMovePairs - 1) {
            rowBg.setFillColor(sf::Color(80, 60, 40, 100));
        }
        else if (displayRow % 2 == 0) {
            rowBg.setFillColor(sf::Color(50, 40, 30, 50));
        }
        else {
            rowBg.setFillColor(sf::Color(45, 35, 25, 30));
        }
        window.draw(rowBg);

        int moveNum = pairIdx + 1;
        std::stringstream numSS;
        numSS << moveNum << ".";
        sf::Text moveNumText(numSS.str(), font, fontSize);
        moveNumText.setFillColor(sf::Color(180, 180, 180));
        moveNumText.setPosition(rightX + 25, rowY + 2);
        window.draw(moveNumText);

        if (whiteIdx < totalMoves) {
            std::string whiteNotation = getMoveNotation(moveHistory[whiteIdx]);
            sf::Text whiteText(whiteNotation, font, fontSize);
            whiteText.setFillColor(sf::Color(230, 230, 230));
            whiteText.setPosition(rightX + 55, rowY + 2);
            window.draw(whiteText);
        }

        if (blackIdx < totalMoves) {
            std::string blackNotation = getMoveNotation(moveHistory[blackIdx]);
            sf::Text blackText(blackNotation, font, fontSize);
            blackText.setFillColor(sf::Color(230, 230, 230));
            blackText.setPosition(rightX + 205, rowY + 2);
            window.draw(blackText);
        }
    }

    if (totalMovePairs > maxVisibleRows) {
        float scrollBarHeight = 40;
        float scrollBarMaxY = boxHeight - 90 - scrollBarHeight;
        float scrollBarY = contentStartY + (scrollOffset * scrollBarMaxY / maxScroll);

        sf::RectangleShape scrollBar(sf::Vector2f(8, scrollBarHeight));
        scrollBar.setPosition(rightX + 325, scrollBarY);
        scrollBar.setFillColor(sf::Color(218, 165, 32, 200));
        window.draw(scrollBar);
    }
}

void ChessGame::handleMouseScroll(float delta, sf::Vector2i mousePos) {
    float rightX = boardOffsetX + 8 * cellSize + 30;
    float startY = boardOffsetY + 20;
    float boxHeight = windowHeight - startY - 30;

    if (gameState == PLAYING &&
        mousePos.x >= rightX && mousePos.x <= rightX + 340 &&
        mousePos.y >= startY && mousePos.y <= startY + boxHeight) {

        scrollOffset -= (int)delta;

        int fontSize = std::max(13, (int)(cellSize * 0.21f));
        float contentHeight = boxHeight - 85;
        int maxVisibleRows = (int)(contentHeight / (fontSize + 10));
        int totalMovePairs = (moveHistory.size() + 1) / 2;
        int maxScroll = std::max(0, totalMovePairs - maxVisibleRows);

        scrollOffset = std::min(scrollOffset, maxScroll);
        scrollOffset = std::max(0, scrollOffset);
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

    std::vector<std::string> controls = { "U - Undo", "H - Hints" };
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