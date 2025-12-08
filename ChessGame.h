#pragma once
#ifndef CHESSGAME_H
#define CHESSGAME_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <limits>

enum PieceType { EMPTY, PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING };
enum Color { NONE, WHITE, BLACK };
enum GameState { MENU, INSTRUCTIONS, PLAYING, GAME_OVER };
enum GameMode { PVP, PVE_EASY, PVE_MEDIUM, PVE_HARD };

struct Piece {
    PieceType type;
    Color color;
    bool hasMoved;
    Piece() : type(EMPTY), color(NONE), hasMoved(false) {}
    Piece(PieceType t, Color c) : type(t), color(c), hasMoved(false) {}
};

struct Move {
    int fromRow, fromCol, toRow, toCol;
    Piece capturedPiece;
    bool wasFirstMove;
    Move(int fr, int fc, int tr, int tc) : fromRow(fr), fromCol(fc), toRow(tr), toCol(tc), wasFirstMove(false) {}
};

struct BoardState {
    Piece board[8][8];
    Color currentPlayer;
    Move lastMove;
    BoardState() : lastMove(-1, -1, -1, -1) {}
};

class ChessGame {
private:
    Piece board[8][8];
    Color currentPlayer;
    std::vector<Move> moveHistory;
    bool gameOver;
    Color winner;
    GameState gameState;
    GameMode gameMode;
    sf::Texture whitePawnTex, whiteRookTex, whiteKnightTex, whiteBishopTex, whiteQueenTex, whiteKingTex;
    sf::Texture blackPawnTex, blackRookTex, blackKnightTex, blackBishopTex, blackQueenTex, blackKingTex;
    sf::Texture backgroundTex;
    float cellSize;
    float boardOffsetX;
    float boardOffsetY;
    float windowWidth;
    float windowHeight;
    bool isPieceSelected;
    bool isDragging;
    int selectedRow, selectedCol;
    sf::Vector2f dragOffset;
    std::vector<std::pair<int, int>> validMoves;
    bool isPromoting;
    int promoteRow, promoteCol;
    sf::Clock whiteClock;
    sf::Clock blackClock;
    float whiteTime;
    float blackTime;
    bool timeRunning;
    bool hintsEnabled;
    bool aiThinking;
    int scrollOffset;
    sf::Texture* getPieceTexture(Piece p);
    void initializeBoard();
    void loadTextures();
    void updateLayout(float width, float height);
    void drawBoard(sf::RenderWindow& window);
    void drawBoardLabels(sf::RenderWindow& window, sf::Font& font);
    void drawHighlights(sf::RenderWindow& window);
    void drawPieces(sf::RenderWindow& window, sf::Vector2i mousePos);
    void drawMenu(sf::RenderWindow& window, sf::Font& font);
    void drawInstructions(sf::RenderWindow& window, sf::Font& font);
    void drawGameOver(sf::RenderWindow& window, sf::Font& font);
    void drawGameUI(sf::RenderWindow& window, sf::Font& font);
    void drawPromotionMenu(sf::RenderWindow& window, sf::Font& font);
    void drawCompactTimer(sf::RenderWindow& window, sf::Font& font);
    void drawMoveHistory(sf::RenderWindow& window, sf::Font& font);
    void drawControls(sf::RenderWindow& window, sf::Font& font);
    std::pair<int, int> getBoardPosition(sf::Vector2i mousePos);
    void calculateValidMoves(int row, int col);
    void checkGameEnd();
    bool isValidMove(int fromRow, int fromCol, int toRow, int toCol);
    bool isValidPawnMove(int fromRow, int fromCol, int toRow, int toCol, Color color);
    bool isValidRookMove(int fromRow, int fromCol, int toRow, int toCol);
    bool isValidKnightMove(int fromRow, int fromCol, int toRow, int toCol);
    bool isValidBishopMove(int fromRow, int fromCol, int toRow, int toCol);
    bool isValidKingMove(int fromRow, int fromCol, int toRow, int toCol);
    bool isValidQueenMove(int fromRow, int fromCol, int toRow, int toCol);
    bool isPathClear(int fromRow, int fromCol, int toRow, int toCol);
    bool isSquareAttacked(int row, int col, Color defenderColor);
    bool isInCheck(Color color);
    bool isCheckmate(Color color);
    bool isStalemate(Color color);
    bool hasLegalMove(Color color);
    void updateTimer();
    void undoMove();
    std::string getMoveNotation(const Move& move);
    int evaluateBoard();
    int minimax(int depth, int alpha, int beta, bool maximizing);
    Move getBestMove(int depth);
    void makeAIMove();

public:
    ChessGame();
    void handleMousePress(sf::Vector2i mousePos);
    void handleMouseRelease(sf::Vector2i mousePos);
    void handleKeyPress(sf::Keyboard::Key key);
    void handleMouseScroll(float delta, sf::Vector2i mousePos);
    bool makeMove(int fromRow, int fromCol, int toRow, int toCol);
    void resetGame();
    void render(sf::RenderWindow& window, sf::Font& font, sf::Vector2i mousePos);
    void resize(float width, float height);
    GameState getGameState();
    void update();
};

#endif