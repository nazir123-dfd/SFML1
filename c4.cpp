#include "ChessGame.h"
#include <algorithm>

void ChessGame::drawMoveHistory(sf::RenderWindow& window, sf::Font& font) {
    int fontSize = std::max(13, static_cast<int>(cellSize * 0.21f));
    float rightX = boardOffsetX + 8 * cellSize + 30;
    float startY = boardOffsetY + 20;

    sf::RectangleShape historyBg(sf::Vector2f(380.0f, 730.0f));
    historyBg.setPosition(rightX, startY);
    historyBg.setFillColor(sf::Color(35, 28, 22, 240));
    historyBg.setOutlineColor(sf::Color(180, 150, 90));
    historyBg.setOutlineThickness(3);
    window.draw(historyBg);

    sf::Text historyTitle("Move History", font, static_cast<unsigned int>(fontSize + 6));
    historyTitle.setFillColor(sf::Color(255, 220, 120));
    historyTitle.setStyle(sf::Text::Bold);
    historyTitle.setPosition(rightX + 20, startY + 18);
    window.draw(historyTitle);

    sf::RectangleShape divider(sf::Vector2f(340.0f, 2.0f));
    divider.setPosition(rightX + 20, startY + 52);
    divider.setFillColor(sf::Color(218, 165, 32, 150));
    window.draw(divider);

    sf::Text whiteHeader("White", font, static_cast<unsigned int>(fontSize));
    whiteHeader.setFillColor(sf::Color(230, 230, 230));
    whiteHeader.setStyle(sf::Text::Bold);
    whiteHeader.setPosition(rightX + 50, startY + 62);
    window.draw(whiteHeader);

    sf::Text blackHeader("Black", font, static_cast<unsigned int>(fontSize));
    blackHeader.setFillColor(sf::Color(230, 230, 230));
    blackHeader.setStyle(sf::Text::Bold);
    blackHeader.setPosition(rightX + 200, startY + 62);
    window.draw(blackHeader);

    int maxVisibleMoves = 27;
    int totalMoveRows = static_cast<int>((moveHistory.size() + 1) / 2);

    int startRow = scrollOffset;
    int endRow = std::min(totalMoveRows, startRow + maxVisibleMoves);

    for (int row = startRow; row < endRow; row++) {
        int moveNum = row + 1;
        int whiteIdx = row * 2;
        int blackIdx = row * 2 + 1;

        int displayRow = row - startRow;
        float yPos = startY + 90 + displayRow * (fontSize + 10.0f);

        if (yPos + fontSize + 8 > startY + 730.0f - 10) {
            break;
        }

        sf::RectangleShape rowBg(sf::Vector2f(340.0f, static_cast<float>(fontSize + 8)));
        rowBg.setPosition(rightX + 20, yPos);
        if (displayRow % 2 == 0) {
            rowBg.setFillColor(sf::Color(50, 40, 30, 50));
        }
        else {
            rowBg.setFillColor(sf::Color(45, 35, 25, 30));
        }
        window.draw(rowBg);

        std::stringstream ss;
        ss << moveNum << ".";
        sf::Text numText(ss.str(), font, static_cast<unsigned int>(fontSize));
        numText.setFillColor(sf::Color(200, 200, 200));
        numText.setPosition(rightX + 25, yPos + 2);
        window.draw(numText);

        if (whiteIdx < static_cast<int>(moveHistory.size())) {
            std::string whiteNotation = getMoveNotation(moveHistory[whiteIdx]);
            sf::Text whiteText(whiteNotation, font, static_cast<unsigned int>(fontSize));
            whiteText.setFillColor(sf::Color(230, 230, 230));
            if (whiteIdx == static_cast<int>(moveHistory.size()) - 1) {
                whiteText.setStyle(sf::Text::Bold);
                whiteText.setFillColor(sf::Color(255, 240, 120));
            }
            whiteText.setPosition(rightX + 50, yPos + 2);
            window.draw(whiteText);
        }

        if (blackIdx < static_cast<int>(moveHistory.size())) {
            std::string blackNotation = getMoveNotation(moveHistory[blackIdx]);
            sf::Text blackText(blackNotation, font, static_cast<unsigned int>(fontSize));
            blackText.setFillColor(sf::Color(230, 230, 230));
            if (blackIdx == static_cast<int>(moveHistory.size()) - 1) {
                blackText.setStyle(sf::Text::Bold);
                blackText.setFillColor(sf::Color(255, 240, 120));
            }
            blackText.setPosition(rightX + 200, yPos + 2);
            window.draw(blackText);
        }
    }

    if (totalMoveRows > maxVisibleMoves) {
        float scrollBarHeight = 620.0f;
        float scrollBarY = startY + 90;
        float scrollBarX = rightX + 355;

        sf::RectangleShape scrollTrack(sf::Vector2f(8.0f, scrollBarHeight));
        scrollTrack.setPosition(scrollBarX, scrollBarY);
        scrollTrack.setFillColor(sf::Color(60, 50, 40));
        window.draw(scrollTrack);

        float thumbHeight = (scrollBarHeight * maxVisibleMoves) / static_cast<float>(totalMoveRows);
        if (thumbHeight < 30.0f) thumbHeight = 30.0f;

        int maxScroll = totalMoveRows - maxVisibleMoves;
        float scrollProgress = static_cast<float>(scrollOffset) / static_cast<float>(maxScroll);
        float thumbY = scrollBarY + (scrollBarHeight - thumbHeight) * scrollProgress;

        sf::RectangleShape scrollThumb(sf::Vector2f(8.0f, thumbHeight));
        scrollThumb.setPosition(scrollBarX, thumbY);
        scrollThumb.setFillColor(sf::Color(180, 150, 90));
        window.draw(scrollThumb);
    }
}

void ChessGame::handleMouseWheel(float delta) {
    int totalMoveRows = static_cast<int>((moveHistory.size() + 1) / 2);
    int maxVisibleMoves = 27;

    if (totalMoveRows > maxVisibleMoves) {
        scrollOffset += (delta > 0) ? -1 : 1;

        int maxScroll = totalMoveRows - maxVisibleMoves;
        if (scrollOffset < 0) scrollOffset = 0;
        if (scrollOffset > maxScroll) scrollOffset = maxScroll;
    }
}

void ChessGame::drawControls(sf::RenderWindow& window, sf::Font& font) {
    int fontSize = std::max(14, static_cast<int>(cellSize * 0.22f));
    float leftX = 30;
    float startY = boardOffsetY + 200;

    sf::RectangleShape controlsBg(sf::Vector2f(140.0f, 200.0f));
    controlsBg.setPosition(leftX, startY);
    controlsBg.setFillColor(sf::Color(35, 28, 22, 240));
    controlsBg.setOutlineColor(sf::Color(180, 150, 90));
    controlsBg.setOutlineThickness(3);
    window.draw(controlsBg);

    sf::Text controlsTitle("Controls", font, static_cast<unsigned int>(fontSize + 3));
    controlsTitle.setFillColor(sf::Color(255, 220, 120));
    controlsTitle.setStyle(sf::Text::Bold);
    controlsTitle.setPosition(leftX + 15, startY + 15);
    window.draw(controlsTitle);

    sf::RectangleShape divider(sf::Vector2f(110.0f, 2.0f));
    divider.setPosition(leftX + 15, startY + 45);
    divider.setFillColor(sf::Color(218, 165, 32, 150));
    window.draw(divider);

    std::vector<std::string> controls = {
        "U - Undo",
        "H - Hints"
    };

    for (size_t i = 0; i < controls.size(); i++) {
        sf::Text text(controls[i], font, static_cast<unsigned int>(fontSize - 1));
        text.setFillColor(sf::Color(230, 230, 230));
        text.setPosition(leftX + 18, startY + 60 + static_cast<float>(i * (fontSize + 12)));
        window.draw(text);
    }

    if (isInCheck(currentPlayer)) {
        sf::RectangleShape checkBox(sf::Vector2f(110.0f, 35.0f));
        checkBox.setPosition(leftX + 15, startY + 140);
        checkBox.setFillColor(sf::Color(180, 30, 30, 200));
        checkBox.setOutlineColor(sf::Color::Red);
        checkBox.setOutlineThickness(2);
        window.draw(checkBox);

        sf::Text checkText("CHECK!", font, static_cast<unsigned int>(fontSize + 2));
        checkText.setFillColor(sf::Color::White);
        checkText.setStyle(sf::Text::Bold);
        checkText.setPosition(leftX + 25, startY + 147);
        window.draw(checkText);
    }
    else if (hintsEnabled) {
        sf::RectangleShape hintBox(sf::Vector2f(110.0f, 35.0f));
        hintBox.setPosition(leftX + 15, startY + 140);
        hintBox.setFillColor(sf::Color(30, 120, 30, 150));
        hintBox.setOutlineColor(sf::Color(50, 200, 50));
        hintBox.setOutlineThickness(2);
        window.draw(hintBox);

        sf::Text hintStatus("Hints: ON", font, static_cast<unsigned int>(fontSize));
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

    int fontSize = std::max(16, static_cast<int>(cellSize * 0.28f));
    float leftX = 30;
    float forfeitY = boardOffsetY + 430;

    sf::RectangleShape forfeitBtn(sf::Vector2f(140.0f, 50.0f));
    forfeitBtn.setPosition(leftX, forfeitY);
    forfeitBtn.setFillColor(sf::Color(140, 50, 50));
    forfeitBtn.setOutlineColor(sf::Color(200, 100, 100));
    forfeitBtn.setOutlineThickness(3);
    window.draw(forfeitBtn);
    //DONE!!!!!!
    sf::Text forfeitText("FORFEIT", font, static_cast<unsigned int>(fontSize + 1));
    forfeitText.setFillColor(sf::Color::White);
    forfeitText.setStyle(sf::Text::Bold);
    float textX = leftX + 70 - forfeitText.getGlobalBounds().width / 2;
    forfeitText.setPosition(textX, forfeitY + 13);
    window.draw(forfeitText);
}