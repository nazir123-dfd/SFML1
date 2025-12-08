////Piece.h
//#pragma once
//#ifndef PIECE_H
//#define PIECE_H
//
//#include <SFML/Graphics.hpp>
//
//enum Color { NONE, WHITE, BLACK };
//
//class Piece {
//protected:
//    Color color;
//    bool hasMoved;
//    sf::Texture* texture;
//
//public:
//    Piece();
//    Piece(Color c);
//    virtual ~Piece();
//
//    Color getColor() const;
//    bool getHasMoved() const;
//    void setHasMoved(bool moved);
//    sf::Texture* getTexture() const;
//    void setTexture(sf::Texture* tex);
//
//    virtual bool isValidMove(int fromRow, int fromCol, int toRow, int toCol,
//        Piece* board[8][8]) const = 0;
//    virtual char getSymbol() const = 0;
//    virtual Piece* clone() const = 0;
//};
//
//class Pawn : public Piece {
//public:
//    Pawn(Color c);
//    bool isValidMove(int fromRow, int fromCol, int toRow, int toCol,
//        Piece* board[8][8]) const override;
//    char getSymbol() const override;
//    Piece* clone() const override;
//};
//
//class Rook : public Piece {
//public:
//    Rook(Color c);
//    bool isValidMove(int fromRow, int fromCol, int toRow, int toCol,
//        Piece* board[8][8]) const override;
//    char getSymbol() const override;
//    Piece* clone() const override;
//};
//
//class Knight : public Piece {
//public:
//    Knight(Color c);
//    bool isValidMove(int fromRow, int fromCol, int toRow, int toCol,
//        Piece* board[8][8]) const override;
//    char getSymbol() const override;
//    Piece* clone() const override;
//};
//
//class Bishop : public Piece {
//public:
//    Bishop(Color c);
//    bool isValidMove(int fromRow, int fromCol, int toRow, int toCol,
//        Piece* board[8][8]) const override;
//    char getSymbol() const override;
//    Piece* clone() const override;
//};
//
//class Queen : public Piece {
//public:
//    Queen(Color c);
//    bool isValidMove(int fromRow, int fromCol, int toRow, int toCol,
//        Piece* board[8][8]) const override;
//    char getSymbol() const override;
//    Piece* clone() const override;
//};
//
//class King : public Piece {
//public:
//    King(Color c);
//    bool isValidMove(int fromRow, int fromCol, int toRow, int toCol,
//        Piece* board[8][8]) const override;
//    char getSymbol() const override;
//    Piece* clone() const override;
//};
//
//#endif
////Piece.cpp
//#include "Piece.h"
//#include <cmath>
//
//Piece::Piece() : color(NONE), hasMoved(false), texture(nullptr) {}
//
//Piece::Piece(Color c) : color(c), hasMoved(false), texture(nullptr) {}
//
//Piece::~Piece() {}
//
//Color Piece::getColor() const { return color; }
//
//bool Piece::getHasMoved() const { return hasMoved; }
//
//void Piece::setHasMoved(bool moved) { hasMoved = moved; }
//
//sf::Texture* Piece::getTexture() const { return texture; }
//
//void Piece::setTexture(sf::Texture* tex) { texture = tex; }
//
//Pawn::Pawn(Color c) : Piece(c) {}
//
//bool Pawn::isValidMove(int fromRow, int fromCol, int toRow, int toCol, Piece* board[8][8]) const {
//    int direction = (color == WHITE) ? -1 : 1;
//    int startRow = (color == WHITE) ? 6 : 1;
//
//    if (toCol == fromCol) {
//        if (toRow == fromRow + direction && board[toRow][toCol] == nullptr) return true;
//        if (fromRow == startRow && toRow == fromRow + 2 * direction &&
//            board[fromRow + direction][fromCol] == nullptr &&
//            board[toRow][toCol] == nullptr) return true;
//    }
//
//    if (std::abs(toCol - fromCol) == 1 && toRow == fromRow + direction) {
//        if (board[toRow][toCol] != nullptr && board[toRow][toCol]->getColor() != color) return true;
//    }
//
//    return false;
//}
//
//char Pawn::getSymbol() const { return 'P'; }
//
//Piece* Pawn::clone() const { return new Pawn(*this); }
//
//Rook::Rook(Color c) : Piece(c) {}
//
//bool Rook::isValidMove(int fromRow, int fromCol, int toRow, int toCol, Piece* board[8][8]) const {
//    if (fromRow != toRow && fromCol != toCol) return false;
//
//    int rowDir = (toRow > fromRow) ? 1 : (toRow < fromRow) ? -1 : 0;
//    int colDir = (toCol > fromCol) ? 1 : (toCol < fromCol) ? -1 : 0;
//
//    int row = fromRow + rowDir;
//    int col = fromCol + colDir;
//
//    while (row != toRow || col != toCol) {
//        if (board[row][col] != nullptr) return false;
//        row += rowDir;
//        col += colDir;
//    }
//    return true;
//}
//
//char Rook::getSymbol() const { return 'R'; }
//
//Piece* Rook::clone() const { return new Rook(*this); }
//
//Knight::Knight(Color c) : Piece(c) {}
//
//bool Knight::isValidMove(int fromRow, int fromCol, int toRow, int toCol, Piece* board[8][8]) const {
//    int rowDiff = std::abs(toRow - fromRow);
//    int colDiff = std::abs(toCol - fromCol);
//    return (rowDiff == 2 && colDiff == 1) || (rowDiff == 1 && colDiff == 2);
//}
//
//char Knight::getSymbol() const { return 'N'; }
//
//Piece* Knight::clone() const { return new Knight(*this); }
//
//Bishop::Bishop(Color c) : Piece(c) {}
//
//bool Bishop::isValidMove(int fromRow, int fromCol, int toRow, int toCol, Piece* board[8][8]) const {
//    if (std::abs(toRow - fromRow) != std::abs(toCol - fromCol)) return false;
//
//    int rowDir = (toRow > fromRow) ? 1 : -1;
//    int colDir = (toCol > fromCol) ? 1 : -1;
//
//    int row = fromRow + rowDir;
//    int col = fromCol + colDir;
//
//    while (row != toRow || col != toCol) {
//        if (board[row][col] != nullptr) return false;
//        row += rowDir;
//        col += colDir;
//    }
//    return true;
//}
//
//char Bishop::getSymbol() const { return 'B'; }
//
//Piece* Bishop::clone() const { return new Bishop(*this); }
//
//Queen::Queen(Color c) : Piece(c) {}
//
//bool Queen::isValidMove(int fromRow, int fromCol, int toRow, int toCol, Piece* board[8][8]) const {
//    if (fromRow == toRow || fromCol == toCol) {
//        int rowDir = (toRow > fromRow) ? 1 : (toRow < fromRow) ? -1 : 0;
//        int colDir = (toCol > fromCol) ? 1 : (toCol < fromCol) ? -1 : 0;
//
//        int row = fromRow + rowDir;
//        int col = fromCol + colDir;
//
//        while (row != toRow || col != toCol) {
//            if (board[row][col] != nullptr) return false;
//            row += rowDir;
//            col += colDir;
//        }
//        return true;
//    }
//
//    if (std::abs(toRow - fromRow) == std::abs(toCol - fromCol)) {
//        int rowDir = (toRow > fromRow) ? 1 : -1;
//        int colDir = (toCol > fromCol) ? 1 : -1;
//
//        int row = fromRow + rowDir;
//        int col = fromCol + colDir;
//
//        while (row != toRow || col != toCol) {
//            if (board[row][col] != nullptr) return false;
//            row += rowDir;
//            col += colDir;
//        }
//        return true;
//    }
//
//    return false;
//}
//
//char Queen::getSymbol() const { return 'Q'; }
//
//Piece* Queen::clone() const { return new Queen(*this); }
//
//King::King(Color c) : Piece(c) {}
//
//bool King::isValidMove(int fromRow, int fromCol, int toRow, int toCol, Piece* board[8][8]) const {
//    int rowDiff = std::abs(toRow - fromRow);
//    int colDiff = std::abs(toCol - fromCol);
//    return (rowDiff <= 1 && colDiff <= 1);
//}
//
//char King::getSymbol() const { return 'K'; }
//
//Piece* King::clone() const { return new King(*this); }
////Board.h
//#pragma once
//#ifndef BOARD_H
//#define BOARD_H
//
//#include "Piece.h"
//#include <vector>
//
//struct Move {
//    int fromRow, fromCol, toRow, toCol;
//    Piece* capturedPiece;
//    bool wasFirstMove;
//    Move(int fr, int fc, int tr, int tc);
//    ~Move();
//};
//
//class Board {
//private:
//    Piece* board[8][8];
//    std::vector<Move*> moveHistory;
//
//public:
//    Board();
//    ~Board();
//
//    void initialize();
//    Piece* getPiece(int row, int col) const;
//    void setPiece(int row, int col, Piece* piece);
//    bool isSquareEmpty(int row, int col) const;
//
//    bool isSquareAttacked(int row, int col, Color defenderColor) const;
//    bool isInCheck(Color color) const;
//    bool hasLegalMove(Color color);
//
//    std::vector<std::pair<int, int>> getValidMoves(int row, int col, Color currentPlayer);
//
//    bool makeMove(int fromRow, int fromCol, int toRow, int toCol, Color currentPlayer);
//    bool undoLastMove(Color& currentPlayer);
//
//    const std::vector<Move*>& getMoveHistory() const;
//
//    void clearBoard();
//    Board* clone() const;
//};
//
//#endif
////Board.cpp
//#include "Board.h"
//
//Move::Move(int fr, int fc, int tr, int tc)
//    : fromRow(fr), fromCol(fc), toRow(tr), toCol(tc),
//    capturedPiece(nullptr), wasFirstMove(false) {
//}
//
//Move::~Move() {
//    if (capturedPiece) {
//        delete capturedPiece;
//        capturedPiece = nullptr;
//    }
//}
//
//Board::Board() {
//    for (int i = 0; i < 8; i++) {
//        for (int j = 0; j < 8; j++) {
//            board[i][j] = nullptr;
//        }
//    }
//}
//
//Board::~Board() {
//    clearBoard();
//    for (Move* move : moveHistory) {
//        delete move;
//    }
//    moveHistory.clear();
//}
//
//void Board::clearBoard() {
//    for (int i = 0; i < 8; i++) {
//        for (int j = 0; j < 8; j++) {
//            if (board[i][j]) {
//                delete board[i][j];
//                board[i][j] = nullptr;
//            }
//        }
//    }
//}
//
//void Board::initialize() {
//    clearBoard();
//
//    board[0][0] = new Rook(BLACK);
//    board[0][1] = new Knight(BLACK);
//    board[0][2] = new Bishop(BLACK);
//    board[0][3] = new Queen(BLACK);
//    board[0][4] = new King(BLACK);
//    board[0][5] = new Bishop(BLACK);
//    board[0][6] = new Knight(BLACK);
//    board[0][7] = new Rook(BLACK);
//
//    for (int i = 0; i < 8; i++) {
//        board[1][i] = new Pawn(BLACK);
//    }
//
//    board[7][0] = new Rook(WHITE);
//    board[7][1] = new Knight(WHITE);
//    board[7][2] = new Bishop(WHITE);
//    board[7][3] = new Queen(WHITE);
//    board[7][4] = new King(WHITE);
//    board[7][5] = new Bishop(WHITE);
//    board[7][6] = new Knight(WHITE);
//    board[7][7] = new Rook(WHITE);
//
//    for (int i = 0; i < 8; i++) {
//        board[6][i] = new Pawn(WHITE);
//    }
//}
//
//Piece* Board::getPiece(int row, int col) const {
//    if (row < 0 || row >= 8 || col < 0 || col >= 8) return nullptr;
//    return board[row][col];
//}
//
//void Board::setPiece(int row, int col, Piece* piece) {
//    if (row >= 0 && row < 8 && col >= 0 && col < 8) {
//        board[row][col] = piece;
//    }
//}
//
//bool Board::isSquareEmpty(int row, int col) const {
//    return board[row][col] == nullptr;
//}
//
//bool Board::isSquareAttacked(int row, int col, Color defenderColor) const {
//    for (int i = 0; i < 8; i++) {
//        for (int j = 0; j < 8; j++) {
//            Piece* attacker = board[i][j];
//            if (attacker && attacker->getColor() != NONE && attacker->getColor() != defenderColor) {
//                Piece* tempTarget = board[row][col];
//                board[row][col] = nullptr;
//
//                bool isAttackPathValid;
//                King* king = dynamic_cast<King*>(attacker);
//                if (king) {
//                    isAttackPathValid = (std::abs(i - row) <= 1 && std::abs(j - col) <= 1);
//                }
//                else {
//                    isAttackPathValid = attacker->isValidMove(i, j, row, col, board);
//                }
//
//                board[row][col] = tempTarget;
//                if (isAttackPathValid) return true;
//            }
//        }
//    }
//    return false;
//}
//
//bool Board::isInCheck(Color color) const {
//    int kingRow = -1, kingCol = -1;
//    for (int i = 0; i < 8; i++) {
//        for (int j = 0; j < 8; j++) {
//            if (board[i][j]) {
//                King* king = dynamic_cast<King*>(board[i][j]);
//                if (king && board[i][j]->getColor() == color) {
//                    kingRow = i;
//                    kingCol = j;
//                    break;
//                }
//            }
//        }
//        if (kingRow != -1) break;
//    }
//    return isSquareAttacked(kingRow, kingCol, color);
//}
//
//bool Board::hasLegalMove(Color color) {
//    for (int i = 0; i < 8; i++) {
//        for (int j = 0; j < 8; j++) {
//            if (board[i][j] && board[i][j]->getColor() == color) {
//                for (int ti = 0; ti < 8; ti++) {
//                    for (int tj = 0; tj < 8; tj++) {
//                        if (board[ti][tj] && board[ti][tj]->getColor() == color) continue;
//
//                        if (board[i][j]->isValidMove(i, j, ti, tj, board)) {
//                            Piece* temp = board[ti][tj];
//                            board[ti][tj] = board[i][j];
//                            board[i][j] = nullptr;
//
//                            bool stillCheck = isInCheck(color);
//
//                            board[i][j] = board[ti][tj];
//                            board[ti][tj] = temp;
//
//                            if (!stillCheck) return true;
//                        }
//                    }
//                }
//            }
//        }
//    }
//    return false;
//}
//
//std::vector<std::pair<int, int>> Board::getValidMoves(int row, int col, Color currentPlayer) {
//    std::vector<std::pair<int, int>> validMoves;
//
//    if (!board[row][col] || board[row][col]->getColor() != currentPlayer) {
//        return validMoves;
//    }
//
//    for (int i = 0; i < 8; i++) {
//        for (int j = 0; j < 8; j++) {
//            if (board[i][j] && board[i][j]->getColor() == currentPlayer) continue;
//
//            if (board[row][col]->isValidMove(row, col, i, j, board)) {
//                Piece* temp = board[i][j];
//                board[i][j] = board[row][col];
//                board[row][col] = nullptr;
//
//                if (!isInCheck(currentPlayer)) {
//                    validMoves.push_back(std::make_pair(i, j));
//                }
//
//                board[row][col] = board[i][j];
//                board[i][j] = temp;
//            }
//        }
//    }
//    return validMoves;
//}
//
//bool Board::makeMove(int fromRow, int fromCol, int toRow, int toCol, Color currentPlayer) {
//    if (!board[fromRow][fromCol] || board[fromRow][fromCol]->getColor() != currentPlayer)
//        return false;
//    if (board[toRow][toCol] && board[toRow][toCol]->getColor() == currentPlayer)
//        return false;
//
//    Piece* tempPiece = board[toRow][toCol];
//    board[toRow][toCol] = board[fromRow][fromCol];
//    board[fromRow][fromCol] = nullptr;
//
//    if (isInCheck(currentPlayer)) {
//        board[fromRow][fromCol] = board[toRow][toCol];
//        board[toRow][toCol] = tempPiece;
//        return false;
//    }
//
//    Move* newMove = new Move(fromRow, fromCol, toRow, toCol);
//    newMove->capturedPiece = tempPiece ? tempPiece->clone() : nullptr;
//    newMove->wasFirstMove = !board[toRow][toCol]->getHasMoved();
//
//    board[toRow][toCol]->setHasMoved(true);
//    moveHistory.push_back(newMove);
//
//    if (tempPiece) {
//        delete tempPiece;
//    }
//
//    return true;
//}
//
//bool Board::undoLastMove(Color& currentPlayer) {
//    if (moveHistory.empty()) return false;
//
//    Move* lastMove = moveHistory.back();
//    moveHistory.pop_back();
//
//    board[lastMove->fromRow][lastMove->fromCol] = board[lastMove->toRow][lastMove->toCol];
//
//    if (lastMove->capturedPiece) {
//        board[lastMove->toRow][lastMove->toCol] = lastMove->capturedPiece->clone();
//    }
//    else {
//        board[lastMove->toRow][lastMove->toCol] = nullptr;
//    }
//
//    if (lastMove->wasFirstMove) {
//        board[lastMove->fromRow][lastMove->fromCol]->setHasMoved(false);
//    }
//
//    currentPlayer = (currentPlayer == WHITE) ? BLACK : WHITE;
//
//    delete lastMove;
//    return true;
//}
//
//const std::vector<Move*>& Board::getMoveHistory() const {
//    return moveHistory;
//}
//
//Board* Board::clone() const {
//    Board* newBoard = new Board();
//    for (int i = 0; i < 8; i++) {
//        for (int j = 0; j < 8; j++) {
//            if (board[i][j]) {
//                newBoard->board[i][j] = board[i][j]->clone();
//            }
//        }
//    }
//    return newBoard;
//}
////ChessGame.h.cpp
//#pragma once
//#ifndef CHESSGAME_H
//#define CHESSGAME_H
//
//#include <SFML/Graphics.hpp>
//#include <vector>
//#include <string>
//#include <sstream>
//#include <cmath>
//#include <algorithm>
//#include <limits>
//#include "Board.h"
//#include "Piece.h"
//
//enum GameState { MENU, INSTRUCTIONS, PLAYING, GAME_OVER };
//enum GameMode { PVP, PVE_EASY, PVE_MEDIUM, PVE_HARD };
//
//class ChessGame {
//private:
//    Board* gameBoard;
//    Color currentPlayer;
//    bool gameOver;
//    Color winner;
//    GameState gameState;
//    GameMode gameMode;
//
//    sf::Texture whitePawnTex, whiteRookTex, whiteKnightTex, whiteBishopTex, whiteQueenTex, whiteKingTex;
//    sf::Texture blackPawnTex, blackRookTex, blackKnightTex, blackBishopTex, blackQueenTex, blackKingTex;
//    sf::Texture backgroundTex;
//
//    float cellSize;
//    float boardOffsetX;
//    float boardOffsetY;
//    float windowWidth;
//    float windowHeight;
//
//    bool isPieceSelected;
//    bool isDragging;
//    int selectedRow, selectedCol;
//    sf::Vector2f dragOffset;
//    std::vector<std::pair<int, int>> validMoves;
//
//    bool isPromoting;
//    int promoteRow, promoteCol;
//
//    sf::Clock whiteClock;
//    sf::Clock blackClock;
//    float whiteTime;
//    float blackTime;
//    bool timeRunning;
//
//    bool hintsEnabled;
//    bool aiThinking;
//
//    sf::Texture* getPieceTexture(Piece* p);
//    void loadTextures();
//    void assignTexturesToPieces();
//    void updateLayout(float width, float height);
//
//    void drawBoard(sf::RenderWindow& window);
//    void drawBoardLabels(sf::RenderWindow& window, sf::Font& font);
//    void drawHighlights(sf::RenderWindow& window);
//    void drawPieces(sf::RenderWindow& window, sf::Vector2i mousePos);
//    void drawMenu(sf::RenderWindow& window, sf::Font& font);
//    void drawInstructions(sf::RenderWindow& window, sf::Font& font);
//    void drawGameOver(sf::RenderWindow& window, sf::Font& font);
//    void drawGameUI(sf::RenderWindow& window, sf::Font& font);
//    void drawPromotionMenu(sf::RenderWindow& window, sf::Font& font);
//    void drawCompactTimer(sf::RenderWindow& window, sf::Font& font);
//    void drawMoveHistory(sf::RenderWindow& window, sf::Font& font);
//    void drawControls(sf::RenderWindow& window, sf::Font& font);
//
//    std::pair<int, int> getBoardPosition(sf::Vector2i mousePos);
//    void calculateValidMoves(int row, int col);
//    void checkGameEnd();
//
//    void updateTimer();
//    void undoMove();
//    std::string getMoveNotation(const Move* move);
//
//    int evaluateBoard();
//    int minimax(Board* board, int depth, int alpha, int beta, bool maximizing);
//    std::pair<int, int> getBestMove(int depth);
//    void makeAIMove();
//
//public:
//    ChessGame();
//    ~ChessGame();
//    void handleMousePress(sf::Vector2i mousePos);
//    void handleMouseRelease(sf::Vector2i mousePos);
//    void handleKeyPress(sf::Keyboard::Key key);
//    bool makeMove(int fromRow, int fromCol, int toRow, int toCol);
//    void resetGame();
//    void render(sf::RenderWindow& window, sf::Font& font, sf::Vector2i mousePos);
//    void resize(float width, float height);
//    GameState getGameState();
//    void update();
//};
//
//#endif
////chess implementation
//#include "ChessGame.h"
//
//ChessGame::ChessGame() {
//    windowWidth = 1200;
//    windowHeight = 800;
//
//    cellSize = 70;
//    boardOffsetX = (windowWidth - 8 * cellSize) / 2;
//    boardOffsetY = (windowHeight - 8 * cellSize) / 2;
//
//    gameState = MENU;
//    gameMode = PVP;
//    currentPlayer = WHITE;
//    gameOver = false;
//    winner = NONE;
//
//    isPieceSelected = false;
//    isDragging = false;
//    selectedRow = -1;
//    selectedCol = -1;
//
//    isPromoting = false;
//    promoteRow = -1;
//    promoteCol = -1;
//
//    whiteTime = 600;
//    blackTime = 600;
//    timeRunning = false;
//
//    hintsEnabled = true;
//    aiThinking = false;
//
//    gameBoard = new Board();
//    gameBoard->initialize();
//
//    loadTextures();
//    assignTexturesToPieces();
//}
//
//ChessGame::~ChessGame() {
//    delete gameBoard;
//}
//
//void ChessGame::loadTextures() {
//    if (!whitePawnTex.loadFromFile("assets/whitepawn.png")) {
//        whitePawnTex.create(100, 100);
//    }
//    if (!whiteRookTex.loadFromFile("assets/whiterook.png")) {
//        whiteRookTex.create(100, 100);
//    }
//    if (!whiteKnightTex.loadFromFile("assets/whiteknight.png")) {
//        whiteKnightTex.create(100, 100);
//    }
//    if (!whiteBishopTex.loadFromFile("assets/whitebishop.png")) {
//        whiteBishopTex.create(100, 100);
//    }
//    if (!whiteQueenTex.loadFromFile("assets/whitequeen.png")) {
//        whiteQueenTex.create(100, 100);
//    }
//    if (!whiteKingTex.loadFromFile("assets/whiteking.png")) {
//        whiteKingTex.create(100, 100);
//    }
//
//    if (!blackPawnTex.loadFromFile("assets/blackpawn.png")) {
//        blackPawnTex.create(100, 100);
//    }
//    if (!blackRookTex.loadFromFile("assets/blackrook.png")) {
//        blackRookTex.create(100, 100);
//    }
//    if (!blackKnightTex.loadFromFile("assets/blackknight.png")) {
//        blackKnightTex.create(100, 100);
//    }
//    if (!blackBishopTex.loadFromFile("assets/blackbishop.png")) {
//        blackBishopTex.create(100, 100);
//    }
//    if (!blackQueenTex.loadFromFile("assets/blackqueen.png")) {
//        blackQueenTex.create(100, 100);
//    }
//    if (!blackKingTex.loadFromFile("assets/blackking.png")) {
//        blackKingTex.create(100, 100);
//    }
//
//    backgroundTex.loadFromFile("assets/background.jpg");
//}
//
//void ChessGame::assignTexturesToPieces() {
//    for (int i = 0; i < 8; i++) {
//        for (int j = 0; j < 8; j++) {
//            Piece* piece = gameBoard->getPiece(i, j);
//            if (piece) {
//                piece->setTexture(getPieceTexture(piece));
//            }
//        }
//    }
//}
//
//sf::Texture* ChessGame::getPieceTexture(Piece* p) {
//    if (!p) return nullptr;
//
//    if (p->getColor() == WHITE) {
//        if (dynamic_cast<Pawn*>(p)) return &whitePawnTex;
//        if (dynamic_cast<Rook*>(p)) return &whiteRookTex;
//        if (dynamic_cast<Knight*>(p)) return &whiteKnightTex;
//        if (dynamic_cast<Bishop*>(p)) return &whiteBishopTex;
//        if (dynamic_cast<Queen*>(p)) return &whiteQueenTex;
//        if (dynamic_cast<King*>(p)) return &whiteKingTex;
//    }
//    else if (p->getColor() == BLACK) {
//        if (dynamic_cast<Pawn*>(p)) return &blackPawnTex;
//        if (dynamic_cast<Rook*>(p)) return &blackRookTex;
//        if (dynamic_cast<Knight*>(p)) return &blackKnightTex;
//        if (dynamic_cast<Bishop*>(p)) return &blackBishopTex;
//        if (dynamic_cast<Queen*>(p)) return &blackQueenTex;
//        if (dynamic_cast<King*>(p)) return &blackKingTex;
//    }
//    return nullptr;
//}
//
//std::pair<int, int> ChessGame::getBoardPosition(sf::Vector2i mousePos) {
//    float x = mousePos.x - boardOffsetX;
//    float y = mousePos.y - boardOffsetY;
//
//    if (x < 0 || x >= 8 * cellSize || y < 0 || y >= 8 * cellSize) {
//        return std::make_pair(-1, -1);
//    }
//
//    int col = (int)(x / cellSize);
//    int row = (int)(y / cellSize);
//
//    return std::make_pair(row, col);
//}
//
//void ChessGame::resetGame() {
//    currentPlayer = WHITE;
//    gameOver = false;
//    winner = NONE;
//    isPieceSelected = false;
//    isDragging = false;
//    selectedRow = -1;
//    selectedCol = -1;
//    isPromoting = false;
//    promoteRow = -1;
//    promoteCol = -1;
//    whiteTime = 600;
//    blackTime = 600;
//    timeRunning = false;
//    aiThinking = false;
//
//    validMoves.clear();
//
//    delete gameBoard;
//    gameBoard = new Board();
//    gameBoard->initialize();
//    assignTexturesToPieces();
//}
//
//void ChessGame::resize(float width, float height) {
//    windowWidth = width;
//    windowHeight = height;
//
//    float maxBoardSize = std::min(width * 0.55f, height * 0.85f);
//    cellSize = maxBoardSize / 8.0f;
//
//    boardOffsetX = (windowWidth - 8 * cellSize) / 2;
//    boardOffsetY = (windowHeight - 8 * cellSize) / 2;
//}
//
//GameState ChessGame::getGameState() {
//    return gameState;
//}
//
//void ChessGame::updateTimer() {
//    if (!timeRunning || gameOver) return;
//
//    if (currentPlayer == WHITE) {
//        whiteTime -= whiteClock.restart().asSeconds();
//        if (whiteTime <= 0) {
//            whiteTime = 0;
//            gameOver = true;
//            winner = BLACK;
//            gameState = GAME_OVER;
//            timeRunning = false;
//        }
//    }
//    else {
//        blackTime -= blackClock.restart().asSeconds();
//        if (blackTime <= 0) {
//            blackTime = 0;
//            gameOver = true;
//            winner = WHITE;
//            gameState = GAME_OVER;
//            timeRunning = false;
//        }
//    }
//}
//
//void ChessGame::update() {
//    if (gameState == PLAYING) {
//        updateTimer();
//        if (gameMode != PVP && currentPlayer == BLACK && !gameOver && !isPromoting && !aiThinking) {
//            makeAIMove();
//        }
//    }
//}
//
//void ChessGame::undoMove() {
//    int undoCount = (gameMode != PVP && gameBoard->getMoveHistory().size() >= 2) ? 2 : 1;
//
//    for (int u = 0; u < undoCount; u++) {
//        if (!gameBoard->undoLastMove(currentPlayer)) break;
//    }
//
//    assignTexturesToPieces();
//    isPieceSelected = false;
//    isDragging = false;
//    selectedRow = -1;
//    selectedCol = -1;
//    validMoves.clear();
//    gameOver = false;
//    winner = NONE;
//
//    if (currentPlayer == WHITE) {
//        whiteClock.restart();
//    }
//    else {
//        blackClock.restart();
//    }
//}
//
//std::string ChessGame::getMoveNotation(const Move* move) {
//    std::string notation;
//
//    char fromFile = 'a' + move->fromCol;
//    char toFile = 'a' + move->toCol;
//    int fromRank = 8 - move->fromRow;
//    int toRank = 8 - move->toRow;
//
//    Piece* piece = gameBoard->getPiece(move->toRow, move->toCol);
//    if (piece) {
//        notation += piece->getSymbol();
//    }
//
//    notation += fromFile;
//    notation += std::to_string(fromRank);
//
//    if (move->capturedPiece) {
//        notation += "x";
//    }
//    else {
//        notation += "-";
//    }
//
//    notation += toFile;
//    notation += std::to_string(toRank);
//
//    return notation;
//}
//
//void ChessGame::handleKeyPress(sf::Keyboard::Key key) {
//    if (gameState == PLAYING) {
//        if (key == sf::Keyboard::U) {
//            undoMove();
//        }
//        else if (key == sf::Keyboard::H) {
//            hintsEnabled = !hintsEnabled;
//            if (!hintsEnabled) {
//                if (isPieceSelected) {
//                    validMoves.clear();
//                }
//            }
//            else {
//                if (isPieceSelected) {
//                    calculateValidMoves(selectedRow, selectedCol);
//                }
//            }
//        }
//    }
//    else if (gameState == INSTRUCTIONS || gameState == GAME_OVER) {
//        if (key == sf::Keyboard::Escape) {
//            gameState = MENU;
//        }
//    }
//}
//
//void ChessGame::checkGameEnd() {
//    bool inCheck = gameBoard->isInCheck(currentPlayer);
//    bool hasLegals = gameBoard->hasLegalMove(currentPlayer);
//
//    if (!hasLegals) {
//        gameOver = true;
//        if (inCheck) {
//            winner = (currentPlayer == WHITE) ? BLACK : WHITE;
//        }
//        else {
//            winner = NONE;
//        }
//        gameState = GAME_OVER;
//        timeRunning = false;
//    }
//}
//
//bool ChessGame::makeMove(int fromRow, int fromCol, int toRow, int toCol) {
//    if (!gameBoard->makeMove(fromRow, fromCol, toRow, toCol, currentPlayer)) {
//        return false;
//    }
//
//    Piece* movedPiece = gameBoard->getPiece(toRow, toCol);
//    if (movedPiece) {
//        movedPiece->setTexture(getPieceTexture(movedPiece));
//    }
//
//    if (dynamic_cast<Pawn*>(movedPiece)) {
//        if ((currentPlayer == WHITE && toRow == 0) || (currentPlayer == BLACK && toRow == 7)) {
//            isPromoting = true;
//            promoteRow = toRow;
//            promoteCol = toCol;
//        }
//    }
//
//    currentPlayer = (currentPlayer == WHITE) ? BLACK : WHITE;
//
//    if (!timeRunning) {
//        timeRunning = true;
//        if (currentPlayer == WHITE) {
//            whiteClock.restart();
//        }
//        else {
//            blackClock.restart();
//        }
//    }
//    else {
//        if (currentPlayer == WHITE) {
//            whiteClock.restart();
//        }
//        else {
//            blackClock.restart();
//        }
//    }
//
//    if (!isPromoting) {
//        checkGameEnd();
//    }
//
//    return true;
//}
//
//void ChessGame::calculateValidMoves(int row, int col) {
//    validMoves = gameBoard->getValidMoves(row, col, currentPlayer);
//}
////chess AI
//#include "ChessGame.h"
//
//int ChessGame::evaluateBoard() {
//    int score = 0;
//    int pieceValues[256];
//
//    for (int i = 0; i < 256; i++) pieceValues[i] = 0;
//    pieceValues['P'] = 10;
//    pieceValues['R'] = 50;
//    pieceValues['N'] = 30;
//    pieceValues['B'] = 30;
//    pieceValues['Q'] = 90;
//    pieceValues['K'] = 900;
//
//    for (int i = 0; i < 8; i++) {
//        for (int j = 0; j < 8; j++) {
//            Piece* piece = gameBoard->getPiece(i, j);
//            if (piece) {
//                int value = pieceValues[(int)piece->getSymbol()];
//                if (piece->getColor() == BLACK) {
//                    score += value;
//                }
//                else {
//                    score -= value;
//                }
//            }
//        }
//    }
//    return score;
//}
//
//int ChessGame::minimax(Board* board, int depth, int alpha, int beta, bool maximizing) {
//    if (depth == 0) {
//        int score = 0;
//        int pieceValues[256];
//
//        for (int i = 0; i < 256; i++) pieceValues[i] = 0;
//        pieceValues['P'] = 10;
//        pieceValues['R'] = 50;
//        pieceValues['N'] = 30;
//        pieceValues['B'] = 30;
//        pieceValues['Q'] = 90;
//        pieceValues['K'] = 900;
//
//        for (int i = 0; i < 8; i++) {
//            for (int j = 0; j < 8; j++) {
//                Piece* piece = board->getPiece(i, j);
//                if (piece) {
//                    int value = pieceValues[(int)piece->getSymbol()];
//                    if (piece->getColor() == BLACK) {
//                        score += value;
//                    }
//                    else {
//                        score -= value;
//                    }
//                }
//            }
//        }
//        return score;
//    }
//
//    Color playerColor = maximizing ? BLACK : WHITE;
//
//    if (!board->hasLegalMove(playerColor)) {
//        if (board->isInCheck(playerColor)) {
//            return maximizing ? -10000 : 10000;
//        }
//        return 0;
//    }
//
//    if (maximizing) {
//        int maxEval = std::numeric_limits<int>::min();
//
//        for (int fr = 0; fr < 8; fr++) {
//            for (int fc = 0; fc < 8; fc++) {
//                Piece* piece = board->getPiece(fr, fc);
//                if (piece && piece->getColor() == BLACK) {
//                    for (int tr = 0; tr < 8; tr++) {
//                        for (int tc = 0; tc < 8; tc++) {
//                            Piece* target = board->getPiece(tr, tc);
//                            if (target && target->getColor() == BLACK) continue;
//
//                            if (piece->isValidMove(fr, fc, tr, tc, const_cast<Piece***>(
//                                reinterpret_cast<Piece* const (*)[8]>(
//                                    &board->getPiece(0, 0))))) {
//
//                                Board* tempBoard = board->clone();
//                                if (tempBoard->makeMove(fr, fc, tr, tc, BLACK)) {
//                                    int eval = minimax(tempBoard, depth - 1, alpha, beta, false);
//                                    maxEval = std::max(maxEval, eval);
//                                    alpha = std::max(alpha, eval);
//                                    delete tempBoard;
//
//                                    if (beta <= alpha) break;
//                                }
//                                else {
//                                    delete tempBoard;
//                                }
//                            }
//                        }
//                        if (beta <= alpha) break;
//                    }
//                }
//                if (beta <= alpha) break;
//            }
//            if (beta <= alpha) break;
//        }
//        return maxEval;
//    }
//    else {
//        int minEval = std::numeric_limits<int>::max();
//
//        for (int fr = 0; fr < 8; fr++) {
//            for (int fc = 0; fc < 8; fc++) {
//                Piece* piece = board->getPiece(fr, fc);
//                if (piece && piece->getColor() == WHITE) {
//                    for (int tr = 0; tr < 8; tr++) {
//                        for (int tc = 0; tc < 8; tc++) {
//                            Piece* target = board->getPiece(tr, tc);
//                            if (target && target->getColor() == WHITE) continue;
//
//                            if (piece->isValidMove(fr, fc, tr, tc, const_cast<Piece***>(
//                                reinterpret_cast<Piece* const (*)[8]>(
//                                    &board->getPiece(0, 0))))) {
//
//                                Board* tempBoard = board->clone();
//                                if (tempBoard->makeMove(fr, fc, tr, tc, WHITE)) {
//                                    int eval = minimax(tempBoard, depth - 1, alpha, beta, true);
//                                    minEval = std::min(minEval, eval);
//                                    beta = std::min(beta, eval);
//                                    delete tempBoard;
//
//                                    if (beta <= alpha) break;
//                                }
//                                else {
//                                    delete tempBoard;
//                                }
//                            }
//                        }
//                        if (beta <= alpha) break;
//                    }
//                }
//                if (beta <= alpha) break;
//            }
//            if (beta <= alpha) break;
//        }
//        return minEval;
//    }
//}
//
//std::pair<int, int> ChessGame::getBestMove(int depth) {
//    int bestFromRow = -1, bestFromCol = -1;
//    int bestToRow = -1, bestToCol = -1;
//    int bestValue = std::numeric_limits<int>::min();
//
//    for (int fr = 0; fr < 8; fr++) {
//        for (int fc = 0; fc < 8; fc++) {
//            Piece* piece = gameBoard->getPiece(fr, fc);
//            if (piece && piece->getColor() == BLACK) {
//                for (int tr = 0; tr < 8; tr++) {
//                    for (int tc = 0; tc < 8; tc++) {
//                        Piece* target = gameBoard->getPiece(tr, tc);
//                        if (target && target->getColor() == BLACK) continue;
//
//                        Board* tempBoard = gameBoard->clone();
//                        if (tempBoard->makeMove(fr, fc, tr, tc, BLACK)) {
//                            int moveValue = minimax(tempBoard, depth - 1,
//                                std::numeric_limits<int>::min(),
//                                std::numeric_limits<int>::max(), false);
//
//                            if (moveValue > bestValue) {
//                                bestValue = moveValue;
//                                bestFromRow = fr;
//                                bestFromCol = fc;
//                                bestToRow = tr;
//                                bestToCol = tc;
//                            }
//                            delete tempBoard;
//                        }
//                        else {
//                            delete tempBoard;
//                        }
//                    }
//                }
//            }
//        }
//    }
//
//    return std::make_pair((bestFromRow << 24) | (bestFromCol << 16) | (bestToRow << 8) | bestToCol, bestValue);
//}
//
//void ChessGame::makeAIMove() {
//    if (currentPlayer != BLACK || gameOver || isPromoting) return;
//
//    aiThinking = true;
//
//    int depth = 1;
//    if (gameMode == PVE_MEDIUM) depth = 2;
//    else if (gameMode == PVE_HARD) depth = 3;
//
//    std::pair<int, int> result = getBestMove(depth);
//    int moveData = result.first;
//
//    int bestFromRow = (moveData >> 24) & 0xFF;
//    int bestFromCol = (moveData >> 16) & 0xFF;
//    int bestToRow = (moveData >> 8) & 0xFF;
//    int bestToCol = moveData & 0xFF;
//
//    if (bestFromRow != -1) {
//        makeMove(bestFromRow, bestFromCol, bestToRow, bestToCol);
//
//        if (isPromoting) {
//            delete gameBoard->getPiece(promoteRow, promoteCol);
//            gameBoard->setPiece(promoteRow, promoteCol, new Queen(BLACK));
//            gameBoard->getPiece(promoteRow, promoteCol)->setTexture(getPieceTexture(gameBoard->getPiece(promoteRow, promoteCol)));
//            gameBoard->getPiece(promoteRow, promoteCol)->setHasMoved(true);
//            isPromoting = false;
//            checkGameEnd();
//        }
//    }
//
//    aiThinking = false;
//}
//// chess draw1
//#include "ChessGame.h"
//
//void ChessGame::drawBoard(sf::RenderWindow& window) {
//    sf::Color lightWood(240, 217, 181);
//    sf::Color darkWood(181, 136, 99);
//
//    for (int i = 0; i < 8; i++) {
//        for (int j = 0; j < 8; j++) {
//            sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));
//            cell.setPosition(boardOffsetX + j * cellSize, boardOffsetY + i * cellSize);
//
//            if ((i + j) % 2 == 0) {
//                cell.setFillColor(lightWood);
//            }
//            else {
//                cell.setFillColor(darkWood);
//            }
//            window.draw(cell);
//        }
//    }
//}
//
//void ChessGame::drawBoardLabels(sf::RenderWindow& window, sf::Font& font) {
//    int fontSize = std::max(14, (int)(cellSize * 0.25f));
//
//    for (int i = 0; i < 8; i++) {
//        char label = 'a' + i;
//        float xPos = boardOffsetX + i * cellSize + cellSize / 2 - fontSize / 3;
//
//        sf::Text topText(std::string(1, label), font, fontSize);
//        topText.setFillColor(sf::Color(200, 200, 200));
//        topText.setStyle(sf::Text::Bold);
//        topText.setPosition(xPos, boardOffsetY - fontSize - 20);
//        window.draw(topText);
//
//        sf::Text bottomText(std::string(1, label), font, fontSize);
//        bottomText.setFillColor(sf::Color(200, 200, 200));
//        bottomText.setStyle(sf::Text::Bold);
//        bottomText.setPosition(xPos, boardOffsetY + 8 * cellSize + 10);
//        window.draw(bottomText);
//    }
//
//    for (int i = 0; i < 8; i++) {
//        char label = '8' - i;
//        float yPos = boardOffsetY + i * cellSize + cellSize / 2 - fontSize / 2;
//
//        sf::Text leftText(std::string(1, label), font, fontSize);
//        leftText.setFillColor(sf::Color(200, 200, 200));
//        leftText.setStyle(sf::Text::Bold);
//        leftText.setPosition(boardOffsetX - fontSize - 20, yPos);
//        window.draw(leftText);
//
//        sf::Text rightText(std::string(1, label), font, fontSize);
//        rightText.setFillColor(sf::Color(200, 200, 200));
//        rightText.setStyle(sf::Text::Bold);
//        rightText.setPosition(boardOffsetX + 8 * cellSize + 10, yPos);
//        window.draw(rightText);
//    }
//}
//
//void ChessGame::drawHighlights(sf::RenderWindow& window) {
//    if (!isPieceSelected || !hintsEnabled) return;
//
//    sf::RectangleShape selectedHighlight(sf::Vector2f(cellSize, cellSize));
//    selectedHighlight.setPosition(boardOffsetX + selectedCol * cellSize, boardOffsetY + selectedRow * cellSize);
//    selectedHighlight.setFillColor(sf::Color(255, 255, 100, 100));
//    window.draw(selectedHighlight);
//
//    for (auto& move : validMoves) {
//        sf::RectangleShape highlight(sf::Vector2f(cellSize, cellSize));
//        highlight.setPosition(boardOffsetX + move.second * cellSize, boardOffsetY + move.first * cellSize);
//
//        if (!gameBoard->isSquareEmpty(move.first, move.second)) {
//            highlight.setFillColor(sf::Color(255, 70, 70, 150));
//        }
//        else {
//            highlight.setFillColor(sf::Color(100, 255, 100, 130));
//        }
//        window.draw(highlight);
//    }
//}
//
//void ChessGame::drawPieces(sf::RenderWindow& window, sf::Vector2i mousePos) {
//    for (int i = 0; i < 8; i++) {
//        for (int j = 0; j < 8; j++) {
//            if (isDragging && i == selectedRow && j == selectedCol) continue;
//
//            Piece* piece = gameBoard->getPiece(i, j);
//            if (piece) {
//                sf::Texture* tex = piece->getTexture();
//                if (tex) {
//                    sf::Sprite sprite(*tex);
//                    sprite.setPosition(boardOffsetX + j * cellSize, boardOffsetY + i * cellSize);
//                    float scaleX = cellSize / tex->getSize().x;
//                    float scaleY = cellSize / tex->getSize().y;
//                    sprite.setScale(scaleX, scaleY);
//                    window.draw(sprite);
//                }
//            }
//        }
//    }
//
//    if (isDragging && selectedRow != -1) {
//        Piece* piece = gameBoard->getPiece(selectedRow, selectedCol);
//        if (piece) {
//            sf::Texture* tex = piece->getTexture();
//            if (tex) {
//                sf::Sprite sprite(*tex);
//                sprite.setPosition(mousePos.x - dragOffset.x, mousePos.y - dragOffset.y);
//                float scaleX = cellSize / tex->getSize().x;
//                float scaleY = cellSize / tex->getSize().y;
//                sprite.setScale(scaleX, scaleY);
//                window.draw(sprite);
//            }
//        }
//    }
//}
//
//void ChessGame::drawCompactTimer(sf::RenderWindow& window, sf::Font& font) {
//    int fontSize = std::max(16, (int)(cellSize * 0.28f));
//
//    int whiteMin = (int)whiteTime / 60;
//    int whiteSec = (int)whiteTime % 60;
//    int blackMin = (int)blackTime / 60;
//    int blackSec = (int)blackTime % 60;
//
//    std::stringstream wss, bss;
//    wss << whiteMin << ":" << (whiteSec < 10 ? "0" : "") << whiteSec;
//    bss << blackMin << ":" << (blackSec < 10 ? "0" : "") << blackSec;
//
//    float topY = boardOffsetY + 20;
//    float leftX = 30;
//
//    sf::RectangleShape whiteBox(sf::Vector2f(140, 70));
//    whiteBox.setPosition(leftX, topY);
//    whiteBox.setFillColor(sf::Color(245, 245, 245));
//    whiteBox.setOutlineColor(currentPlayer == WHITE ? sf::Color(50, 200, 50) : sf::Color(120, 120, 120));
//    whiteBox.setOutlineThickness(currentPlayer == WHITE ? 4 : 2);
//    window.draw(whiteBox);
//
//    sf::Text whiteLabel("WHITE", font, fontSize - 4);
//    whiteLabel.setFillColor(sf::Color(40, 40, 40));
//    whiteLabel.setStyle(sf::Text::Bold);
//    whiteLabel.setPosition(leftX + 10, topY + 10);
//    window.draw(whiteLabel);
//
//    sf::Text whiteTimeText(wss.str(), font, fontSize + 4);
//    whiteTimeText.setFillColor(currentPlayer == WHITE ? sf::Color(0, 150, 0) : sf::Color(80, 80, 80));
//    whiteTimeText.setStyle(sf::Text::Bold);
//    whiteTimeText.setPosition(leftX + 10, topY + 40);
//    window.draw(whiteTimeText);
//
//    sf::RectangleShape blackBox(sf::Vector2f(140, 70));
//    blackBox.setPosition(leftX, topY + 90);
//    blackBox.setFillColor(sf::Color(40, 40, 40));
//    blackBox.setOutlineColor(currentPlayer == BLACK ? sf::Color(50, 200, 50) : sf::Color(100, 100, 100));
//    blackBox.setOutlineThickness(currentPlayer == BLACK ? 4 : 2);
//    window.draw(blackBox);
//
//    sf::Text blackLabel("BLACK", font, fontSize - 4);
//    blackLabel.setFillColor(sf::Color(220, 220, 220));
//    blackLabel.setStyle(sf::Text::Bold);
//    blackLabel.setPosition(leftX + 10, topY + 100);
//    window.draw(blackLabel);
//
//    sf::Text blackTimeText(bss.str(), font, fontSize + 4);
//    blackTimeText.setFillColor(currentPlayer == BLACK ? sf::Color(100, 255, 100) : sf::Color(180, 180, 180));
//    blackTimeText.setStyle(sf::Text::Bold);
//    blackTimeText.setPosition(leftX + 10, topY + 130);
//    window.draw(blackTimeText);
//}
////chess draw2
//#include "ChessGame.h"
//
//void ChessGame::drawMoveHistory(sf::RenderWindow& window, sf::Font& font) {
//    int fontSize = std::max(13, (int)(cellSize * 0.21f));
//    float rightX = boardOffsetX + 8 * cellSize + 30;
//    float startY = boardOffsetY + 20;
//
//    sf::RectangleShape historyBg(sf::Vector2f(240, 650));
//    historyBg.setPosition(rightX, startY);
//    historyBg.setFillColor(sf::Color(35, 28, 22, 240));
//    historyBg.setOutlineColor(sf::Color(180, 150, 90));
//    historyBg.setOutlineThickness(3);
//    window.draw(historyBg);
//
//    sf::Text historyTitle("Move History", font, fontSize + 6);
//    historyTitle.setFillColor(sf::Color(255, 220, 120));
//    historyTitle.setStyle(sf::Text::Bold);
//    historyTitle.setPosition(rightX + 20, startY + 18);
//    window.draw(historyTitle);
//
//    sf::RectangleShape divider(sf::Vector2f(200, 2));
//    divider.setPosition(rightX + 20, startY + 52);
//    divider.setFillColor(sf::Color(218, 165, 32, 150));
//    window.draw(divider);
//
//    const std::vector<Move*>& history = gameBoard->getMoveHistory();
//    int maxMoves = 32;
//    int startIdx = std::max(0, (int)history.size() - maxMoves);
//
//    for (int i = startIdx; i < history.size(); i++) {
//        std::string notation = getMoveNotation(history[i]);
//
//        sf::RectangleShape moveBg(sf::Vector2f(200, fontSize + 8));
//        moveBg.setPosition(rightX + 20, startY + 70 + (i - startIdx) * (fontSize + 10));
//
//        if (i == history.size() - 1) {
//            moveBg.setFillColor(sf::Color(80, 60, 40, 100));
//        }
//        else if ((i - startIdx) % 2 == 0) {
//            moveBg.setFillColor(sf::Color(50, 40, 30, 50));
//        }
//        else {
//            moveBg.setFillColor(sf::Color(45, 35, 25, 30));
//        }
//        window.draw(moveBg);
//
//        int moveNum = (i / 2) + 1;
//        bool isWhiteMove = (i % 2 == 0);
//
//        std::stringstream ss;
//        if (isWhiteMove) {
//            ss << moveNum << ". " << notation;
//        }
//        else {
//            ss << "    " << notation;
//        }
//
//        sf::Text moveText(ss.str(), font, fontSize);
//        moveText.setFillColor(sf::Color(230, 230, 230));
//        moveText.setPosition(rightX + 28, startY + 72 + (i - startIdx) * (fontSize + 10));
//        window.draw(moveText);
//    }
//}
//
//void ChessGame::drawControls(sf::RenderWindow& window, sf::Font& font) {
//    int fontSize = std::max(14, (int)(cellSize * 0.22f));
//    float leftX = 30;
//    float startY = boardOffsetY + 200;
//
//    sf::RectangleShape controlsBg(sf::Vector2f(140, 200));
//    controlsBg.setPosition(leftX, startY);
//    controlsBg.setFillColor(sf::Color(35, 28, 22, 240));
//    controlsBg.setOutlineColor(sf::Color(180, 150, 90));
//    controlsBg.setOutlineThickness(3);
//    window.draw(controlsBg);
//
//    sf::Text controlsTitle("Controls", font, fontSize + 3);
//    controlsTitle.setFillColor(sf::Color(255, 220, 120));
//    controlsTitle.setStyle(sf::Text::Bold);
//    controlsTitle.setPosition(leftX + 15, startY + 15);
//    window.draw(controlsTitle);
//
//    sf::RectangleShape divider(sf::Vector2f(110, 2));
//    divider.setPosition(leftX + 15, startY + 45);
//    divider.setFillColor(sf::Color(218, 165, 32, 150));
//    window.draw(divider);
//
//    std::vector<std::string> controls = {
//        "U - Undo",
//        "H - Hints"
//    };
//
//    for (int i = 0; i < controls.size(); i++) {
//        sf::Text text(controls[i], font, fontSize - 1);
//        text.setFillColor(sf::Color(230, 230, 230));
//        text.setPosition(leftX + 18, startY + 60 + i * (fontSize + 12));
//        window.draw(text);
//    }
//
//    if (gameBoard->isInCheck(currentPlayer)) {
//        sf::RectangleShape checkBox(sf::Vector2f(110, 35));
//        checkBox.setPosition(leftX + 15, startY + 140);
//        checkBox.setFillColor(sf::Color(180, 30, 30, 200));
//        checkBox.setOutlineColor(sf::Color::Red);
//        checkBox.setOutlineThickness(2);
//        window.draw(checkBox);
//
//        sf::Text checkText("CHECK!", font, fontSize + 2);
//        checkText.setFillColor(sf::Color::White);
//        checkText.setStyle(sf::Text::Bold);
//        checkText.setPosition(leftX + 25, startY + 147);
//        window.draw(checkText);
//    }
//    else if (hintsEnabled) {
//        sf::RectangleShape hintBox(sf::Vector2f(110, 35));
//        hintBox.setPosition(leftX + 15, startY + 140);
//        hintBox.setFillColor(sf::Color(30, 120, 30, 150));
//        hintBox.setOutlineColor(sf::Color(50, 200, 50));
//        hintBox.setOutlineThickness(2);
//        window.draw(hintBox);
//
//        sf::Text hintStatus("Hints: ON", font, fontSize);
//        hintStatus.setFillColor(sf::Color(180, 255, 180));
//        hintStatus.setStyle(sf::Text::Bold);
//        hintStatus.setPosition(leftX + 22, startY + 147);
//        window.draw(hintStatus);
//    }
//}
//
//void ChessGame::drawGameUI(sf::RenderWindow& window, sf::Font& font) {
//    drawCompactTimer(window, font);
//    drawMoveHistory(window, font);
//    drawControls(window, font);
//
//    int fontSize = std::max(16, (int)(cellSize * 0.28f));
//    float leftX = 30;
//    float forfeitY = boardOffsetY + 430;
//
//    sf::RectangleShape forfeitBtn(sf::Vector2f(140, 50));
//    forfeitBtn.setPosition(leftX, forfeitY);
//    forfeitBtn.setFillColor(sf::Color(140, 50, 50));
//    forfeitBtn.setOutlineColor(sf::Color(200, 100, 100));
//    forfeitBtn.setOutlineThickness(3);
//    window.draw(forfeitBtn);
//
//    sf::Text forfeitText("FORFEIT", font, fontSize + 1);
//    forfeitText.setFillColor(sf::Color::White);
//    forfeitText.setStyle(sf::Text::Bold);
//    float textX = leftX + 70 - forfeitText.getGlobalBounds().width / 2;
//    forfeitText.setPosition(textX, forfeitY + 13);
//    window.draw(forfeitText);
//}
////chess draw3
//#include "ChessGame.h"
//
//void ChessGame::drawMenu(sf::RenderWindow& window, sf::Font& font) {
//    if (backgroundTex.getSize().x > 0) {
//        sf::Sprite bgSprite(backgroundTex);
//        float scaleX = (float)windowWidth / backgroundTex.getSize().x;
//        float scaleY = (float)windowHeight / backgroundTex.getSize().y;
//        float scale = std::max(scaleX, scaleY);
//        bgSprite.setScale(scale, scale);
//        float offsetX = (windowWidth - backgroundTex.getSize().x * scale) / 2.0f;
//        float offsetY = (windowHeight - backgroundTex.getSize().y * scale) / 2.0f;
//        bgSprite.setPosition(offsetX, offsetY);
//        window.draw(bgSprite);
//
//        sf::RectangleShape overlay(sf::Vector2f((float)windowWidth, (float)windowHeight));
//        overlay.setFillColor(sf::Color(0, 0, 0, 140));
//        window.draw(overlay);
//    }
//    else {
//        sf::RectangleShape bg(sf::Vector2f((float)windowWidth, (float)windowHeight));
//        bg.setFillColor(sf::Color(50, 50, 50));
//        window.draw(bg);
//    }
//
//    float centerX = windowWidth / 2.0f;
//
//    sf::RectangleShape titleBox(sf::Vector2f(620, 100));
//    titleBox.setPosition(centerX - 310, 50);
//    titleBox.setFillColor(sf::Color(20, 20, 15, 200));
//    titleBox.setOutlineColor(sf::Color(218, 165, 32));
//    titleBox.setOutlineThickness(4);
//    window.draw(titleBox);
//
//    sf::Text title("CHESS MASTER", font, 60);
//    title.setFillColor(sf::Color(218, 165, 32));
//    title.setStyle(sf::Text::Bold);
//    title.setPosition(centerX - title.getGlobalBounds().width / 2, 70);
//    window.draw(title);
//
//    sf::CircleShape leftDot1(8);
//    leftDot1.setFillColor(sf::Color(218, 165, 32));
//    leftDot1.setPosition(centerX - 330, 92);
//    window.draw(leftDot1);
//
//    sf::CircleShape rightDot1(8);
//    rightDot1.setFillColor(sf::Color(218, 165, 32));
//    rightDot1.setPosition(centerX + 314, 92);
//    window.draw(rightDot1);
//
//    sf::CircleShape leftDot2(6);
//    leftDot2.setFillColor(sf::Color(160, 130, 70));
//    leftDot2.setPosition(centerX - 320, 118);
//    window.draw(leftDot2);
//
//    sf::CircleShape rightDot2(6);
//    rightDot2.setFillColor(sf::Color(160, 130, 70));
//    rightDot2.setPosition(centerX + 314, 118);
//    window.draw(rightDot2);
//
//    sf::Text subtitle("Choose your game mode", font, 20);
//    subtitle.setFillColor(sf::Color(218, 165, 32));
//    subtitle.setStyle(sf::Text::Italic);
//    subtitle.setPosition(centerX - subtitle.getGlobalBounds().width / 2, 165);
//    window.draw(subtitle);
//
//    std::vector<std::string> options = {
//        "PLAYER VS PLAYER",
//        "PLAYER VS AI (EASY)",
//        "PLAYER VS AI (MEDIUM)",
//        "PLAYER VS AI (HARD)",
//        "INSTRUCTIONS"
//    };
//
//    for (int i = 0; i < options.size(); i++) {
//        float btnY = 210 + i * 62;
//
//        sf::RectangleShape btn(sf::Vector2f(320, 52));
//        btn.setPosition(centerX - 160, btnY);
//        btn.setFillColor(sf::Color(40, 30, 20, 220));
//        btn.setOutlineColor(sf::Color(218, 165, 32));
//        btn.setOutlineThickness(2);
//        window.draw(btn);
//
//        sf::Text text(options[i], font, 24);
//        text.setFillColor(sf::Color(240, 240, 240));
//        text.setStyle(sf::Text::Bold);
//        text.setPosition(centerX - text.getGlobalBounds().width / 2, btnY + 13);
//        window.draw(text);
//    }
//}
//
//void ChessGame::drawInstructions(sf::RenderWindow& window, sf::Font& font) {
//    if (backgroundTex.getSize().x > 0) {
//        sf::Sprite bgSprite(backgroundTex);
//        float scaleX = windowWidth / backgroundTex.getSize().x;
//        float scaleY = windowHeight / backgroundTex.getSize().y;
//        float scale = std::max(scaleX, scaleY);
//        bgSprite.setScale(scale, scale);
//        float offsetX = (windowWidth - backgroundTex.getSize().x * scale) / 2;
//        float offsetY = (windowHeight - backgroundTex.getSize().y * scale) / 2;
//        bgSprite.setPosition(offsetX, offsetY);
//        window.draw(bgSprite);
//
//        sf::RectangleShape overlay(sf::Vector2f(windowWidth, windowHeight));
//        overlay.setFillColor(sf::Color(0, 0, 0, 180));
//        window.draw(overlay);
//    }
//    else {
//        sf::RectangleShape bg(sf::Vector2f(windowWidth, windowHeight));
//        bg.setFillColor(sf::Color(30, 20, 15));
//        window.draw(bg);
//    }
//
//    sf::RectangleShape mainPanel(sf::Vector2f(800, 620));
//    mainPanel.setPosition(windowWidth / 2 - 400, windowHeight / 2 - 310);
//    mainPanel.setFillColor(sf::Color(25, 18, 12, 240));
//    mainPanel.setOutlineColor(sf::Color(218, 165, 32));
//    mainPanel.setOutlineThickness(4);
//    window.draw(mainPanel);
//
//    sf::Text title("HOW TO PLAY", font, 56);
//    title.setFillColor(sf::Color(255, 215, 0));
//    title.setStyle(sf::Text::Bold);
//    title.setPosition(windowWidth / 2 - title.getGlobalBounds().width / 2, windowHeight / 2 - 270);
//    window.draw(title);
//
//    std::vector<std::string> instructions = {
//        "Click on a piece to select it",
//        "Click on highlighted square to move",
//        "Drag and drop pieces to move",
//        "",
//        "Press H to toggle hints",
//        "Press U to undo move",
//        "",
//        "10 minute timer for each player",
//        "Choose AI difficulty or play with a friend"
//    };
//
//    float startY = windowHeight / 2 - 180;
//    int actualLine = 0;
//
//    for (int i = 0; i < instructions.size(); i++) {
//        if (instructions[i] == "") {
//            sf::RectangleShape divider(sf::Vector2f(660, 2));
//            divider.setPosition(windowWidth / 2 - 330, startY + actualLine * 42 + 18);
//            divider.setFillColor(sf::Color(218, 165, 32, 120));
//            window.draw(divider);
//            actualLine++;
//            continue;
//        }
//
//        sf::CircleShape bullet(5);
//        bullet.setFillColor(sf::Color(218, 165, 32));
//        bullet.setPosition(windowWidth / 2 - 330, startY + actualLine * 42 + 5);
//        window.draw(bullet);
//
//        sf::Text text(instructions[i], font, 22);
//        text.setFillColor(sf::Color(240, 240, 240));
//        text.setPosition(windowWidth / 2 - 310, startY + actualLine * 42);
//        window.draw(text);
//        actualLine++;
//    }
//
//    sf::RectangleShape backBtn(sf::Vector2f(280, 60));
//    backBtn.setPosition(windowWidth / 2 - 140, windowHeight / 2 + 220);
//    backBtn.setFillColor(sf::Color(40, 26, 13));
//    backBtn.setOutlineColor(sf::Color(218, 165, 32));
//    backBtn.setOutlineThickness(3);
//    window.draw(backBtn);
//
//    sf::Text backText("BACK TO MENU", font, 26);
//    backText.setFillColor(sf::Color(255, 255, 255));
//    backText.setStyle(sf::Text::Bold);
//    backText.setPosition(windowWidth / 2 - backText.getGlobalBounds().width / 2, windowHeight / 2 + 233);
//    window.draw(backText);
//}
//
//void ChessGame::drawGameOver(sf::RenderWindow& window, sf::Font& font) {
//    sf::RectangleShape fullOverlay(sf::Vector2f(windowWidth, windowHeight));
//    fullOverlay.setFillColor(sf::Color(0, 0, 0, 180));
//    window.draw(fullOverlay);
//
//    sf::RectangleShape bg(sf::Vector2f(580, 380));
//    bg.setPosition(windowWidth / 2 - 290, windowHeight / 2 - 190);
//    bg.setFillColor(sf::Color(40, 30, 20));
//    bg.setOutlineColor(sf::Color(210, 180, 140));
//    bg.setOutlineThickness(5);
//    window.draw(bg);
//
//    std::string message;
//    if (winner == NONE) {
//        message = "STALEMATE!";
//    }
//    else if (winner == WHITE) {
//        message = "WHITE WINS!";
//    }
//    else {
//        message = "BLACK WINS!";
//    }
//
//    sf::Text title(message, font, 52);
//    title.setFillColor(sf::Color::White);
//    title.setStyle(sf::Text::Bold);
//    title.setPosition(windowWidth / 2 - title.getGlobalBounds().width / 2, windowHeight / 2 - 110);
//    window.draw(title);
//
//    sf::Text subtext(winner == NONE ? "DRAW" : "CHECKMATE", font, 32);
//    subtext.setFillColor(sf::Color(210, 180, 140));
//    subtext.setPosition(windowWidth / 2 - subtext.getGlobalBounds().width / 2, windowHeight / 2 - 45);
//    window.draw(subtext);
//
//    sf::RectangleShape menuBtn(sf::Vector2f(280, 75));
//    menuBtn.setPosition(windowWidth / 2 - 140, windowHeight / 2 + 40);
//    menuBtn.setFillColor(sf::Color(101, 67, 33));
//    menuBtn.setOutlineColor(sf::Color(210, 180, 140));
//    menuBtn.setOutlineThickness(3);
//    window.draw(menuBtn);
//
//    sf::Text menuText("MAIN MENU", font, 36);
//    menuText.setFillColor(sf::Color::White);
//    menuText.setStyle(sf::Text::Bold);
//    menuText.setPosition(windowWidth / 2 - menuText.getGlobalBounds().width / 2, windowHeight / 2 + 57);
//    window.draw(menuText);
//}
//
//void ChessGame::drawPromotionMenu(sf::RenderWindow& window, sf::Font& font) {
//    sf::RectangleShape overlay(sf::Vector2f(windowWidth, windowHeight));
//    overlay.setFillColor(sf::Color(0, 0, 0, 200));
//    window.draw(overlay);
//
//    sf::RectangleShape bg(sf::Vector2f(380, 340));
//    bg.setPosition(windowWidth / 2 - 190, windowHeight / 2 - 170);
//    bg.setFillColor(sf::Color(40, 30, 20));
//    bg.setOutlineColor(sf::Color(210, 180, 140));
//    bg.setOutlineThickness(4);
//    window.draw(bg);
//
//    sf::Text title("Promote Pawn To:", font, 32);
//    title.setFillColor(sf::Color::White);
//    title.setStyle(sf::Text::Bold);
//    title.setPosition(windowWidth / 2 - title.getGlobalBounds().width / 2, windowHeight / 2 - 135);
//    window.draw(title);
//
//    std::vector<std::string> pieces = { "Queen", "Rook", "Bishop", "Knight" };
//    for (int i = 0; i < 4; i++) {
//        sf::RectangleShape btn(sf::Vector2f(330, 52));
//        btn.setPosition(windowWidth / 2 - 165, windowHeight / 2 - 65 + i * 68);
//        btn.setFillColor(sf::Color(101, 67, 33));
//        btn.setOutlineColor(sf::Color(210, 180, 140));
//        btn.setOutlineThickness(2);
//        window.draw(btn);
//
//        sf::Text text(pieces[i], font, 28);
//        text.setFillColor(sf::Color::White);
//        text.setStyle(sf::Text::Bold);
//        text.setPosition(windowWidth / 2 - text.getGlobalBounds().width / 2, windowHeight / 2 - 56 + i * 68);
//        window.draw(text);
//    }
//}
////chess draw 4
//#include "ChessGame.h"
//
//void ChessGame::render(sf::RenderWindow& window, sf::Font& font, sf::Vector2i mousePos) {
//    window.clear();
//
//    if (gameState == MENU) {
//        drawMenu(window, font);
//    }
//    else if (gameState == INSTRUCTIONS) {
//        drawInstructions(window, font);
//    }
//    else if (gameState == PLAYING) {
//        sf::RectangleShape bg(sf::Vector2f(windowWidth, windowHeight));
//        bg.setFillColor(sf::Color(60, 45, 35));
//        window.draw(bg);
//
//        drawBoard(window);
//        drawBoardLabels(window, font);
//        drawHighlights(window);
//        drawPieces(window, mousePos);
//        drawGameUI(window, font);
//
//        if (isPromoting) {
//            drawPromotionMenu(window, font);
//        }
//    }
//    else if (gameState == GAME_OVER) {
//        sf::RectangleShape bg(sf::Vector2f(windowWidth, windowHeight));
//        bg.setFillColor(sf::Color(60, 45, 35));
//        window.draw(bg);
//
//        drawBoard(window);
//        drawBoardLabels(window, font);
//        drawPieces(window, mousePos);
//        drawGameOver(window, font);
//    }
//
//    window.display();
//}
//
//void ChessGame::handleMousePress(sf::Vector2i mousePos) {
//    if (gameState == MENU) {
//        float centerX = windowWidth / 2.0f;
//        for (int i = 0; i < 5; i++) {
//            float btnY = 210 + i * 62;
//            if (mousePos.x >= centerX - 160 && mousePos.x <= centerX + 160 &&
//                mousePos.y >= btnY && mousePos.y <= btnY + 52) {
//                if (i == 0) {
//                    gameMode = PVP;
//                    gameState = PLAYING;
//                }
//                else if (i == 1) {
//                    gameMode = PVE_EASY;
//                    gameState = PLAYING;
//                }
//                else if (i == 2) {
//                    gameMode = PVE_MEDIUM;
//                    gameState = PLAYING;
//                }
//                else if (i == 3) {
//                    gameMode = PVE_HARD;
//                    gameState = PLAYING;
//                }
//                else if (i == 4) {
//                    gameState = INSTRUCTIONS;
//                }
//                break;
//            }
//        }
//    }
//    else if (gameState == INSTRUCTIONS) {
//        if (mousePos.x >= windowWidth / 2 - 140 && mousePos.x <= windowWidth / 2 + 140 &&
//            mousePos.y >= windowHeight / 2 + 220 && mousePos.y <= windowHeight / 2 + 280) {
//            gameState = MENU;
//        }
//    }
//    else if (gameState == PLAYING && !isPromoting) {
//        float leftX = 30;
//        float forfeitY = boardOffsetY + 430;
//
//        if (mousePos.x >= leftX && mousePos.x <= leftX + 140 &&
//            mousePos.y >= forfeitY && mousePos.y <= forfeitY + 50) {
//            gameOver = true;
//            winner = (currentPlayer == WHITE) ? BLACK : WHITE;
//            gameState = GAME_OVER;
//            return;
//        }
//
//        std::pair<int, int> pos = getBoardPosition(mousePos);
//        if (pos.first != -1) {
//            int row = pos.first;
//            int col = pos.second;
//
//            if (isPieceSelected) {
//                bool isValidTarget = false;
//                for (auto& move : validMoves) {
//                    if (move.first == row && move.second == col) {
//                        isValidTarget = true;
//                        break;
//                    }
//                }
//
//                if (isValidTarget) {
//                    makeMove(selectedRow, selectedCol, row, col);
//                    isPieceSelected = false;
//                    selectedRow = -1;
//                    selectedCol = -1;
//                    validMoves.clear();
//                    isDragging = false;
//                }
//                else {
//                    Piece* piece = gameBoard->getPiece(row, col);
//                    if (piece && piece->getColor() == currentPlayer) {
//                        selectedRow = row;
//                        selectedCol = col;
//                        calculateValidMoves(row, col);
//                        isDragging = true;
//                        float cellX = boardOffsetX + col * cellSize;
//                        float cellY = boardOffsetY + row * cellSize;
//                        dragOffset = sf::Vector2f((float)mousePos.x - cellX, (float)mousePos.y - cellY);
//                    }
//                    else {
//                        isPieceSelected = false;
//                        selectedRow = -1;
//                        selectedCol = -1;
//                        validMoves.clear();
//                        isDragging = false;
//                    }
//                }
//            }
//            else {
//                Piece* piece = gameBoard->getPiece(row, col);
//                if (piece && piece->getColor() == currentPlayer) {
//                    isPieceSelected = true;
//                    selectedRow = row;
//                    selectedCol = col;
//                    float cellX = boardOffsetX + col * cellSize;
//                    float cellY = boardOffsetY + row * cellSize;
//                    dragOffset = sf::Vector2f((float)mousePos.x - cellX, (float)mousePos.y - cellY);
//                    calculateValidMoves(row, col);
//                    isDragging = true;
//                }
//            }
//        }
//    }
//    else if (gameState == PLAYING && isPromoting) {
//        if (mousePos.x >= windowWidth / 2 - 165 && mousePos.x <= windowWidth / 2 + 165) {
//            Piece* newPiece = nullptr;
//            if (mousePos.y >= windowHeight / 2 - 65 && mousePos.y < windowHeight / 2 + 3) {
//                newPiece = new Queen(currentPlayer == WHITE ? BLACK : WHITE);
//            }
//            else if (mousePos.y >= windowHeight / 2 + 3 && mousePos.y < windowHeight / 2 + 71) {
//                newPiece = new Rook(currentPlayer == WHITE ? BLACK : WHITE);
//            }
//            else if (mousePos.y >= windowHeight / 2 + 71 && mousePos.y < windowHeight / 2 + 139) {
//                newPiece = new Bishop(currentPlayer == WHITE ? BLACK : WHITE);
//            }
//            else if (mousePos.y >= windowHeight / 2 + 139 && mousePos.y < windowHeight / 2 + 207) {
//                newPiece = new Knight(currentPlayer == WHITE ? BLACK : WHITE);
//            }
//
//            if (newPiece) {
//                delete gameBoard->getPiece(promoteRow, promoteCol);
//                gameBoard->setPiece(promoteRow, promoteCol, newPiece);
//                newPiece->setTexture(getPieceTexture(newPiece));
//                newPiece->setHasMoved(true);
//                isPromoting = false;
//                checkGameEnd();
//            }
//        }
//    }
//    else if (gameState == GAME_OVER) {
//        if (mousePos.x >= windowWidth / 2 - 140 && mousePos.x <= windowWidth / 2 + 140 &&
//            mousePos.y >= windowHeight / 2 + 40 && mousePos.y <= windowHeight / 2 + 115) {
//            resetGame();
//            gameState = MENU;
//        }
//    }
//}
//
//void ChessGame::handleMouseRelease(sf::Vector2i mousePos) {
//    if (isDragging && gameState == PLAYING && !isPromoting && isPieceSelected) {
//        std::pair<int, int> pos = getBoardPosition(mousePos);
//        if (pos.first != -1) {
//            int toRow = pos.first;
//            int toCol = pos.second;
//            bool isValidTarget = false;
//            for (auto& move : validMoves) {
//                if (move.first == toRow && move.second == toCol) {
//                    isValidTarget = true;
//                    break;
//                }
//            }
//            if (isValidTarget) {
//                makeMove(selectedRow, selectedCol, toRow, toCol);
//                isPieceSelected = false;
//                selectedRow = -1;
//                selectedCol = -1;
//                validMoves.clear();
//                isDragging = false;
//                return;
//            }
//        }
//        isDragging = false;
//    }
//}
////main
//#include <SFML/Graphics.hpp>
//#include "ChessGame.h"
//
//int main() {
//    sf::RenderWindow window(sf::VideoMode(1200, 800), "Chess Game", sf::Style::Default);
//    window.setFramerateLimit(60);
//
//    sf::Font font;
//    if (!font.loadFromFile("C:/Windows/Fonts/times.ttf")) {
//        return -1;
//    }
//
//    ChessGame game;
//
//    while (window.isOpen()) {
//        sf::Event event;
//        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
//
//        while (window.pollEvent(event)) {
//            if (event.type == sf::Event::Closed) {
//                window.close();
//            }
//
//            if (event.type == sf::Event::Resized) {
//                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
//                window.setView(sf::View(visibleArea));
//                game.resize(event.size.width, event.size.height);
//            }
//
//            if (event.type == sf::Event::MouseButtonPressed) {
//                if (event.mouseButton.button == sf::Mouse::Left) {
//                    game.handleMousePress(mousePos);
//                }
//            }
//
//            if (event.type == sf::Event::MouseButtonReleased) {
//                if (event.mouseButton.button == sf::Mouse::Left) {
//                    game.handleMouseRelease(mousePos);
//                }
//            }
//
//            if (event.type == sf::Event::KeyPressed) {
//                game.handleKeyPress(event.key.code);
//            }
//        }
//
//        game.update();
//        game.render(window, font, mousePos);
//    }
//
//    return 0;
//}