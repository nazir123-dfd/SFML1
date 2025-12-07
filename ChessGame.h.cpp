#include "ChessGame.h"

ChessGame::ChessGame() {
    initializeBoard();
    currentPlayer = WHITE;
    gameOver = false;
    winner = NONE;
    gameState = MENU;
    gameMode = PVP;
    isPieceSelected = false;
    isDragging = false;
    selectedRow = -1;
    selectedCol = -1;
    isPromoting = false;
    whiteTime = 600.0f;
    blackTime = 600.0f;
    timeRunning = false;
    hintsEnabled = false;
    aiThinking = false;
    windowWidth = 1200;
    windowHeight = 800;
    loadTextures();
    updateLayout(windowWidth, windowHeight);
}

void ChessGame::loadTextures() {
    std::string basePath = "assets/";
    whitePawnTex.loadFromFile(basePath + "whitepawn.png");
    whiteRookTex.loadFromFile(basePath + "whiterook.png");
    whiteKnightTex.loadFromFile(basePath + "whiteknight.png");
    whiteBishopTex.loadFromFile(basePath + "whitebishop.png");
    whiteQueenTex.loadFromFile(basePath + "whitequeen.png");
    whiteKingTex.loadFromFile(basePath + "whiteking.png");
    blackPawnTex.loadFromFile(basePath + "blackpawn.png");
    blackRookTex.loadFromFile(basePath + "blackrook.png");
    blackKnightTex.loadFromFile(basePath + "blackknight.png");
    blackBishopTex.loadFromFile(basePath + "blackbishop.png");
    blackQueenTex.loadFromFile(basePath + "blackqueen.png");
    blackKingTex.loadFromFile(basePath + "blackking.png");
    backgroundTex.loadFromFile(basePath + "background.jpg");
}

void ChessGame::updateLayout(float width, float height) {
    windowWidth = width;
    windowHeight = height;

    float boardSize = std::min(width * 0.6f, height * 0.9f);
    cellSize = boardSize / 8.0f;
    boardOffsetX = (width - boardSize) / 2.0f;
    boardOffsetY = (height - boardSize) / 2.0f + 20.0f;
}

void ChessGame::resize(float width, float height) {
    updateLayout(width, height);
}

sf::Texture* ChessGame::getPieceTexture(Piece p) {
    if (p.type == EMPTY) return nullptr;
    if (p.color == WHITE) {
        switch (p.type) {
        case PAWN: return &whitePawnTex;
        case ROOK: return &whiteRookTex;
        case KNIGHT: return &whiteKnightTex;
        case BISHOP: return &whiteBishopTex;
        case QUEEN: return &whiteQueenTex;
        case KING: return &whiteKingTex;
        default: return nullptr;
        }
    }
    else {
        switch (p.type) {
        case PAWN: return &blackPawnTex;
        case ROOK: return &blackRookTex;
        case KNIGHT: return &blackKnightTex;
        case BISHOP: return &blackBishopTex;
        case QUEEN: return &blackQueenTex;
        case KING: return &blackKingTex;
        default: return nullptr;
        }
    }
}

void ChessGame::initializeBoard() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            board[i][j] = Piece();
        }
    }

    board[0][0] = Piece(ROOK, BLACK);
    board[0][1] = Piece(KNIGHT, BLACK);
    board[0][2] = Piece(BISHOP, BLACK);
    board[0][3] = Piece(QUEEN, BLACK);
    board[0][4] = Piece(KING, BLACK);
    board[0][5] = Piece(BISHOP, BLACK);
    board[0][6] = Piece(KNIGHT, BLACK);
    board[0][7] = Piece(ROOK, BLACK);

    for (int i = 0; i < 8; i++) {
        board[1][i] = Piece(PAWN, BLACK);
    }

    board[7][0] = Piece(ROOK, WHITE);
    board[7][1] = Piece(KNIGHT, WHITE);
    board[7][2] = Piece(BISHOP, WHITE);
    board[7][3] = Piece(QUEEN, WHITE);
    board[7][4] = Piece(KING, WHITE);
    board[7][5] = Piece(BISHOP, WHITE);
    board[7][6] = Piece(KNIGHT, WHITE);
    board[7][7] = Piece(ROOK, WHITE);

    for (int i = 0; i < 8; i++) {
        board[6][i] = Piece(PAWN, WHITE);
    }
}

void ChessGame::resetGame() {
    initializeBoard();
    currentPlayer = WHITE;
    gameOver = false;
    winner = NONE;
    isPieceSelected = false;
    isDragging = false;
    selectedRow = -1;
    selectedCol = -1;
    isPromoting = false;
    moveHistory.clear();
    validMoves.clear();
    whiteTime = 600.0f;
    blackTime = 600.0f;
    timeRunning = false;
    hintsEnabled = false;
    aiThinking = false;
}

std::pair<int, int> ChessGame::getBoardPosition(sf::Vector2i mousePos) {
    int col = (mousePos.x - boardOffsetX) / cellSize;
    int row = (mousePos.y - boardOffsetY) / cellSize;
    if (row >= 0 && row < 8 && col >= 0 && col < 8) {
        return std::make_pair(row, col);
    }
    return std::make_pair(-1, -1);
}

void ChessGame::calculateValidMoves(int row, int col) {
    validMoves.clear();
    if (board[row][col].color != currentPlayer) return;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (i == row && j == col) continue;
            if (isValidMove(row, col, i, j)) {
                Piece tempPiece = board[i][j];
                Piece tempFrom = board[row][col];
                board[i][j] = board[row][col];
                board[row][col] = Piece();

                bool inCheck = isInCheck(currentPlayer);

                board[row][col] = tempFrom;
                board[i][j] = tempPiece;

                if (!inCheck) {
                    validMoves.push_back(std::make_pair(i, j));
                }
            }
        }
    }
}

GameState ChessGame::getGameState() {
    return gameState;
}