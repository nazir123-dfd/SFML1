#include "ChessGame.h"

void ChessGame::render(sf::RenderWindow& window, sf::Font& font, sf::Vector2i mousePos) {
    window.clear();

    if (gameState == MENU) {
        drawMenu(window, font);
    }
    else if (gameState == INSTRUCTIONS) {
        drawInstructions(window, font);
    }
    else if (gameState == PLAYING) {
        sf::RectangleShape bg(sf::Vector2f(windowWidth, windowHeight));
        bg.setFillColor(sf::Color(60, 45, 35));
        window.draw(bg);

        drawBoard(window);
        drawBoardLabels(window, font);
        drawHighlights(window);
        drawPieces(window, mousePos);
        drawGameUI(window, font);

        if (isPromoting) {
            drawPromotionMenu(window, font);
        }
    }
    else if (gameState == GAME_OVER) {
        sf::RectangleShape bg(sf::Vector2f(windowWidth, windowHeight));
        bg.setFillColor(sf::Color(60, 45, 35));
        window.draw(bg);

        drawBoard(window);
        drawBoardLabels(window, font);
        drawPieces(window, mousePos);
        drawGameOver(window, font);
    }

    window.display();
}

void ChessGame::handleMousePress(sf::Vector2i mousePos) {
    if (gameState == MENU) {
        float centerX = windowWidth / 2.0f;
        for (int i = 0; i < 5; i++) {
            float btnY = 210 + i * 62;
            if (mousePos.x >= centerX - 160 && mousePos.x <= centerX + 160 &&
                mousePos.y >= btnY && mousePos.y <= btnY + 52) {
                if (i == 0) {
                    gameMode = PVP;
                    gameState = PLAYING;
                }
                else if (i == 1) {
                    gameMode = PVE_EASY;
                    gameState = PLAYING;
                }
                else if (i == 2) {
                    gameMode = PVE_MEDIUM;
                    gameState = PLAYING;
                }
                else if (i == 3) {
                    gameMode = PVE_HARD;
                    gameState = PLAYING;
                }
                else if (i == 4) {
                    gameState = INSTRUCTIONS;
                }
                break;
            }
        }
    }
    else if (gameState == INSTRUCTIONS) {
        if (mousePos.x >= windowWidth / 2 - 140 && mousePos.x <= windowWidth / 2 + 140 &&
            mousePos.y >= windowHeight / 2 + 220 && mousePos.y <= windowHeight / 2 + 280) {
            gameState = MENU;
        }
    }
    else if (gameState == PLAYING && !isPromoting) {
        float centerX = boardOffsetX + (8 * cellSize) / 2.0f;
        float forfeitY = boardOffsetY + 8 * cellSize + 50;

        if (mousePos.x >= centerX - 90 && mousePos.x <= centerX + 90 &&
            mousePos.y >= forfeitY && mousePos.y <= forfeitY + 55) {
            gameOver = true;
            winner = (currentPlayer == WHITE) ? BLACK : WHITE;
            gameState = GAME_OVER;
            return;
        }

        std::pair<int, int> pos = getBoardPosition(mousePos);
        if (pos.first != -1) {
            int row = pos.first;
            int col = pos.second;

            if (isPieceSelected) {
                bool isValidTarget = false;
                for (auto& move : validMoves) {
                    if (move.first == row && move.second == col) {
                        isValidTarget = true;
                        break;
                    }
                }

                if (isValidTarget) {
                    makeMove(selectedRow, selectedCol, row, col);
                    isPieceSelected = false;
                    selectedRow = -1;
                    selectedCol = -1;
                    validMoves.clear();
                    isDragging = false;
                }
                else if (board[row][col].type != EMPTY && board[row][col].color == currentPlayer) {
                    selectedRow = row;
                    selectedCol = col;
                    calculateValidMoves(row, col);
                    isDragging = true;
                    float cellX = boardOffsetX + col * cellSize;
                    float cellY = boardOffsetY + row * cellSize;
                    dragOffset = sf::Vector2f((float)mousePos.x - cellX, (float)mousePos.y - cellY);
                }
                else {
                    isPieceSelected = false;
                    selectedRow = -1;
                    selectedCol = -1;
                    validMoves.clear();
                    isDragging = false;
                }
            }
            else {
                if (board[row][col].type != EMPTY && board[row][col].color == currentPlayer) {
                    isPieceSelected = true;
                    selectedRow = row;
                    selectedCol = col;
                    float cellX = boardOffsetX + col * cellSize;
                    float cellY = boardOffsetY + row * cellSize;
                    dragOffset = sf::Vector2f((float)mousePos.x - cellX, (float)mousePos.y - cellY);
                    calculateValidMoves(row, col);
                    isDragging = true;
                }
            }
        }
    }
    else if (gameState == PLAYING && isPromoting) {
        if (mousePos.x >= windowWidth / 2 - 165 && mousePos.x <= windowWidth / 2 + 165) {
            if (mousePos.y >= windowHeight / 2 - 65 && mousePos.y < windowHeight / 2 + 3) {
                board[promoteRow][promoteCol].type = QUEEN;
                isPromoting = false;
                checkGameEnd();
            }
            else if (mousePos.y >= windowHeight / 2 + 3 && mousePos.y < windowHeight / 2 + 71) {
                board[promoteRow][promoteCol].type = ROOK;
                isPromoting = false;
                checkGameEnd();
            }
            else if (mousePos.y >= windowHeight / 2 + 71 && mousePos.y < windowHeight / 2 + 139) {
                board[promoteRow][promoteCol].type = BISHOP;
                isPromoting = false;
                checkGameEnd();
            }
            else if (mousePos.y >= windowHeight / 2 + 139 && mousePos.y < windowHeight / 2 + 207) {
                board[promoteRow][promoteCol].type = KNIGHT;
                isPromoting = false;
                checkGameEnd();
            }
        }
    }
    else if (gameState == GAME_OVER) {
        if (mousePos.x >= windowWidth / 2 - 140 && mousePos.x <= windowWidth / 2 + 140 &&
            mousePos.y >= windowHeight / 2 + 40 && mousePos.y <= windowHeight / 2 + 115) {
            resetGame();
            gameState = MENU;
        }
    }
}

void ChessGame::handleMouseRelease(sf::Vector2i mousePos) {
    if (isDragging && gameState == PLAYING && !isPromoting && isPieceSelected) {
        std::pair<int, int> pos = getBoardPosition(mousePos);
        if (pos.first != -1) {
            int toRow = pos.first;
            int toCol = pos.second;
            bool isValidTarget = false;
            for (auto& move : validMoves) {
                if (move.first == toRow && move.second == toCol) {
                    isValidTarget = true;
                    break;
                }
            }
            if (isValidTarget) {
                makeMove(selectedRow, selectedCol, toRow, toCol);
                isPieceSelected = false;
                selectedRow = -1;
                selectedCol = -1;
                validMoves.clear();
                isDragging = false;
                return;
            }
        }
        isDragging = false;
    }
}