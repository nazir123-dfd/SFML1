#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

using namespace std;

enum PieceType { EMPTY, PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING };
enum Color { NONE, WHITE, BLACK };

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

class ChessBoard {
private:
    Piece board[8][8];
    Color currentPlayer;
    vector<Move> moveHistory;
    bool gameOver;
    Color winner;

public:
    ChessBoard() {
        initializeBoard();
        currentPlayer = WHITE;
        gameOver = false;
        winner = NONE;
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

    void displayBoard() {
        system("cls");
        cout << "\n========================================\n";
        cout << "     CHESS GAME - CONSOLE MODE\n";
        cout << "========================================\n\n";

        cout << "    a   b   c   d   e   f   g   h\n";
        cout << "  +---+---+---+---+---+---+---+---+\n";

        for (int i = 0; i < 8; i++) {
            cout << (8 - i) << " |";
            for (int j = 0; j < 8; j++) {
                cout << " " << getPieceSymbol(board[i][j]) << " |";
            }
            cout << " " << (8 - i) << "\n";
            cout << "  +---+---+---+---+---+---+---+---+\n";
        }

        cout << "    a   b   c   d   e   f   g   h\n\n";

        if (currentPlayer == WHITE) {
            cout << ">>> White's Turn <<<\n";
        }
        else {
            cout << ">>> Black's Turn <<<\n";
        }

        if (isInCheck(currentPlayer)) {
            cout << "*** CHECK! ***\n";
        }

        cout << "\n";
    }

    string getPieceSymbol(Piece p) {
        if (p.type == EMPTY) return " ";

        if (p.color == WHITE) {
            switch (p.type) {
            case PAWN: return "P";
            case ROOK: return "R";
            case KNIGHT: return "N";
            case BISHOP: return "B";
            case QUEEN: return "Q";
            case KING: return "K";
            default: return " ";
            }
        }
        else {
            switch (p.type) {
            case PAWN: return "p";
            case ROOK: return "r";
            case KNIGHT: return "n";
            case BISHOP: return "b";
            case QUEEN: return "q";
            case KING: return "k";
            default: return " ";
            }
        }
    }

    bool makeMove(string from, string to) {
        if (from.length() != 2 || to.length() != 2) return false;

        int fromCol = from[0] - 'a';
        int fromRow = 8 - (from[1] - '0');
        int toCol = to[0] - 'a';
        int toRow = 8 - (to[1] - '0');

        if (fromCol < 0 || fromCol > 7 || fromRow < 0 || fromRow > 7) return false;
        if (toCol < 0 || toCol > 7 || toRow < 0 || toRow > 7) return false;

        if (board[fromRow][fromCol].color != currentPlayer) {
            cout << "Error: Not your piece!\n";
            return false;
        }

        if (board[toRow][toCol].color == currentPlayer) {
            cout << "Error: Cannot capture your own piece!\n";
            return false;
        }

        if (!isValidMove(fromRow, fromCol, toRow, toCol)) {
            cout << "Error: Invalid move for this piece!\n";
            return false;
        }

        Piece tempPiece = board[toRow][toCol];
        board[toRow][toCol] = board[fromRow][fromCol];
        board[fromRow][fromCol] = Piece();

        if (isInCheck(currentPlayer)) {
            board[fromRow][fromCol] = board[toRow][toCol];
            board[toRow][toCol] = tempPiece;
            cout << "Error: King would be in check!\n";
            return false;
        }

        board[toRow][toCol].hasMoved = true;

        if (board[toRow][toCol].type == PAWN) {
            if ((currentPlayer == WHITE && toRow == 0) || (currentPlayer == BLACK && toRow == 7)) {
                promotePawn(toRow, toCol);
            }
        }

        moveHistory.push_back(Move(fromRow, fromCol, toRow, toCol));

        currentPlayer = (currentPlayer == WHITE) ? BLACK : WHITE;

        if (isCheckmate(currentPlayer)) {
            gameOver = true;
            winner = (currentPlayer == WHITE) ? BLACK : WHITE;
        }
        else if (isStalemate(currentPlayer)) {
            gameOver = true;
            winner = NONE;
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

    void promotePawn(int row, int col) {
        cout << "\nPawn Promotion! Choose piece:\n";
        cout << "1. Queen\n";
        cout << "2. Rook\n";
        cout << "3. Bishop\n";
        cout << "4. Knight\n";
        cout << "Choice: ";

        int choice;
        cin >> choice;

        switch (choice) {
        case 1: board[row][col].type = QUEEN; break;
        case 2: board[row][col].type = ROOK; break;
        case 3: board[row][col].type = BISHOP; break;
        case 4: board[row][col].type = KNIGHT; break;
        default: board[row][col].type = QUEEN;
        }
    }

    bool isGameOver() { return gameOver; }

    void displayWinner() {
        if (winner == NONE) {
            cout << "\n========================================\n";
            cout << "      GAME DRAW (Stalemate)\n";
            cout << "========================================\n\n";
        }
        else {
            cout << "\n========================================\n";
            if (winner == WHITE) {
                cout << "      WHITE WINS! CHECKMATE!\n";
            }
            else {
                cout << "      BLACK WINS! CHECKMATE!\n";
            }
            cout << "========================================\n\n";
        }
    }

    void showMoves() {
        if (moveHistory.empty()) {
            cout << "No moves yet.\n";
            return;
        }

        cout << "\nMove History:\n";
        cout << "=============\n";
        for (int i = 0; i < moveHistory.size(); i++) {
            char fromCol = 'a' + moveHistory[i].fromCol;
            char toCol = 'a' + moveHistory[i].toCol;
            int fromRow = 8 - moveHistory[i].fromRow;
            int toRow = 8 - moveHistory[i].toRow;

            cout << (i + 1) << ". " << fromCol << fromRow << " -> " << toCol << toRow << "\n";
        }
        cout << "\n";
    }

    void showHelp() {
        cout << "\n========================================\n";
        cout << "         CHESS PIECE SYMBOLS\n";
        cout << "========================================\n";
        cout << "White: K=King Q=Queen R=Rook B=Bishop N=Knight P=Pawn\n";
        cout << "Black: k=king q=queen r=rook b=bishop n=knight p=pawn\n\n";
        cout << "HOW TO PLAY:\n";
        cout << "- Enter moves as: e2 e4 (from position to position)\n";
        cout << "- Coordinates: columns a-h, rows 1-8\n";
        cout << "- Special moves: Castling, Pawn promotion, En passant\n";
        cout << "\nCOMMANDS:\n";
        cout << "h - Show move history\n";
        cout << "? - Show this help\n";
        cout << "q - Quit game\n";
        cout << "========================================\n\n";
    }
};

int main() {
    ChessBoard game;
    string from, to;

    cout << "\n========================================\n";
    cout << "     WELCOME TO CONSOLE CHESS!\n";
    cout << "========================================\n\n";
    cout << "Type '?' for help\n";
    cout << "Press Enter to start...";
    cin.get();

    while (!game.isGameOver()) {
        game.displayBoard();

        cout << "Enter move (e.g., e2 e4), 'h' for history, '?' for help, 'q' to quit: ";

        cin >> from;

        if (from == "q" || from == "Q") {
            cout << "\nThanks for playing!\n";
            break;
        }

        if (from == "h" || from == "H") {
            game.showMoves();
            cout << "Press Enter to continue...";
            cin.ignore();
            cin.get();
            continue;
        }

        if (from == "?") {
            game.showHelp();
            cout << "Press Enter to continue...";
            cin.ignore();
            cin.get();
            continue;
        }

        cin >> to;

        if (!game.makeMove(from, to)) {
            cout << "Invalid move! Press Enter to try again...";
            cin.ignore();
            cin.get();
        }
    }

    game.displayBoard();
    game.displayWinner();
    game.showMoves();

    cout << "Press Enter to exit...";
    cin.ignore();\\code
    cin.get();

    return 0;
}