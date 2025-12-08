#include "ChessGame.h"

void ChessGame::drawBoard(sf::RenderWindow& window) {
    sf::Color lightWood(240, 217, 181);
    sf::Color darkWood(181, 136, 99);

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));
            cell.setPosition(boardOffsetX + j * cellSize, boardOffsetY + i * cellSize);

            if ((i + j) % 2 == 0) {
                cell.setFillColor(lightWood);
            }
            else {
                cell.setFillColor(darkWood);
            }
            window.draw(cell);
        }
    }
}

void ChessGame::drawBoardLabels(sf::RenderWindow& window, sf::Font& font) {
    int fontSize = std::max(14, (int)(cellSize * 0.25f));

    for (int i = 0; i < 8; i++) {
        char label = 'a' + i;
        float xPos = boardOffsetX + i * cellSize + cellSize / 2 - fontSize / 3;

        sf::Text topText(std::string(1, label), font, fontSize);
        topText.setFillColor(sf::Color(200, 200, 200));
        topText.setStyle(sf::Text::Bold);
        topText.setPosition(xPos, boardOffsetY - fontSize - 20);
        window.draw(topText);

        sf::Text bottomText(std::string(1, label), font, fontSize);
        bottomText.setFillColor(sf::Color(200, 200, 200));
        bottomText.setStyle(sf::Text::Bold);
        bottomText.setPosition(xPos, boardOffsetY + 8 * cellSize + 10);
        window.draw(bottomText);
    }

    for (int i = 0; i < 8; i++) {
        char label = '8' - i;
        float yPos = boardOffsetY + i * cellSize + cellSize / 2 - fontSize / 2;

        sf::Text leftText(std::string(1, label), font, fontSize);
        leftText.setFillColor(sf::Color(200, 200, 200));
        leftText.setStyle(sf::Text::Bold);
        leftText.setPosition(boardOffsetX - fontSize - 20, yPos);
        window.draw(leftText);

        sf::Text rightText(std::string(1, label), font, fontSize);
        rightText.setFillColor(sf::Color(200, 200, 200));
        rightText.setStyle(sf::Text::Bold);
        rightText.setPosition(boardOffsetX + 8 * cellSize + 10, yPos);
        window.draw(rightText);
    }
}

void ChessGame::drawHighlights(sf::RenderWindow& window) {
    if (!isPieceSelected || !hintsEnabled) return;

    sf::RectangleShape selectedHighlight(sf::Vector2f(cellSize, cellSize));
    selectedHighlight.setPosition(boardOffsetX + selectedCol * cellSize, boardOffsetY + selectedRow * cellSize);
    selectedHighlight.setFillColor(sf::Color(255, 255, 100, 100));
    window.draw(selectedHighlight);

    for (auto& move : validMoves) {
        sf::RectangleShape highlight(sf::Vector2f(cellSize, cellSize));
        highlight.setPosition(boardOffsetX + move.second * cellSize, boardOffsetY + move.first * cellSize);

        if (board[move.first][move.second].type != EMPTY) {
            highlight.setFillColor(sf::Color(255, 70, 70, 150));
        }
        else {
            highlight.setFillColor(sf::Color(100, 255, 100, 130));
        }
        window.draw(highlight);
    }
}

void ChessGame::drawPieces(sf::RenderWindow& window, sf::Vector2i mousePos) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (isDragging && i == selectedRow && j == selectedCol) continue;
            if (board[i][j].type != EMPTY) {
                sf::Texture* tex = getPieceTexture(board[i][j]);
                if (tex) {
                    sf::Sprite sprite(*tex);
                    sprite.setPosition(boardOffsetX + j * cellSize, boardOffsetY + i * cellSize);
                    float scaleX = cellSize / tex->getSize().x;
                    float scaleY = cellSize / tex->getSize().y;
                    sprite.setScale(scaleX, scaleY);
                    window.draw(sprite);
                }
            }
        }
    }

    if (isDragging && selectedRow != -1) {
        sf::Texture* tex = getPieceTexture(board[selectedRow][selectedCol]);
        if (tex) {
            sf::Sprite sprite(*tex);
            sprite.setPosition(mousePos.x - dragOffset.x, mousePos.y - dragOffset.y);
            float scaleX = cellSize / tex->getSize().x;
            float scaleY = cellSize / tex->getSize().y;
            sprite.setScale(scaleX, scaleY);
            window.draw(sprite);
        }
    }
}

void ChessGame::drawCompactTimer(sf::RenderWindow& window, sf::Font& font) {
    int fontSize = std::max(16, (int)(cellSize * 0.28f));

    int whiteMin = (int)whiteTime / 60;
    int whiteSec = (int)whiteTime % 60;
    int blackMin = (int)blackTime / 60;
    int blackSec = (int)blackTime % 60;

    std::stringstream wss, bss;
    wss << whiteMin << ":" << (whiteSec < 10 ? "0" : "") << whiteSec;
    bss << blackMin << ":" << (blackSec < 10 ? "0" : "") << blackSec;

    float topY = boardOffsetY + 20;
    float leftX = 30;

    sf::RectangleShape whiteBox(sf::Vector2f(140, 70));
    whiteBox.setPosition(leftX, topY);
    whiteBox.setFillColor(sf::Color(245, 245, 245));
    whiteBox.setOutlineColor(currentPlayer == WHITE ? sf::Color(50, 200, 50) : sf::Color(120, 120, 120));
    whiteBox.setOutlineThickness(currentPlayer == WHITE ? 4 : 2);
    window.draw(whiteBox);

    sf::Text whiteLabel("WHITE", font, fontSize - 4);
    whiteLabel.setFillColor(sf::Color(40, 40, 40));
    whiteLabel.setStyle(sf::Text::Bold);
    whiteLabel.setPosition(leftX + 10, topY + 10);
    window.draw(whiteLabel);

    sf::Text whiteTimeText(wss.str(), font, fontSize + 4);
    whiteTimeText.setFillColor(currentPlayer == WHITE ? sf::Color(0, 150, 0) : sf::Color(80, 80, 80));
    whiteTimeText.setStyle(sf::Text::Bold);
    whiteTimeText.setPosition(leftX + 10, topY + 40);
    window.draw(whiteTimeText);

    sf::RectangleShape blackBox(sf::Vector2f(140, 70));
    blackBox.setPosition(leftX, topY + 90);
    blackBox.setFillColor(sf::Color(40, 40, 40));
    blackBox.setOutlineColor(currentPlayer == BLACK ? sf::Color(50, 200, 50) : sf::Color(100, 100, 100));
    blackBox.setOutlineThickness(currentPlayer == BLACK ? 4 : 2);
    window.draw(blackBox);

    sf::Text blackLabel("BLACK", font, fontSize - 4);
    blackLabel.setFillColor(sf::Color(220, 220, 220));
    blackLabel.setStyle(sf::Text::Bold);
    blackLabel.setPosition(leftX + 10, topY + 100);
    window.draw(blackLabel);

    sf::Text blackTimeText(bss.str(), font, fontSize + 4);
    blackTimeText.setFillColor(currentPlayer == BLACK ? sf::Color(100, 255, 100) : sf::Color(180, 180, 180));
    blackTimeText.setStyle(sf::Text::Bold);
    blackTimeText.setPosition(leftX + 10, topY + 130);
    window.draw(blackTimeText);
}