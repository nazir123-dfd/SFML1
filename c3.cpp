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
    int fontSize = std::max(16, (int)(cellSize * 0.30f));

    for (int i = 0; i < 8; i++) {
        char label = 'a' + i;
        float xPos = boardOffsetX + i * cellSize + cellSize / 2 - fontSize / 3;

        sf::Text topText(std::string(1, label), font, fontSize);
        topText.setFillColor(sf::Color(220, 220, 220));
        topText.setStyle(sf::Text::Bold);
        topText.setPosition(xPos, boardOffsetY - fontSize - 28);
        window.draw(topText);

        sf::Text bottomText(std::string(1, label), font, fontSize);
        bottomText.setFillColor(sf::Color(220, 220, 220));
        bottomText.setStyle(sf::Text::Bold);
        bottomText.setPosition(xPos, boardOffsetY + 8 * cellSize + 15);
        window.draw(bottomText);
    }

    for (int i = 0; i < 8; i++) {
        char label = '8' - i;
        float yPos = boardOffsetY + i * cellSize + cellSize / 2 - fontSize / 2;

        sf::Text leftText(std::string(1, label), font, fontSize);
        leftText.setFillColor(sf::Color(220, 220, 220));
        leftText.setStyle(sf::Text::Bold);
        leftText.setPosition(boardOffsetX - fontSize - 28, yPos);
        window.draw(leftText);

        sf::Text rightText(std::string(1, label), font, fontSize);
        rightText.setFillColor(sf::Color(220, 220, 220));
        rightText.setStyle(sf::Text::Bold);
        rightText.setPosition(boardOffsetX + 8 * cellSize + 15, yPos);
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

void ChessGame::drawTimer(sf::RenderWindow& window, sf::Font& font) {
    int fontSize = std::max(24, (int)(cellSize * 0.42f));

    int whiteMin = (int)whiteTime / 60;
    int whiteSec = (int)whiteTime % 60;
    int blackMin = (int)blackTime / 60;
    int blackSec = (int)blackTime % 60;

    std::stringstream wss, bss;
    wss << whiteMin << ":" << (whiteSec < 10 ? "0" : "") << whiteSec;
    bss << blackMin << ":" << (blackSec < 10 ? "0" : "") << blackSec;

    float leftPanelX = boardOffsetX - 260;
    float topY = boardOffsetY + 80;

    sf::RectangleShape whiteTimerBg(sf::Vector2f(220, 120));
    whiteTimerBg.setPosition(leftPanelX, topY);
    whiteTimerBg.setFillColor(sf::Color(250, 250, 250, 255));
    whiteTimerBg.setOutlineColor(currentPlayer == WHITE ? sf::Color(50, 200, 50) : sf::Color(140, 140, 140));
    whiteTimerBg.setOutlineThickness(currentPlayer == WHITE ? 5 : 3);
    window.draw(whiteTimerBg);

    sf::Text whiteLabel("WHITE", font, fontSize - 2);
    whiteLabel.setFillColor(sf::Color(50, 50, 50));
    whiteLabel.setStyle(sf::Text::Bold);
    whiteLabel.setPosition(leftPanelX + 20, topY + 20);
    window.draw(whiteLabel);

    sf::Text whiteTimeText(wss.str(), font, fontSize + 8);
    whiteTimeText.setFillColor(currentPlayer == WHITE ? sf::Color(0, 150, 0) : sf::Color(80, 80, 80));
    whiteTimeText.setStyle(sf::Text::Bold);
    whiteTimeText.setPosition(leftPanelX + 20, topY + 65);
    window.draw(whiteTimeText);

    sf::RectangleShape blackTimerBg(sf::Vector2f(220, 120));
    blackTimerBg.setPosition(leftPanelX, topY + 160);
    blackTimerBg.setFillColor(sf::Color(45, 45, 45, 255));
    blackTimerBg.setOutlineColor(currentPlayer == BLACK ? sf::Color(50, 200, 50) : sf::Color(100, 100, 100));
    blackTimerBg.setOutlineThickness(currentPlayer == BLACK ? 5 : 3);
    window.draw(blackTimerBg);

    sf::Text blackLabel("BLACK", font, fontSize - 2);
    blackLabel.setFillColor(sf::Color(230, 230, 230));
    blackLabel.setStyle(sf::Text::Bold);
    blackLabel.setPosition(leftPanelX + 20, topY + 180);
    window.draw(blackLabel);

    sf::Text blackTimeText(bss.str(), font, fontSize + 8);
    blackTimeText.setFillColor(currentPlayer == BLACK ? sf::Color(100, 255, 100) : sf::Color(180, 180, 180));
    blackTimeText.setStyle(sf::Text::Bold);
    blackTimeText.setPosition(leftPanelX + 20, topY + 225);
    window.draw(blackTimeText);
}