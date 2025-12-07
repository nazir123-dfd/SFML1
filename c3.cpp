#include "ChessGame.h"

void ChessGame::drawBoard(sf::RenderWindow& window) {
    sf::Color lightBrown(240, 217, 181);
    sf::Color darkBrown(181, 136, 99);

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));
            cell.setPosition(boardOffsetX + j * cellSize, boardOffsetY + i * cellSize);
            if ((i + j) % 2 == 0) {
                cell.setFillColor(lightBrown);
            }
            else {
                cell.setFillColor(darkBrown);
            }
            window.draw(cell);
        }
    }
}

void ChessGame::drawBoardLabels(sf::RenderWindow& window, sf::Font& font) {
    int fontSize = std::max(14, (int)(cellSize * 0.28f));

    for (int i = 0; i < 8; i++) {
        char label = 'a' + i;
        sf::Text topText(std::string(1, label), font, fontSize);
        topText.setFillColor(sf::Color(200, 200, 200));
        topText.setStyle(sf::Text::Bold);
        float xPos = boardOffsetX + i * cellSize + cellSize / 2 - fontSize / 3;
        topText.setPosition(xPos, boardOffsetY - fontSize - 12);
        window.draw(topText);

        sf::Text bottomText(std::string(1, label), font, fontSize);
        bottomText.setFillColor(sf::Color(200, 200, 200));
        bottomText.setStyle(sf::Text::Bold);
        bottomText.setPosition(xPos, boardOffsetY + 8 * cellSize + 8);
        window.draw(bottomText);
    }

    for (int i = 0; i < 8; i++) {
        char label = '8' - i;
        sf::Text leftText(std::string(1, label), font, fontSize);
        leftText.setFillColor(sf::Color(200, 200, 200));
        leftText.setStyle(sf::Text::Bold);
        float yPos = boardOffsetY + i * cellSize + cellSize / 2 - fontSize / 2;
        leftText.setPosition(boardOffsetX - fontSize - 18, yPos);
        window.draw(leftText);

        sf::Text rightText(std::string(1, label), font, fontSize);
        rightText.setFillColor(sf::Color(200, 200, 200));
        rightText.setStyle(sf::Text::Bold);
        rightText.setPosition(boardOffsetX + 8 * cellSize + 12, yPos);
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
            highlight.setFillColor(sf::Color(255, 80, 80, 140));
        }
        else {
            highlight.setFillColor(sf::Color(100, 255, 100, 120));
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
    int fontSize = std::max(22, (int)(cellSize * 0.40f));

    int whiteMin = (int)whiteTime / 60;
    int whiteSec = (int)whiteTime % 60;
    int blackMin = (int)blackTime / 60;
    int blackSec = (int)blackTime % 60;

    std::stringstream wss, bss;
    wss << whiteMin << ":" << (whiteSec < 10 ? "0" : "") << whiteSec;
    bss << blackMin << ":" << (blackSec < 10 ? "0" : "") << blackSec;

    float leftPanelX = boardOffsetX - 240;
    float topY = boardOffsetY + 50;

    sf::RectangleShape whiteTimerBg(sf::Vector2f(200, 110));
    whiteTimerBg.setPosition(leftPanelX, topY);
    whiteTimerBg.setFillColor(sf::Color(245, 245, 245, 250));
    whiteTimerBg.setOutlineColor(sf::Color(160, 160, 160));
    whiteTimerBg.setOutlineThickness(3);
    window.draw(whiteTimerBg);

    if (currentPlayer == WHITE) {
        sf::CircleShape activeIndicator(8);
        activeIndicator.setFillColor(sf::Color(50, 200, 50));
        activeIndicator.setPosition(leftPanelX + 15, topY + 15);
        window.draw(activeIndicator);
    }

    sf::Text whiteLabel("WHITE", font, fontSize - 4);
    whiteLabel.setFillColor(sf::Color(60, 60, 60));
    whiteLabel.setStyle(sf::Text::Bold);
    whiteLabel.setPosition(leftPanelX + 20, topY + 25);
    window.draw(whiteLabel);

    sf::Text whiteTimeText(wss.str(), font, fontSize + 6);
    whiteTimeText.setFillColor(currentPlayer == WHITE ? sf::Color(0, 150, 0) : sf::Color(80, 80, 80));
    whiteTimeText.setStyle(sf::Text::Bold);
    whiteTimeText.setPosition(leftPanelX + 20, topY + 60);
    window.draw(whiteTimeText);

    sf::RectangleShape blackTimerBg(sf::Vector2f(200, 110));
    blackTimerBg.setPosition(leftPanelX, topY + 140);
    blackTimerBg.setFillColor(sf::Color(50, 50, 50, 250));
    blackTimerBg.setOutlineColor(sf::Color(100, 100, 100));
    blackTimerBg.setOutlineThickness(3);
    window.draw(blackTimerBg);

    if (currentPlayer == BLACK) {
        sf::CircleShape activeIndicator(8);
        activeIndicator.setFillColor(sf::Color(100, 255, 100));
        activeIndicator.setPosition(leftPanelX + 15, topY + 155);
        window.draw(activeIndicator);
    }

    sf::Text blackLabel("BLACK", font, fontSize - 4);
    blackLabel.setFillColor(sf::Color(220, 220, 220));
    blackLabel.setStyle(sf::Text::Bold);
    blackLabel.setPosition(leftPanelX + 20, topY + 165);
    window.draw(blackLabel);

    sf::Text blackTimeText(bss.str(), font, fontSize + 6);
    blackTimeText.setFillColor(currentPlayer == BLACK ? sf::Color(100, 255, 100) : sf::Color(180, 180, 180));
    blackTimeText.setStyle(sf::Text::Bold);
    blackTimeText.setPosition(leftPanelX + 20, topY + 200);
    window.draw(blackTimeText);
}