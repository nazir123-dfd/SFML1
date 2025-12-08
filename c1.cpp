#include "ChessGame.h"

void ChessGame::updateTimer() {
    if (!timeRunning || gameOver) return;

    if (currentPlayer == WHITE) {
        whiteTime -= whiteClock.restart().asSeconds();
        if (whiteTime <= 0) {
            whiteTime = 0;
            gameOver = true;
            winner = BLACK;
            gameState = GAME_OVER;
            timeRunning = false;
        }
    }
    else {
        blackTime -= blackClock.restart().asSeconds();
        if (blackTime <= 0) {
            blackTime = 0;
            gameOver = true;
            winner = WHITE;
            gameState = GAME_OVER;
            timeRunning = false;
        }
    }
}

void ChessGame::update() {
    if (gameState == PLAYING) {
        updateTimer();
        if (gameMode != PVP && currentPlayer == BLACK && !gameOver && !isPromoting && !aiThinking) {
            makeAIMove();
        }
    }
}

void ChessGame::undoMove() {
    if (moveHistory.empty()) return;

    int undoCount = (gameMode != PVP && moveHistory.size() >= 2) ? 2 : 1;

    for (int u = 0; u < undoCount && !moveHistory.empty(); u++) {
        Move lastMove = moveHistory.back();
        moveHistory.pop_back();

        board[lastMove.fromRow][lastMove.fromCol] = board[lastMove.toRow][lastMove.toCol];
        board[lastMove.toRow][lastMove.toCol] = lastMove.capturedPiece;

        if (lastMove.wasFirstMove) {
            board[lastMove.fromRow][lastMove.fromCol].hasMoved = false;
        }

        currentPlayer = (currentPlayer == WHITE) ? BLACK : WHITE;

        if (currentPlayer == WHITE) {
            whiteClock.restart();
        }
        else {
            blackClock.restart();
        }
    }

    isPieceSelected = false;
    isDragging = false;
    selectedRow = -1;
    selectedCol = -1;
    validMoves.clear();
    gameOver = false;
    winner = NONE;
}

std::string ChessGame::getMoveNotation(const Move& move) {
    std::string notation;

    char fromFile = 'a' + move.fromCol;
    char toFile = 'a' + move.toCol;
    int fromRank = 8 - move.fromRow;
    int toRank = 8 - move.toRow;

    Piece piece = board[move.toRow][move.toCol];

    switch (piece.type) {
    case KING: notation += "K"; break;
    case QUEEN: notation += "Q"; break;
    case ROOK: notation += "R"; break;
    case BISHOP: notation += "B"; break;
    case KNIGHT: notation += "N"; break;
    default: break;
    }

    notation += fromFile;
    notation += std::to_string(fromRank);

    if (move.capturedPiece.type != EMPTY) {
        notation += "x";
    }
    else {
        notation += "-";
    }

    notation += toFile;
    notation += std::to_string(toRank);

    return notation;
}

void ChessGame::handleKeyPress(sf::Keyboard::Key key) {
    if (gameState == PLAYING) {
        if (key == sf::Keyboard::U) {
            undoMove();
        }
        else if (key == sf::Keyboard::H) {
            hintsEnabled = !hintsEnabled;
            if (!hintsEnabled) {
                if (isPieceSelected) {
                    validMoves.clear();
                }
            }
            else {
                if (isPieceSelected) {
                    calculateValidMoves(selectedRow, selectedCol);
                }
            }
        }
    }
    else if (gameState == INSTRUCTIONS || gameState == GAME_OVER) {
        if (key == sf::Keyboard::Escape) {
            gameState = MENU;
        }
    }
}

void ChessGame::checkGameEnd() {
    bool inCheck = isInCheck(currentPlayer);
    bool hasLegals = hasLegalMove(currentPlayer);

    if (!hasLegals) {
        gameOver = true;
        if (inCheck) {
            winner = (currentPlayer == WHITE) ? BLACK : WHITE;
        }
        else {
            winner = NONE;
        }
        gameState = GAME_OVER;
        timeRunning = false;
    }
}

bool ChessGame::makeMove(int fromRow, int fromCol, int toRow, int toCol) {
    if (board[fromRow][fromCol].color != currentPlayer) return false;
    if (board[toRow][toCol].color == currentPlayer) return false;

    Piece tempPiece = board[toRow][toCol];
    Piece tempFrom = board[fromRow][fromCol];
    board[toRow][toCol] = board[fromRow][fromCol];
    board[fromRow][fromCol] = Piece();

    if (isInCheck(currentPlayer)) {
        board[fromRow][fromCol] = board[toRow][toCol];
        board[toRow][toCol] = tempPiece;
        return false;
    }

    Move newMove(fromRow, fromCol, toRow, toCol);
    newMove.capturedPiece = tempPiece;
    newMove.wasFirstMove = !tempFrom.hasMoved;

    board[toRow][toCol].hasMoved = true;

    if (board[toRow][toCol].type == PAWN) {
        if ((currentPlayer == WHITE && toRow == 0) || (currentPlayer == BLACK && toRow == 7)) {
            isPromoting = true;
            promoteRow = toRow;
            promoteCol = toCol;
        }
    }

    moveHistory.push_back(newMove);
    currentPlayer = (currentPlayer == WHITE) ? BLACK : WHITE;

    if (!timeRunning) {
        timeRunning = true;
        if (currentPlayer == WHITE) {
            whiteClock.restart();
        }
        else {
            blackClock.restart();
        }
    }
    else {
        if (currentPlayer == WHITE) {
            whiteClock.restart();
        }
        else {
            blackClock.restart();
        }
    }

    if (!isPromoting) {
        checkGameEnd();
    }

    return true;
}

void ChessGame::calculateValidMoves(int row, int col) {
    validMoves.clear();

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (isValidMove(row, col, i, j)) {
                Piece temp = board[i][j];
                Piece tempFrom = board[row][col];
                board[i][j] = board[row][col];
                board[row][col] = Piece();

                if (!isInCheck(currentPlayer)) {
                    validMoves.push_back(std::make_pair(i, j));
                }

                board[row][col] = tempFrom;
                board[i][j] = temp;
            }
        }
    }
}