#include "ChessGame.h"

ChessGame::ChessGame() {
    windowWidth = 1200;
    windowHeight = 800;

    cellSize = 70;
    boardOffsetX = (windowWidth - 8 * cellSize) / 2;
    boardOffsetY = (windowHeight - 8 * cellSize) / 2;

    gameState = MENU;
    gameMode = PVP;
    currentPlayer = WHITE;
    gameOver = false;
    winner = NONE;

    isPieceSelected = false;//done!!!!!!!!
    isDragging = false;
    selectedRow = -1;
    selectedCol = -1;

    isPromoting = false;
    promoteRow = -1;
    promoteCol = -1;

    whiteTime = 600;
    blackTime = 600;
    timeRunning = false;

    hintsEnabled = true;
    aiThinking = false;

    initializeBoard();
    loadTextures();
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

void ChessGame::loadTextures() {
    if (!whitePawnTex.loadFromFile("assets/whitepawn.png")) {
        whitePawnTex.create(100, 100);
    }
    if (!whiteRookTex.loadFromFile("assets/whiterook.png")) {
        whiteRookTex.create(100, 100);
    }
    if (!whiteKnightTex.loadFromFile("assets/whiteknight.png")) {
        whiteKnightTex.create(100, 100);
    }
    if (!whiteBishopTex.loadFromFile("assets/whitebishop.png")) {
        whiteBishopTex.create(100, 100);
    }
    if (!whiteQueenTex.loadFromFile("assets/whitequeen.png")) {
        whiteQueenTex.create(100, 100);
    }
    if (!whiteKingTex.loadFromFile("assets/whiteking.png")) {
        whiteKingTex.create(100, 100);
    }

    if (!blackPawnTex.loadFromFile("assets/blackpawn.png")) {
        blackPawnTex.create(100, 100);
    }
    if (!blackRookTex.loadFromFile("assets/blackrook.png")) {
        blackRookTex.create(100, 100);
    }
    if (!blackKnightTex.loadFromFile("assets/blackknight.png")) {
        blackKnightTex.create(100, 100);
    }
    if (!blackBishopTex.loadFromFile("assets/blackbishop.png")) {
        blackBishopTex.create(100, 100);
    }
    if (!blackQueenTex.loadFromFile("assets/blackqueen.png")) {
        blackQueenTex.create(100, 100);
    }
    if (!blackKingTex.loadFromFile("assets/blackking.png")) {
        blackKingTex.create(100, 100);
    }

    backgroundTex.loadFromFile("assets/background.jpg");
}

sf::Texture* ChessGame::getPieceTexture(Piece p) {
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
    else if (p.color == BLACK) {
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
    return nullptr;
}

std::pair<int, int> ChessGame::getBoardPosition(sf::Vector2i mousePos) {
    float x = mousePos.x - boardOffsetX;
    float y = mousePos.y - boardOffsetY;

    if (x < 0 || x >= 8 * cellSize || y < 0 || y >= 8 * cellSize) {
        return std::make_pair(-1, -1);
    }

    int col = (int)(x / cellSize);
    int row = (int)(y / cellSize);

    return std::make_pair(row, col);
}

void ChessGame::resetGame() {
    currentPlayer = WHITE;
    gameOver = false;
    winner = NONE;
    isPieceSelected = false;
    isDragging = false;
    selectedRow = -1;
    selectedCol = -1;
    isPromoting = false;
    promoteRow = -1;
    promoteCol = -1;
    whiteTime = 600;
    blackTime = 600;
    timeRunning = false;
    aiThinking = false;
    scrollOffset = 0;
    moveHistory.clear();
    validMoves.clear();

    initializeBoard();
}

void ChessGame::resize(float width, float height) {
    windowWidth = width;
    windowHeight = height;

    float maxBoardSize = std::min(width * 0.55f, height * 0.85f);
    cellSize = maxBoardSize / 8.0f;

    boardOffsetX = (windowWidth - 8 * cellSize) / 2;
    boardOffsetY = (windowHeight - 8 * cellSize) / 2;
}

GameState ChessGame::getGameState() {
    return gameState;
}