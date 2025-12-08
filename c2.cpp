#include "ChessGame.h"

int ChessGame::evaluateBoard() {
    int score = 0;
    int pieceValues[7] = { 0, 10, 50, 30, 30, 90, 900 };

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (board[i][j].type != EMPTY) {
                int value = pieceValues[board[i][j].type];
                if (board[i][j].color == BLACK) {
                    score += value;
                }
                else {
                    score -= value;
                }
            }
        }
    }
    return score;
}

int ChessGame::minimax(int depth, int alpha, int beta, bool maximizing) {
    if (depth == 0) {
        return evaluateBoard();
    }

    Color playerColor = maximizing ? BLACK : WHITE;

    if (!hasLegalMove(playerColor)) {
        if (isInCheck(playerColor)) {
            return maximizing ? -10000 : 10000;
        }
        return 0;
    }

    if (maximizing) {
        int maxEval = std::numeric_limits<int>::min();

        for (int fr = 0; fr < 8; fr++) {
            for (int fc = 0; fc < 8; fc++) {
                if (board[fr][fc].color == BLACK) {
                    for (int tr = 0; tr < 8; tr++) {
                        for (int tc = 0; tc < 8; tc++) {
                            if (isValidMove(fr, fc, tr, tc)) {
                                Piece temp = board[tr][tc];
                                Piece tempFrom = board[fr][fc];
                                board[tr][tc] = board[fr][fc];
                                board[fr][fc] = Piece();

                                if (!isInCheck(BLACK)) {
                                    int eval = minimax(depth - 1, alpha, beta, false);
                                    maxEval = std::max(maxEval, eval);
                                    alpha = std::max(alpha, eval);
                                }

                                board[fr][fc] = tempFrom;
                                board[tr][tc] = temp;

                                if (beta <= alpha) break;
                            }
                        }
                        if (beta <= alpha) break;
                    }
                }
                if (beta <= alpha) break;
            }
            if (beta <= alpha) break;
        }
        return maxEval;
    }
    else {
        int minEval = std::numeric_limits<int>::max();

        for (int fr = 0; fr < 8; fr++) {
            for (int fc = 0; fc < 8; fc++) {
                if (board[fr][fc].color == WHITE) {
                    for (int tr = 0; tr < 8; tr++) {
                        for (int tc = 0; tc < 8; tc++) {
                            if (isValidMove(fr, fc, tr, tc)) {
                                Piece temp = board[tr][tc];
                                Piece tempFrom = board[fr][fc];
                                board[tr][tc] = board[fr][fc];
                                board[fr][fc] = Piece();

                                if (!isInCheck(WHITE)) {
                                    int eval = minimax(depth - 1, alpha, beta, true);
                                    minEval = std::min(minEval, eval);
                                    beta = std::min(beta, eval);
                                }

                                board[fr][fc] = tempFrom;
                                board[tr][tc] = temp;

                                if (beta <= alpha) break;
                            }
                        }
                        if (beta <= alpha) break;
                    }
                }
                if (beta <= alpha) break;
            }
            if (beta <= alpha) break;
        }
        return minEval;
    }
}

Move ChessGame::getBestMove(int depth) {
    Move bestMove(-1, -1, -1, -1);
    int bestValue = std::numeric_limits<int>::min();

    for (int fr = 0; fr < 8; fr++) {
        for (int fc = 0; fc < 8; fc++) {
            if (board[fr][fc].color == BLACK) {
                for (int tr = 0; tr < 8; tr++) {
                    for (int tc = 0; tc < 8; tc++) {
                        if (isValidMove(fr, fc, tr, tc)) {
                            Piece temp = board[tr][tc];
                            Piece tempFrom = board[fr][fc];
                            board[tr][tc] = board[fr][fc];
                            board[fr][fc] = Piece();

                            if (!isInCheck(BLACK)) {
                                int moveValue = minimax(depth - 1, std::numeric_limits<int>::min(), std::numeric_limits<int>::max(), false);

                                if (moveValue > bestValue) {
                                    bestValue = moveValue;
                                    bestMove = Move(fr, fc, tr, tc);
                                }
                            }

                            board[fr][fc] = tempFrom;
                            board[tr][tc] = temp;
                        }
                    }
                }
            }
        }
    }
    return bestMove;
}

void ChessGame::makeAIMove() {
    if (currentPlayer != BLACK || gameOver || isPromoting) return;

    aiThinking = true;

    int depth = 1;
    if (gameMode == PVE_MEDIUM) depth = 2;
    else if (gameMode == PVE_HARD) depth = 3;

    Move bestMove = getBestMove(depth);

    if (bestMove.fromRow != -1) {
        makeMove(bestMove.fromRow, bestMove.fromCol, bestMove.toRow, bestMove.toCol);

        if (isPromoting) {
            board[promoteRow][promoteCol].type = QUEEN;
            isPromoting = false;
            checkGameEnd();
        }
    }

    aiThinking = false;
}

bool ChessGame::isValidMove(int fromRow, int fromCol, int toRow, int toCol) {
    Piece piece = board[fromRow][fromCol];
    if (board[toRow][toCol].color == piece.color && piece.type != KING) return false;

    switch (piece.type) {
    case PAWN: return isValidPawnMove(fromRow, fromCol, toRow, toCol, piece.color);
    case ROOK: return isValidRookMove(fromRow, fromCol, toRow, toCol);
    case KNIGHT: return isValidKnightMove(fromRow, fromCol, toRow, toCol);
    case BISHOP: return isValidBishopMove(fromRow, fromCol, toRow, toCol);
    case QUEEN: return isValidQueenMove(fromRow, fromCol, toRow, toCol);
    case KING: return isValidKingMove(fromRow, fromCol, toRow, toCol);
    default: return false;
    }
}

bool ChessGame::isValidPawnMove(int fromRow, int fromCol, int toRow, int toCol, Color color) {
    int direction = (color == WHITE) ? -1 : 1;
    int startRow = (color == WHITE) ? 6 : 1;

    if (toCol == fromCol) {
        if (toRow == fromRow + direction && board[toRow][toCol].type == EMPTY) return true;
        if (fromRow == startRow && toRow == fromRow + 2 * direction &&
            board[fromRow + direction][fromCol].type == EMPTY &&
            board[toRow][toCol].type == EMPTY) return true;
    }

    if (std::abs(toCol - fromCol) == 1 && toRow == fromRow + direction) {
        if (board[toRow][toCol].type != EMPTY && board[toRow][toCol].color != color) return true;
    }

    return false;
}

bool ChessGame::isValidRookMove(int fromRow, int fromCol, int toRow, int toCol) {
    if (fromRow != toRow && fromCol != toCol) return false;
    return isPathClear(fromRow, fromCol, toRow, toCol);
}

bool ChessGame::isValidKnightMove(int fromRow, int fromCol, int toRow, int toCol) {
    int rowDiff = std::abs(toRow - fromRow);
    int colDiff = std::abs(toCol - fromCol);
    return (rowDiff == 2 && colDiff == 1) || (rowDiff == 1 && colDiff == 2);
}

bool ChessGame::isValidBishopMove(int fromRow, int fromCol, int toRow, int toCol) {
    if (std::abs(toRow - fromRow) != std::abs(toCol - fromCol)) return false;
    return isPathClear(fromRow, fromCol, toRow, toCol);
}

bool ChessGame::isValidQueenMove(int fromRow, int fromCol, int toRow, int toCol) {
    return isValidRookMove(fromRow, fromCol, toRow, toCol) || isValidBishopMove(fromRow, fromCol, toRow, toCol);
}

bool ChessGame::isValidKingMove(int fromRow, int fromCol, int toRow, int toCol) {
    int rowDiff = std::abs(toRow - fromRow);
    int colDiff = std::abs(toCol - fromCol);
    return (rowDiff <= 1 && colDiff <= 1);
}

bool ChessGame::isPathClear(int fromRow, int fromCol, int toRow, int toCol) {
    int rowDir = (toRow > fromRow) ? 1 : (toRow < fromRow) ? -1 : 0;
    int colDir = (toCol > fromCol) ? 1 : (toCol < fromCol) ? -1 : 0;

    int row = fromRow + rowDir;
    int col = fromCol + colDir;

    while (row != toRow || col != toCol) {
        if (board[row][col].type != EMPTY) return false;
        row += rowDir;
        col += colDir;
    }
    return true;
}

bool ChessGame::isSquareAttacked(int row, int col, Color defenderColor) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Piece attacker = board[i][j];
            if (attacker.color != NONE && attacker.color != defenderColor) {
                Piece tempTarget = board[row][col];
                board[row][col] = Piece(EMPTY, NONE);

                bool isAttackPathValid;
                if (attacker.type == KING) {
                    isAttackPathValid = (std::abs(i - row) <= 1 && std::abs(j - col) <= 1);
                }
                else {
                    isAttackPathValid = isValidMove(i, j, row, col);
                }

                board[row][col] = tempTarget;
                if (isAttackPathValid) return true;
            }
        }
    }
    return false;
}

bool ChessGame::isInCheck(Color color) {
    int kingRow = -1, kingCol = -1;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (board[i][j].type == KING && board[i][j].color == color) {
                kingRow = i;
                kingCol = j;
                break;
            }
        }
        if (kingRow != -1) break;
    }
    return isSquareAttacked(kingRow, kingCol, color);
}

bool ChessGame::hasLegalMove(Color color) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (board[i][j].color == color) {
                for (int ti = 0; ti < 8; ti++) {
                    for (int tj = 0; tj < 8; tj++) {
                        if (board[ti][tj].color == color) continue;
                        if (isValidMove(i, j, ti, tj)) {
                            Piece temp = board[ti][tj];
                            Piece tempFrom = board[i][j];
                            board[ti][tj] = board[i][j];
                            board[i][j] = Piece();

                            bool stillCheck = isInCheck(color);

                            board[i][j] = tempFrom;
                            board[ti][tj] = temp;

                            if (!stillCheck) return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

bool ChessGame::isCheckmate(Color color) {
    if (!isInCheck(color)) return false;
    return !hasLegalMove(color);
}

bool ChessGame::isStalemate(Color color) {
    if (isInCheck(color)) return false;
    return !hasLegalMove(color);
}