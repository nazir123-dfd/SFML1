/*
QUICK CHECKMATE TEST SCENARIOS:

1. FOOL'S MATE (Black wins in 2 moves) - Fastest checkmate in chess:
   White: f2 -> f3 (move pawn)
   Black: e7 -> e5 (move pawn)
   White: g2 -> g4 (move pawn)
   Black: d8 -> h4 (move queen) = CHECKMATE! Black wins!

2. SCHOLAR'S MATE (White wins in 4 moves)://kmkmkdf
   White: e2 -> e4 (pawn)
   Black: e7 -> e5 (pawn)
   White: f1 -> c4 (bishop)
   Black: b8 -> c6 (knight)
   White: d1 -> h5 (queen)
   Black: g8 -> f6 (knight)
   White: h5 -> f7 (queen captures pawn) = CHECKMATE! White wins!

Test these to verify checkmate detection is working!
*/

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

enum PieceType { EMPTY, PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING };
enum Color { NONE, WHITE, BLACK };
enum GameState { MENU, INSTRUCTIONS, PLAYING, GAME_OVER };

struct Piece {
    PieceType type;
    Color color;
    bool hasMoved;

    Piece() : type(EMPTY), color(NONE), hasMoved(false) {}
    Piece(PieceType t, Color c) : type(t), color(c), hasMoved(false) {}
};

struct Move {
    int fromRow, fromCol, toRow, toCol;
    Move(int fr, int fc, int tr, int tc) : fromRow(fr), fromCol(fc), toRow(tr), toCol(tc) {}
};

class ChessGame {
private:
    Piece board[8][8];
    Color currentPlayer;
    vector<Move> moveHistory;
    bool gameOver;
    Color winner;
    GameState gameState;

    // SFML textures
    sf::Texture whitePawnTex, whiteRookTex, whiteKnightTex, whiteBishopTex, whiteQueenTex, whiteKingTex;
    sf::Texture blackPawnTex, blackRookTex, blackKnightTex, blackBishopTex, blackQueenTex, blackKingTex;
    sf::Texture backgroundTex;

    // Board dimensions
    const float CELL_SIZE = 80.0f;
    const float BOARD_OFFSET_X = 100.0f;
    const float BOARD_OFFSET_Y = 50.0f;

    // Selection and drag
    bool isPieceSelected;
    bool isDragging;
    int selectedRow, selectedCol;
    sf::Vector2f dragOffset;

    // Valid moves highlighting
    vector<pair<int, int>> validMoves;

    // Promotion state
    bool isPromoting;
    int promoteRow, promoteCol;

public:
    ChessGame() {
        initializeBoard();
        currentPlayer = WHITE;
        gameOver = false;
        winner = NONE;
        gameState = MENU;
        isPieceSelected = false;
        isDragging = false;
        selectedRow = -1;
        selectedCol = -1;
        isPromoting = false;

        // Load textures
        loadTextures();
    }

    void loadTextures() {
        string basePath = "assets/";

        if (!whitePawnTex.loadFromFile(basePath + "whitepawn.png")) {
            cout << "Error loading whitepawn.png" << endl;
        }
        if (!whiteRookTex.loadFromFile(basePath + "whiterook.png")) {
            cout << "Error loading whiterook.png" << endl;
        }
        if (!whiteKnightTex.loadFromFile(basePath + "whiteknight.png")) {
            cout << "Error loading whiteknight.png" << endl;
        }
        if (!whiteBishopTex.loadFromFile(basePath + "whitebishop.png")) {
            cout << "Error loading whitebishop.png" << endl;
        }
        if (!whiteQueenTex.loadFromFile(basePath + "whitequeen.png")) {
            cout << "Error loading whitequeen.png" << endl;
        }
        if (!whiteKingTex.loadFromFile(basePath + "whiteking.png")) {
            cout << "Error loading whiteking.png" << endl;
        }

        if (!blackPawnTex.loadFromFile(basePath + "blackpawn.png")) {
            cout << "Error loading blackpawn.png" << endl;
        }
        if (!blackRookTex.loadFromFile(basePath + "blackrook.png")) {
            cout << "Error loading blackrook.png" << endl;
        }
        if (!blackKnightTex.loadFromFile(basePath + "blackknight.png")) {
            cout << "Error loading blackknight.png" << endl;
        }
        if (!blackBishopTex.loadFromFile(basePath + "blackbishop.png")) {
            cout << "Error loading blackbishop.png" << endl;
        }
        if (!blackQueenTex.loadFromFile(basePath + "blackqueen.png")) {
            cout << "Error loading blackqueen.png" << endl;
        }
        if (!blackKingTex.loadFromFile(basePath + "blackking.png")) {
            cout << "Error loading blackking.png" << endl;
        }

        if (!backgroundTex.loadFromFile(basePath + "background.jpg")) {
            cout << "Warning: Could not load background.jpg, will use solid color" << endl;//not working for now , would fix later 
        }//???!!!
    }

    sf::Texture* getPieceTexture(Piece p) {
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

    void initializeBoard() {
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

    void drawBoard(sf::RenderWindow& window) {
        sf::Color lightBrown(222, 184, 135);
        sf::Color darkBrown(139, 69, 19);

        // Draw the checkered board
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                sf::RectangleShape cell(sf::Vector2f(CELL_SIZE, CELL_SIZE));
                cell.setPosition(BOARD_OFFSET_X + j * CELL_SIZE, BOARD_OFFSET_Y + i * CELL_SIZE);

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

    void drawBoardLabels(sf::RenderWindow& window, sf::Font& font) {
        // Column labels (a-h) at top and bottom
        for (int i = 0; i < 8; i++) {
            char label = 'a' + i;

            // Top labels
            sf::Text topText(string(1, label), font, 24);
            topText.setFillColor(sf::Color::White);
            topText.setStyle(sf::Text::Bold);
            float xPos = BOARD_OFFSET_X + i * CELL_SIZE + CELL_SIZE / 2 - 8;
            topText.setPosition(xPos, BOARD_OFFSET_Y - 35);
            window.draw(topText);

            // Bottom labels
            sf::Text bottomText(string(1, label), font, 24);
            bottomText.setFillColor(sf::Color::White);
            bottomText.setStyle(sf::Text::Bold);
            bottomText.setPosition(xPos, BOARD_OFFSET_Y + 8 * CELL_SIZE + 10);
            window.draw(bottomText);
        }

        // Row labels (8-1) at left and right
        for (int i = 0; i < 8; i++) {
            char label = '8' - i;

            // Left labels
            sf::Text leftText(string(1, label), font, 24);
            leftText.setFillColor(sf::Color::White);
            leftText.setStyle(sf::Text::Bold);
            float yPos = BOARD_OFFSET_Y + i * CELL_SIZE + CELL_SIZE / 2 - 12;
            leftText.setPosition(BOARD_OFFSET_X - 35, yPos);
            window.draw(leftText);

            // Right labels
            sf::Text rightText(string(1, label), font, 24);
            rightText.setFillColor(sf::Color::White);
            rightText.setStyle(sf::Text::Bold);
            rightText.setPosition(BOARD_OFFSET_X + 8 * CELL_SIZE + 15, yPos);
            window.draw(rightText);
        }
    }

    void drawHighlights(sf::RenderWindow& window) {
        if (!isPieceSelected) return;

        // Highlight selected cell
        sf::RectangleShape selectedHighlight(sf::Vector2f(CELL_SIZE, CELL_SIZE));
        selectedHighlight.setPosition(BOARD_OFFSET_X + selectedCol * CELL_SIZE,
            BOARD_OFFSET_Y + selectedRow * CELL_SIZE);
        selectedHighlight.setFillColor(sf::Color(255, 255, 0, 100));
        window.draw(selectedHighlight);

        // Draw valid moves
        for (auto& move : validMoves) {
            sf::RectangleShape highlight(sf::Vector2f(CELL_SIZE, CELL_SIZE));
            highlight.setPosition(BOARD_OFFSET_X + move.second * CELL_SIZE,
                BOARD_OFFSET_Y + move.first * CELL_SIZE);

            // Check if there's an enemy piece (capture move)
            if (board[move.first][move.second].type != EMPTY) {
                highlight.setFillColor(sf::Color(255, 100, 100, 120)); // Red for capture
            }
            else {
                highlight.setFillColor(sf::Color(100, 255, 100, 120)); // Green for empty
            }

            window.draw(highlight);
        }
    }

    void drawPieces(sf::RenderWindow& window, sf::Vector2i mousePos) {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                // Skip the piece being dragged
                if (isDragging && i == selectedRow && j == selectedCol) continue;

                if (board[i][j].type != EMPTY) {
                    sf::Texture* tex = getPieceTexture(board[i][j]);
                    if (tex) {
                        sf::Sprite sprite(*tex);
                        sprite.setPosition(BOARD_OFFSET_X + j * CELL_SIZE,
                            BOARD_OFFSET_Y + i * CELL_SIZE);

                        // Scale to fit cell
                        float scaleX = CELL_SIZE / tex->getSize().x;
                        float scaleY = CELL_SIZE / tex->getSize().y;
                        sprite.setScale(scaleX, scaleY);

                        window.draw(sprite);
                    }
                }
            }
        }

        // Draw dragged piece
        if (isDragging && selectedRow != -1) {
            sf::Texture* tex = getPieceTexture(board[selectedRow][selectedCol]);
            if (tex) {
                sf::Sprite sprite(*tex);
                sprite.setPosition(mousePos.x - dragOffset.x, mousePos.y - dragOffset.y);

                float scaleX = CELL_SIZE / tex->getSize().x;
                float scaleY = CELL_SIZE / tex->getSize().y;
                sprite.setScale(scaleX, scaleY);

                window.draw(sprite);
            }
        }
    }

    void drawMenu(sf::RenderWindow& window, sf::Font& font) {
        // Background
        if (backgroundTex.getSize().x > 0) {
            sf::Sprite bgSprite(backgroundTex);
            float scaleX = (float)window.getSize().x / backgroundTex.getSize().x;
            float scaleY = (float)window.getSize().y / backgroundTex.getSize().y;
            bgSprite.setScale(scaleX, scaleY);
            window.draw(bgSprite);
        }
        else {
            sf::RectangleShape bg(sf::Vector2f(window.getSize().x, window.getSize().y));
            bg.setFillColor(sf::Color(20, 20, 30));
            window.draw(bg);
        }

        // Semi-transparent overlay
        sf::RectangleShape overlay(sf::Vector2f(window.getSize().x, window.getSize().y));
        overlay.setFillColor(sf::Color(0, 0, 0, 100));
        window.draw(overlay);

        // Title
        sf::Text title("CHESS GAME", font, 70);
        title.setFillColor(sf::Color::White);
        title.setStyle(sf::Text::Bold);
        title.setPosition(window.getSize().x / 2 - title.getGlobalBounds().width / 2, 100);
        window.draw(title);

        // Play button
        sf::RectangleShape playBtn(sf::Vector2f(350, 90));
        playBtn.setPosition(window.getSize().x / 2 - 175, 300);
        playBtn.setFillColor(sf::Color(101, 67, 33));
        playBtn.setOutlineColor(sf::Color(210, 180, 140));
        playBtn.setOutlineThickness(3);
        window.draw(playBtn);

        sf::Text playText("PLAY", font, 45);
        playText.setFillColor(sf::Color::White);
        playText.setStyle(sf::Text::Bold);
        playText.setPosition(window.getSize().x / 2 - playText.getGlobalBounds().width / 2, 315);
        window.draw(playText);

        // Instructions button
        sf::RectangleShape instrBtn(sf::Vector2f(350, 90));
        instrBtn.setPosition(window.getSize().x / 2 - 175, 420);
        instrBtn.setFillColor(sf::Color(101, 67, 33));
        instrBtn.setOutlineColor(sf::Color(210, 180, 140));
        instrBtn.setOutlineThickness(3);
        window.draw(instrBtn);

        sf::Text instrText("INSTRUCTIONS", font, 45);
        instrText.setFillColor(sf::Color::White);
        instrText.setStyle(sf::Text::Bold);
        instrText.setPosition(window.getSize().x / 2 - instrText.getGlobalBounds().width / 2, 435);
        window.draw(instrText);
    }

    void drawInstructions(sf::RenderWindow& window, sf::Font& font) {
        // Background
        if (backgroundTex.getSize().x > 0) {
            sf::Sprite bgSprite(backgroundTex);
            float scaleX = (float)window.getSize().x / backgroundTex.getSize().x;
            float scaleY = (float)window.getSize().y / backgroundTex.getSize().y;
            bgSprite.setScale(scaleX, scaleY);
            window.draw(bgSprite);
        }
        else {
            sf::RectangleShape bg(sf::Vector2f(window.getSize().x, window.getSize().y));
            bg.setFillColor(sf::Color(20, 20, 30));
            window.draw(bg);
        }

        sf::RectangleShape overlay(sf::Vector2f(window.getSize().x, window.getSize().y));
        overlay.setFillColor(sf::Color(0, 0, 0, 150));
        window.draw(overlay);

        sf::Text title("INSTRUCTIONS", font, 50);
        title.setFillColor(sf::Color::White);
        title.setStyle(sf::Text::Bold);
        title.setPosition(window.getSize().x / 2 - title.getGlobalBounds().width / 2, 50);
        window.draw(title);

        vector<string> instructions = {
            "- Click on a piece to select it",
            "- Valid moves will be highlighted in GREEN",
            "- Capture moves will be highlighted in RED",
            "- Click on a highlighted square to move",
            "- OR drag and drop pieces to move them",
            "- Press FORFEIT button to end game",
            "",
            "Click anywhere to continue..."
        };

        for (int i = 0; i < instructions.size(); i++) {
            sf::Text text(instructions[i], font, 28);
            text.setFillColor(sf::Color::White);
            text.setPosition(100, 150 + i * 50);
            window.draw(text);
        }
    }

    void drawGameOver(sf::RenderWindow& window, sf::Font& font) {
        // Draw semi-transparent overlay first
        sf::RectangleShape fullOverlay(sf::Vector2f(window.getSize().x, window.getSize().y));
        fullOverlay.setFillColor(sf::Color(0, 0, 0, 180));
        window.draw(fullOverlay);

        // Main game over box
        sf::RectangleShape bg(sf::Vector2f(600, 400));
        bg.setPosition(window.getSize().x / 2 - 300, window.getSize().y / 2 - 200);
        bg.setFillColor(sf::Color(40, 30, 20));
        bg.setOutlineColor(sf::Color(210, 180, 140));
        bg.setOutlineThickness(5);
        window.draw(bg);

        string message;
        if (winner == NONE) {
            message = "STALEMATE!";
        }
        else if (winner == WHITE) {
            message = "WHITE WINS!";
        }
        else {
            message = "BLACK WINS!";
        }

        sf::Text title(message, font, 55);
        title.setFillColor(sf::Color::White);
        title.setStyle(sf::Text::Bold);
        title.setPosition(window.getSize().x / 2 - title.getGlobalBounds().width / 2,
            window.getSize().y / 2 - 120);
        window.draw(title);

        sf::Text subtext("CHECKMATE", font, 35);
        if (winner == NONE) {
            subtext.setString("DRAW");
        }
        subtext.setFillColor(sf::Color(210, 180, 140));
        subtext.setPosition(window.getSize().x / 2 - subtext.getGlobalBounds().width / 2,
            window.getSize().y / 2 - 50);
        window.draw(subtext);

        // Menu button (on top of everything)
        sf::RectangleShape menuBtn(sf::Vector2f(300, 80));
        menuBtn.setPosition(window.getSize().x / 2 - 150, window.getSize().y / 2 + 50);
        menuBtn.setFillColor(sf::Color(101, 67, 33));
        menuBtn.setOutlineColor(sf::Color(210, 180, 140));
        menuBtn.setOutlineThickness(3);
        window.draw(menuBtn);

        sf::Text menuText("MAIN MENU", font, 40);
        menuText.setFillColor(sf::Color::White);
        menuText.setStyle(sf::Text::Bold);
        menuText.setPosition(window.getSize().x / 2 - menuText.getGlobalBounds().width / 2,
            window.getSize().y / 2 + 70);
        window.draw(menuText);
    }

    void drawGameUI(sf::RenderWindow& window, sf::Font& font) {
        // Current player indicator
        sf::Text playerText(currentPlayer == WHITE ? "White's Turn" : "Black's Turn", font, 30);
        playerText.setFillColor(sf::Color::White);
        playerText.setStyle(sf::Text::Bold);
        playerText.setPosition(BOARD_OFFSET_X, BOARD_OFFSET_Y + 8 * CELL_SIZE + 20);
        window.draw(playerText);

        // Check indicator
        if (isInCheck(currentPlayer)) {
            sf::Text checkText("CHECK!", font, 30);
            checkText.setFillColor(sf::Color::Red);
            checkText.setStyle(sf::Text::Bold);
            checkText.setPosition(BOARD_OFFSET_X + 300, BOARD_OFFSET_Y + 8 * CELL_SIZE + 20);
            window.draw(checkText);
        }

        // Forfeit button
        sf::RectangleShape forfeitBtn(sf::Vector2f(150, 50));
        forfeitBtn.setPosition(BOARD_OFFSET_X + 8 * CELL_SIZE + 20, BOARD_OFFSET_Y);
        forfeitBtn.setFillColor(sf::Color(120, 40, 40));
        forfeitBtn.setOutlineColor(sf::Color(200, 100, 100));
        forfeitBtn.setOutlineThickness(2);
        window.draw(forfeitBtn);

        sf::Text forfeitText("FORFEIT", font, 25);
        forfeitText.setFillColor(sf::Color::White);
        forfeitText.setStyle(sf::Text::Bold);
        forfeitText.setPosition(BOARD_OFFSET_X + 8 * CELL_SIZE + 35, BOARD_OFFSET_Y + 12);
        window.draw(forfeitText);
    }

    void drawPromotionMenu(sf::RenderWindow& window, sf::Font& font) {
        // Full screen overlay
        sf::RectangleShape overlay(sf::Vector2f(window.getSize().x, window.getSize().y));
        overlay.setFillColor(sf::Color(0, 0, 0, 200));
        window.draw(overlay);

        sf::RectangleShape bg(sf::Vector2f(400, 350));
        bg.setPosition(window.getSize().x / 2 - 200, window.getSize().y / 2 - 175);
        bg.setFillColor(sf::Color(40, 30, 20));
        bg.setOutlineColor(sf::Color(210, 180, 140));
        bg.setOutlineThickness(4);
        window.draw(bg);

        sf::Text title("Promote Pawn To:", font, 35);
        title.setFillColor(sf::Color::White);
        title.setStyle(sf::Text::Bold);
        title.setPosition(window.getSize().x / 2 - title.getGlobalBounds().width / 2,
            window.getSize().y / 2 - 140);
        window.draw(title);

        vector<string> pieces = { "Queen", "Rook", "Bishop", "Knight" };
        for (int i = 0; i < 4; i++) {
            sf::RectangleShape btn(sf::Vector2f(350, 55));
            btn.setPosition(window.getSize().x / 2 - 175, window.getSize().y / 2 - 70 + i * 70);
            btn.setFillColor(sf::Color(101, 67, 33));
            btn.setOutlineColor(sf::Color(210, 180, 140));
            btn.setOutlineThickness(2);
            window.draw(btn);

            sf::Text text(pieces[i], font, 30);
            text.setFillColor(sf::Color::White);
            text.setStyle(sf::Text::Bold);
            text.setPosition(window.getSize().x / 2 - text.getGlobalBounds().width / 2,
                window.getSize().y / 2 - 60 + i * 70);
            window.draw(text);
        }
    }

    pair<int, int> getBoardPosition(sf::Vector2i mousePos) {
        int col = (mousePos.x - BOARD_OFFSET_X) / CELL_SIZE;
        int row = (mousePos.y - BOARD_OFFSET_Y) / CELL_SIZE;

        if (row >= 0 && row < 8 && col >= 0 && col < 8) {
            return make_pair(row, col);
        }
        return make_pair(-1, -1);
    }

    void calculateValidMoves(int row, int col) {
        validMoves.clear();

        if (board[row][col].color != currentPlayer) return;

        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (i == row && j == col) continue;

                if (isValidMove(row, col, i, j)) {
                    // Check if move leaves king in check
                    Piece tempPiece = board[i][j];
                    Piece tempFrom = board[row][col];
                    board[i][j] = board[row][col];
                    board[row][col] = Piece();

                    bool inCheck = isInCheck(currentPlayer);

                    board[row][col] = tempFrom;
                    board[i][j] = tempPiece;

                    if (!inCheck) {
                        validMoves.push_back(make_pair(i, j));
                    }
                }
            }
        }
    }

    void handleMousePress(sf::Vector2i mousePos) {
        if (gameState == MENU) {
            // Check play button
            if (mousePos.x >= 1000 / 2 - 175 && mousePos.x <= 1000 / 2 + 175 &&
                mousePos.y >= 300 && mousePos.y <= 390) {
                gameState = PLAYING;
            }
            // Check instructions button
            else if (mousePos.x >= 1000 / 2 - 175 && mousePos.x <= 1000 / 2 + 175 &&
                mousePos.y >= 420 && mousePos.y <= 510) {
                gameState = INSTRUCTIONS;
            }
        }
        else if (gameState == INSTRUCTIONS) {
            gameState = MENU;
        }
        else if (gameState == PLAYING && !isPromoting) {
            // Check forfeit button
            if (mousePos.x >= BOARD_OFFSET_X + 8 * CELL_SIZE + 20 &&
                mousePos.x <= BOARD_OFFSET_X + 8 * CELL_SIZE + 170 &&
                mousePos.y >= BOARD_OFFSET_Y && mousePos.y <= BOARD_OFFSET_Y + 50) {
                gameOver = true;
                winner = (currentPlayer == WHITE) ? BLACK : WHITE;
                gameState = GAME_OVER;
                return;
            }

            pair<int, int> pos = getBoardPosition(mousePos);
            if (pos.first != -1) {
                int row = pos.first;
                int col = pos.second;

                // If a piece is already selected
                if (isPieceSelected) {
                    // Check if clicking on a valid move
                    bool isValidTarget = false;
                    for (auto& move : validMoves) {
                        if (move.first == row && move.second == col) {
                            isValidTarget = true;
                            break;
                        }
                    }

                    if (isValidTarget) {
                        // Make the move
                        makeMove(selectedRow, selectedCol, row, col);
                        isPieceSelected = false;
                        selectedRow = -1;
                        selectedCol = -1;
                        validMoves.clear();
                        isDragging = false;
                    }
                    else if (board[row][col].type != EMPTY && board[row][col].color == currentPlayer) {
                        // Select a different piece
                        selectedRow = row;
                        selectedCol = col;
                        calculateValidMoves(row, col);
                        isDragging = true;

                        float cellX = BOARD_OFFSET_X + col * CELL_SIZE;
                        float cellY = BOARD_OFFSET_Y + row * CELL_SIZE;
                        dragOffset = sf::Vector2f(mousePos.x - cellX, mousePos.y - cellY);
                    }
                    else {
                        // Deselect
                        isPieceSelected = false;
                        selectedRow = -1;
                        selectedCol = -1;
                        validMoves.clear();
                        isDragging = false;
                    }
                }
                else {
                    // Select a piece
                    if (board[row][col].type != EMPTY && board[row][col].color == currentPlayer) {
                        isPieceSelected = true;
                        selectedRow = row;
                        selectedCol = col;

                        float cellX = BOARD_OFFSET_X + col * CELL_SIZE;
                        float cellY = BOARD_OFFSET_Y + row * CELL_SIZE;
                        dragOffset = sf::Vector2f(mousePos.x - cellX, mousePos.y - cellY);

                        calculateValidMoves(row, col);
                        isDragging = true;
                    }
                }
            }
        }
        else if (gameState == PLAYING && isPromoting) {
            // Check promotion buttons
            int centerX = 1000 / 2;
            int centerY = 800 / 2;

            if (mousePos.x >= centerX - 175 && mousePos.x <= centerX + 175) {
                if (mousePos.y >= centerY - 70 && mousePos.y < centerY) {
                    board[promoteRow][promoteCol].type = QUEEN;
                    isPromoting = false;
                    checkGameEnd();
                }
                else if (mousePos.y >= centerY && mousePos.y < centerY + 70) {
                    board[promoteRow][promoteCol].type = ROOK;
                    isPromoting = false;
                    checkGameEnd();
                }
                else if (mousePos.y >= centerY + 70 && mousePos.y < centerY + 140) {
                    board[promoteRow][promoteCol].type = BISHOP;
                    isPromoting = false;
                    checkGameEnd();
                }
                else if (mousePos.y >= centerY + 140 && mousePos.y < centerY + 210) {
                    board[promoteRow][promoteCol].type = KNIGHT;
                    isPromoting = false;
                    checkGameEnd();
                }
            }
        }
        else if (gameState == GAME_OVER) {
            // Check menu button - larger clickable area
            int centerX = 1000 / 2;
            int centerY = 800 / 2;
            if (mousePos.x >= centerX - 150 && mousePos.x <= centerX + 150 &&
                mousePos.y >= centerY + 50 && mousePos.y <= centerY + 130) {
                resetGame();
                gameState = MENU;
            }
        }
    }

    void handleMouseRelease(sf::Vector2i mousePos) {
        if (isDragging && gameState == PLAYING && !isPromoting && isPieceSelected) {
            pair<int, int> pos = getBoardPosition(mousePos);

            if (pos.first != -1) {
                int toRow = pos.first;
                int toCol = pos.second;

                // Check if it's a valid move
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

            // If not a valid drop, just stop dragging but keep selection
            isDragging = false;
        }
    }

    void checkGameEnd() {
        // Check if current player is in check
        bool inCheck = isInCheck(currentPlayer);

        // Check if current player has any legal moves
        bool hasLegal = hasLegalMove(currentPlayer);

        if (!hasLegal) {
            gameOver = true;
            if (inCheck) {
                // Checkmate - current player loses, other player wins
                winner = (currentPlayer == WHITE) ? BLACK : WHITE;
                cout << "CHECKMATE! " << (winner == WHITE ? "White" : "Black") << " wins!" << endl;
            }
            else {
                // Stalemate - draw
                winner = NONE;
                cout << "STALEMATE! Game is a draw!" << endl;
            }
            gameState = GAME_OVER;
        }
    }

    bool makeMove(int fromRow, int fromCol, int toRow, int toCol) {
        if (board[fromRow][fromCol].color != currentPlayer) {
            return false;
        }

        if (board[toRow][toCol].color == currentPlayer) {
            return false;
        }

        if (!isValidMove(fromRow, fromCol, toRow, toCol)) {
            return false;
        }

        Piece tempPiece = board[toRow][toCol];
        board[toRow][toCol] = board[fromRow][fromCol];
        board[fromRow][fromCol] = Piece();

        if (isInCheck(currentPlayer)) {
            board[fromRow][fromCol] = board[toRow][toCol];
            board[toRow][toCol] = tempPiece;
            return false;
        }

        board[toRow][toCol].hasMoved = true;

        if (board[toRow][toCol].type == PAWN) {
            if ((currentPlayer == WHITE && toRow == 0) || (currentPlayer == BLACK && toRow == 7)) {
                isPromoting = true;
                promoteRow = toRow;
                promoteCol = toCol;
            }
        }

        moveHistory.push_back(Move(fromRow, fromCol, toRow, toCol));

        currentPlayer = (currentPlayer == WHITE) ? BLACK : WHITE;

        if (!isPromoting) {
            checkGameEnd();
        }

        return true;
    }

    bool isValidMove(int fromRow, int fromCol, int toRow, int toCol) {
        Piece piece = board[fromRow][fromCol];

        switch (piece.type) {
        case PAWN:
            return isValidPawnMove(fromRow, fromCol, toRow, toCol, piece.color);
        case ROOK:
            return isValidRookMove(fromRow, fromCol, toRow, toCol);
        case KNIGHT:
            return isValidKnightMove(fromRow, fromCol, toRow, toCol);
        case BISHOP:
            return isValidBishopMove(fromRow, fromCol, toRow, toCol);
        case QUEEN:
            return isValidQueenMove(fromRow, fromCol, toRow, toCol);
        case KING:
            return isValidKingMove(fromRow, fromCol, toRow, toCol);
        default:
            return false;
        }
    }

    bool isValidPawnMove(int fromRow, int fromCol, int toRow, int toCol, Color color) {
        int direction = (color == WHITE) ? -1 : 1;
        int startRow = (color == WHITE) ? 6 : 1;

        if (toCol == fromCol) {
            if (toRow == fromRow + direction && board[toRow][toCol].type == EMPTY) {
                return true;
            }
            if (fromRow == startRow && toRow == fromRow + 2 * direction &&
                board[fromRow + direction][fromCol].type == EMPTY &&
                board[toRow][toCol].type == EMPTY) {
                return true;
            }
        }

        if (abs(toCol - fromCol) == 1 && toRow == fromRow + direction) {
            if (board[toRow][toCol].type != EMPTY && board[toRow][toCol].color != color) {
                return true;
            }
        }

        return false;
    }

    bool isValidRookMove(int fromRow, int fromCol, int toRow, int toCol) {
        if (fromRow != toRow && fromCol != toCol) return false;

        return isPathClear(fromRow, fromCol, toRow, toCol);
    }

    bool isValidKnightMove(int fromRow, int fromCol, int toRow, int toCol) {
        int rowDiff = abs(toRow - fromRow);
        int colDiff = abs(toCol - fromCol);

        return (rowDiff == 2 && colDiff == 1) || (rowDiff == 1 && colDiff == 2);
    }

    bool isValidBishopMove(int fromRow, int fromCol, int toRow, int toCol) {
        if (abs(toRow - fromRow) != abs(toCol - fromCol)) return false;

        return isPathClear(fromRow, fromCol, toRow, toCol);
    }

    bool isValidQueenMove(int fromRow, int fromCol, int toRow, int toCol) {
        return isValidRookMove(fromRow, fromCol, toRow, toCol) ||
            isValidBishopMove(fromRow, fromCol, toRow, toCol);
    }

    bool isValidKingMove(int fromRow, int fromCol, int toRow, int toCol) {
        int rowDiff = abs(toRow - fromRow);
        int colDiff = abs(toCol - fromCol);

        if (rowDiff <= 1 && colDiff <= 1) {
            return true;
        }

        if (!board[fromRow][fromCol].hasMoved && rowDiff == 0 && colDiff == 2) {
            if (toCol > fromCol) {
                if (board[fromRow][7].type == ROOK && !board[fromRow][7].hasMoved) {
                    if (board[fromRow][5].type == EMPTY && board[fromRow][6].type == EMPTY) {
                        if (!isSquareAttacked(fromRow, 4, currentPlayer) &&
                            !isSquareAttacked(fromRow, 5, currentPlayer) &&
                            !isSquareAttacked(fromRow, 6, currentPlayer)) {
                            board[fromRow][5] = board[fromRow][7];
                            board[fromRow][7] = Piece();
                            return true;
                        }
                    }
                }
            }
            else {
                if (board[fromRow][0].type == ROOK && !board[fromRow][0].hasMoved) {
                    if (board[fromRow][1].type == EMPTY &&
                        board[fromRow][2].type == EMPTY &&
                        board[fromRow][3].type == EMPTY) {
                        if (!isSquareAttacked(fromRow, 4, currentPlayer) &&
                            !isSquareAttacked(fromRow, 3, currentPlayer) &&
                            !isSquareAttacked(fromRow, 2, currentPlayer)) {
                            board[fromRow][3] = board[fromRow][0];
                            board[fromRow][0] = Piece();
                            return true;
                        }
                    }
                }
            }
        }

        return false;
    }

    bool isPathClear(int fromRow, int fromCol, int toRow, int toCol) {
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

    bool isSquareAttacked(int row, int col, Color defenderColor) {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (board[i][j].color != NONE && board[i][j].color != defenderColor) {
                    if (board[i][j].type == KING) {
                        if (abs(i - row) <= 1 && abs(j - col) <= 1) {
                            return true;
                        }
                    }
                    else if (isValidMove(i, j, row, col)) {
                        return true;
                    }
                }
            }
        }
        return false;
    }

    bool isInCheck(Color color) {
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

    bool isCheckmate(Color color) {
        if (!isInCheck(color)) return false;

        return !hasLegalMove(color);
    }

    bool isStalemate(Color color) {
        if (isInCheck(color)) return false;

        return !hasLegalMove(color);
    }

    bool hasLegalMove(Color color) {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (board[i][j].color == color) {
                    for (int ti = 0; ti < 8; ti++) {
                        for (int tj = 0; tj < 8; tj++) {
                            if (board[ti][tj].color == color) continue;

                            if (isValidMove(i, j, ti, tj)) {
                                Piece tempPiece = board[ti][tj];
                                board[ti][tj] = board[i][j];
                                board[i][j] = Piece();

                                bool stillCheck = isInCheck(color);

                                board[i][j] = board[ti][tj];
                                board[ti][tj] = tempPiece;

                                if (!stillCheck) return true;
                            }
                        }
                    }
                }
            }
        }
        return false;
    }

    void resetGame() {
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
    }

    void render(sf::RenderWindow& window, sf::Font& font, sf::Vector2i mousePos) {
        window.clear();

        if (gameState == MENU) {
            drawMenu(window, font);
        }
        else if (gameState == INSTRUCTIONS) {
            drawInstructions(window, font);
        }
        else if (gameState == PLAYING) {
            // Brown background for gameplay
            sf::RectangleShape bg(sf::Vector2f(window.getSize().x, window.getSize().y));
            bg.setFillColor(sf::Color(90, 60, 40)); // Medium brown
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
            // Brown background for game over screen
            sf::RectangleShape bg(sf::Vector2f(window.getSize().x, window.getSize().y));
            bg.setFillColor(sf::Color(90, 60, 40)); // Medium brown
            window.draw(bg);

            drawBoard(window);
            drawBoardLabels(window, font);
            drawPieces(window, mousePos);
            drawGameOver(window, font);
        }

        window.display();
    }

    GameState getGameState() { return gameState; }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(1000, 800), "Chess Game");
    window.setFramerateLimit(60);

    sf::Font font;
    if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
        cout << "Error loading font!" << endl;
        return -1;
    }

    ChessGame game;

    while (window.isOpen()) {
        sf::Event event;
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    game.handleMousePress(mousePos);
                }
            }

            if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    game.handleMouseRelease(mousePos);
                }
            }
        }

        game.render(window, font, mousePos);
    }

    return 0;
}