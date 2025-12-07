#include "ChessGame.h"

void ChessGame::drawBoard(sf::RenderWindow& window) {
    sf::Color lightBrown(222, 184, 135);
    sf::Color darkBrown(139, 69, 19);

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
    int fontSize = std::max(12, (int)(cellSize * 0.25f));

    for (int i = 0; i < 8; i++) {
        char label = 'a' + i;
        sf::Text topText(std::string(1, label), font, fontSize);
        topText.setFillColor(sf::Color::White);
        topText.setStyle(sf::Text::Bold);
        float xPos = boardOffsetX + i * cellSize + cellSize / 2 - fontSize / 3;
        topText.setPosition(xPos, boardOffsetY - fontSize - 10);
        window.draw(topText);

        sf::Text bottomText(std::string(1, label), font, fontSize);
        bottomText.setFillColor(sf::Color::White);
        bottomText.setStyle(sf::Text::Bold);
        bottomText.setPosition(xPos, boardOffsetY + 8 * cellSize + 5);
        window.draw(bottomText);
    }

    for (int i = 0; i < 8; i++) {
        char label = '8' - i;
        sf::Text leftText(std::string(1, label), font, fontSize);
        leftText.setFillColor(sf::Color::White);
        leftText.setStyle(sf::Text::Bold);
        float yPos = boardOffsetY + i * cellSize + cellSize / 2 - fontSize / 2;
        leftText.setPosition(boardOffsetX - fontSize - 15, yPos);
        window.draw(leftText);

        sf::Text rightText(std::string(1, label), font, fontSize);
        rightText.setFillColor(sf::Color::White);
        rightText.setStyle(sf::Text::Bold);
        rightText.setPosition(boardOffsetX + 8 * cellSize + 10, yPos);
        window.draw(rightText);
    }
}

void ChessGame::drawHighlights(sf::RenderWindow& window) {
    if (!isPieceSelected || !hintsEnabled) return;

    sf::RectangleShape selectedHighlight(sf::Vector2f(cellSize, cellSize));
    selectedHighlight.setPosition(boardOffsetX + selectedCol * cellSize, boardOffsetY + selectedRow * cellSize);
    selectedHighlight.setFillColor(sf::Color(255, 255, 0, 100));
    window.draw(selectedHighlight);

    for (auto& move : validMoves) {
        sf::RectangleShape highlight(sf::Vector2f(cellSize, cellSize));
        highlight.setPosition(boardOffsetX + move.second * cellSize, boardOffsetY + move.first * cellSize);
        if (board[move.first][move.second].type != EMPTY) {
            highlight.setFillColor(sf::Color(255, 100, 100, 120));
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
    int fontSize = std::max(20, (int)(cellSize * 0.38f));

    int whiteMin = (int)whiteTime / 60;
    int whiteSec = (int)whiteTime % 60;
    int blackMin = (int)blackTime / 60;
    int blackSec = (int)blackTime % 60;

    std::stringstream wss, bss;
    wss << whiteMin << ":" << (whiteSec < 10 ? "0" : "") << whiteSec;
    bss << blackMin << ":" << (blackSec < 10 ? "0" : "") << blackSec;

    float leftPanelX = boardOffsetX - 220;
    float topY = boardOffsetY + 30;

    static sf::Clock blinkClock;
    bool blink = (blinkClock.getElapsedTime().asMilliseconds() / 500) % 2 == 0;

    sf::RectangleShape whiteTimerBg(sf::Vector2f(190, 100));
    whiteTimerBg.setPosition(leftPanelX, topY);
    whiteTimerBg.setFillColor(sf::Color(245, 245, 245, 250));
    whiteTimerBg.setOutlineColor((currentPlayer == WHITE && blink) ? sf::Color(50, 200, 50) : sf::Color(100, 100, 100));
    whiteTimerBg.setOutlineThickness((currentPlayer == WHITE && blink) ? 5 : 3);
    window.draw(whiteTimerBg);

    sf::RectangleShape whiteStripe(sf::Vector2f(190, 8));
    whiteStripe.setPosition(leftPanelX, topY);
    whiteStripe.setFillColor(sf::Color(218, 165, 32));
    window.draw(whiteStripe);

    sf::Text whiteLabel("WHITE", font, fontSize - 2);
    whiteLabel.setFillColor(sf::Color(40, 40, 40));
    whiteLabel.setStyle(sf::Text::Bold);
    whiteLabel.setPosition(leftPanelX + 15, topY + 20);
    window.draw(whiteLabel);

    sf::Text whiteTimeText(wss.str(), font, fontSize + 4);
    whiteTimeText.setFillColor(currentPlayer == WHITE ? sf::Color(0, 150, 0) : sf::Color(60, 60, 60));
    whiteTimeText.setStyle(sf::Text::Bold);
    whiteTimeText.setPosition(leftPanelX + 15, topY + 55);
    window.draw(whiteTimeText);

    sf::RectangleShape blackTimerBg(sf::Vector2f(190, 100));
    blackTimerBg.setPosition(leftPanelX, topY + 120);
    blackTimerBg.setFillColor(sf::Color(40, 40, 40, 250));
    blackTimerBg.setOutlineColor((currentPlayer == BLACK && blink) ? sf::Color(50, 200, 50) : sf::Color(100, 100, 100));
    blackTimerBg.setOutlineThickness((currentPlayer == BLACK && blink) ? 5 : 3);
    window.draw(blackTimerBg);

    sf::RectangleShape blackStripe(sf::Vector2f(190, 8));
    blackStripe.setPosition(leftPanelX, topY + 120);
    blackStripe.setFillColor(sf::Color(218, 165, 32));
    window.draw(blackStripe);

    sf::Text blackLabel("BLACK", font, fontSize - 2);
    blackLabel.setFillColor(sf::Color(240, 240, 240));
    blackLabel.setStyle(sf::Text::Bold);
    blackLabel.setPosition(leftPanelX + 15, topY + 140);
    window.draw(blackLabel);

    sf::Text blackTimeText(bss.str(), font, fontSize + 4);
    blackTimeText.setFillColor(currentPlayer == BLACK ? sf::Color(100, 255, 100) : sf::Color(200, 200, 200));
    blackTimeText.setStyle(sf::Text::Bold);
    blackTimeText.setPosition(leftPanelX + 15, topY + 175);
    window.draw(blackTimeText);
}

void ChessGame::drawMoveHistory(sf::RenderWindow& window, sf::Font& font) {
    int fontSize = std::max(14, (int)(cellSize * 0.22f));
    float rightX = boardOffsetX + 8 * cellSize + 40;
    float startY = boardOffsetY + 20;

    sf::RectangleShape historyBg(sf::Vector2f(200, 450));
    historyBg.setPosition(rightX, startY);
    historyBg.setFillColor(sf::Color(40, 26, 13, 230));
    historyBg.setOutlineColor(sf::Color(160, 130, 70));
    historyBg.setOutlineThickness(2);
    window.draw(historyBg);

    sf::Text historyTitle("Move History", font, fontSize + 4);
    historyTitle.setFillColor(sf::Color(255, 215, 0));
    historyTitle.setStyle(sf::Text::Bold);
    historyTitle.setPosition(rightX + 10, startY + 10);
    window.draw(historyTitle);

    sf::RectangleShape divider(sf::Vector2f(180, 2));
    divider.setPosition(rightX + 10, startY + 40);
    divider.setFillColor(sf::Color(218, 165, 32));
    window.draw(divider);

    int startIdx = std::max(0, (int)moveHistory.size() - 14);
    for (int i = startIdx; i < moveHistory.size(); i++) {
        std::string notation = getMoveNotation(moveHistory[i]);
        sf::Text moveText(notation, font, fontSize);
        moveText.setFillColor(sf::Color(230, 230, 230));
        moveText.setPosition(rightX + 15, startY + 55 + (i - startIdx) * (fontSize + 10));
        window.draw(moveText);
    }
}

void ChessGame::drawControls(sf::RenderWindow& window, sf::Font& font) {
    int fontSize = std::max(14, (int)(cellSize * 0.22f));
    float leftX = boardOffsetX - 180;
    float startY = boardOffsetY + 250;

    sf::RectangleShape controlsBg(sf::Vector2f(150, 200));
    controlsBg.setPosition(leftX, startY);
    controlsBg.setFillColor(sf::Color(40, 26, 13, 230));
    controlsBg.setOutlineColor(sf::Color(160, 130, 70));
    controlsBg.setOutlineThickness(2);
    window.draw(controlsBg);

    sf::Text controlsTitle("Controls", font, fontSize + 2);
    controlsTitle.setFillColor(sf::Color(255, 215, 0));
    controlsTitle.setStyle(sf::Text::Bold);
    controlsTitle.setPosition(leftX + 10, startY + 10);
    window.draw(controlsTitle);

    sf::RectangleShape divider(sf::Vector2f(130, 2));
    divider.setPosition(leftX + 10, startY + 38);
    divider.setFillColor(sf::Color(218, 165, 32));
    window.draw(divider);

    std::vector<std::string> controls = {
        "U - Undo",
        "H - Hints",
        "ESC - Menu"
    };

    for (int i = 0; i < controls.size(); i++) {
        sf::Text text(controls[i], font, fontSize);
        text.setFillColor(sf::Color(230, 230, 230));
        text.setPosition(leftX + 15, startY + 50 + i * (fontSize + 12));
        window.draw(text);
    }

    if (hintsEnabled) {
        sf::Text hintStatus("Hints: ON", font, fontSize);
        hintStatus.setFillColor(sf::Color(100, 255, 100));
        hintStatus.setStyle(sf::Text::Bold);
        hintStatus.setPosition(leftX + 15, startY + 140);
        window.draw(hintStatus);
    }

    if (isInCheck(currentPlayer)) {
        sf::Text checkText("CHECK!", font, fontSize + 4);
        checkText.setFillColor(sf::Color::Red);
        checkText.setStyle(sf::Text::Bold);
        checkText.setPosition(leftX + 15, startY + 165);
        window.draw(checkText);
    }
}

void ChessGame::drawGameUI(sf::RenderWindow& window, sf::Font& font) {
    drawTimer(window, font);
    drawMoveHistory(window, font);
    drawControls(window, font);

    int fontSize = std::max(16, (int)(cellSize * 0.28f));
    float rightX = boardOffsetX + 8 * cellSize + 40;

    sf::RectangleShape forfeitBtn(sf::Vector2f(200, 60));
    forfeitBtn.setPosition(rightX, boardOffsetY + 490);
    forfeitBtn.setFillColor(sf::Color(120, 40, 40));
    forfeitBtn.setOutlineColor(sf::Color(200, 100, 100));
    forfeitBtn.setOutlineThickness(3);
    window.draw(forfeitBtn);

    sf::Text forfeitText("FORFEIT", font, fontSize + 4);
    forfeitText.setFillColor(sf::Color::White);
    forfeitText.setStyle(sf::Text::Bold);
    forfeitText.setPosition(rightX + 50, boardOffsetY + 505);
    window.draw(forfeitText);
}

void ChessGame::drawMenu(sf::RenderWindow& window, sf::Font& font) {
    if (backgroundTex.getSize().x > 0) {
        sf::Sprite bgSprite(backgroundTex);
        float scaleX = windowWidth / backgroundTex.getSize().x;
        float scaleY = windowHeight / backgroundTex.getSize().y;
        float scale = std::max(scaleX, scaleY);
        bgSprite.setScale(scale, scale);
        float offsetX = (windowWidth - backgroundTex.getSize().x * scale) / 2;
        float offsetY = (windowHeight - backgroundTex.getSize().y * scale) / 2;
        bgSprite.setPosition(offsetX, offsetY);
        window.draw(bgSprite);

        sf::RectangleShape overlay(sf::Vector2f(windowWidth, windowHeight));
        overlay.setFillColor(sf::Color(0, 0, 0, 160));
        window.draw(overlay);
    }
    else {
        sf::RectangleShape bg(sf::Vector2f(windowWidth, windowHeight));
        sf::Color gradientTop(139, 90, 43);
        sf::Color gradientBottom(40, 26, 13);
        bg.setFillColor(gradientBottom);
        window.draw(bg);
    }

    sf::RectangleShape titleOuterBox(sf::Vector2f(750, 140));
    titleOuterBox.setPosition(windowWidth / 2 - 375, 50);
    titleOuterBox.setFillColor(sf::Color(0, 0, 0, 220));
    titleOuterBox.setOutlineColor(sf::Color(218, 165, 32));
    titleOuterBox.setOutlineThickness(5);
    window.draw(titleOuterBox);

    sf::RectangleShape titleInnerBox(sf::Vector2f(730, 120));
    titleInnerBox.setPosition(windowWidth / 2 - 365, 60);
    titleInnerBox.setFillColor(sf::Color(40, 26, 13, 200));
    titleInnerBox.setOutlineColor(sf::Color(160, 130, 70));
    titleInnerBox.setOutlineThickness(2);
    window.draw(titleInnerBox);

    sf::Text title("CHESS MASTER", font, 72);
    title.setFillColor(sf::Color(255, 215, 0));
    title.setStyle(sf::Text::Bold);
    title.setPosition(windowWidth / 2 - title.getGlobalBounds().width / 2, 80);

    sf::Text titleShadow("CHESS MASTER", font, 72);
    titleShadow.setFillColor(sf::Color(0, 0, 0, 150));
    titleShadow.setStyle(sf::Text::Bold);
    titleShadow.setPosition(windowWidth / 2 - titleShadow.getGlobalBounds().width / 2 + 3, 83);
    window.draw(titleShadow);
    window.draw(title);

    sf::Text subtitle("Choose your game mode", font, 24);
    subtitle.setFillColor(sf::Color(218, 165, 32));
    subtitle.setStyle(sf::Text::Italic);
    subtitle.setPosition(windowWidth / 2 - subtitle.getGlobalBounds().width / 2, 210);
    window.draw(subtitle);

    std::vector<std::string> options = { "PLAYER VS PLAYER", "PLAYER VS AI (EASY)", "PLAYER VS AI (MEDIUM)", "PLAYER VS AI (HARD)", "INSTRUCTIONS" };

    for (int i = 0; i < options.size(); i++) {
        float btnY = 260 + i * 82;

        sf::RectangleShape btnShadow(sf::Vector2f(450, 68));
        btnShadow.setPosition(windowWidth / 2 - 222, btnY + 4);
        btnShadow.setFillColor(sf::Color(0, 0, 0, 100));
        window.draw(btnShadow);

        sf::RectangleShape btn(sf::Vector2f(450, 68));
        btn.setPosition(windowWidth / 2 - 225, btnY);
        btn.setFillColor(sf::Color(40, 26, 13, 230));
        btn.setOutlineColor(sf::Color(218, 165, 32));
        btn.setOutlineThickness(3);
        window.draw(btn);

        sf::RectangleShape btnInner(sf::Vector2f(440, 58));
        btnInner.setPosition(windowWidth / 2 - 220, btnY + 5);
        btnInner.setFillColor(sf::Color(60, 40, 20, 180));
        window.draw(btnInner);

        sf::RectangleShape btnGlow(sf::Vector2f(430, 3));
        btnGlow.setPosition(windowWidth / 2 - 215, btnY + 8);
        btnGlow.setFillColor(sf::Color(255, 215, 0, 80));
        window.draw(btnGlow);

        sf::Text text(options[i], font, 30);
        text.setFillColor(sf::Color(255, 255, 255));
        text.setStyle(sf::Text::Bold);
        text.setPosition(windowWidth / 2 - text.getGlobalBounds().width / 2, btnY + 18);
        window.draw(text);
    }

    sf::CircleShape decoration1(8);
    decoration1.setFillColor(sf::Color(218, 165, 32));
    decoration1.setPosition(windowWidth / 2 - 400, 120);
    window.draw(decoration1);

    sf::CircleShape decoration2(8);
    decoration2.setFillColor(sf::Color(218, 165, 32));
    decoration2.setPosition(windowWidth / 2 + 384, 120);
    window.draw(decoration2);

    sf::CircleShape decoration3(6);
    decoration3.setFillColor(sf::Color(160, 130, 70));
    decoration3.setPosition(windowWidth / 2 - 390, 160);
    window.draw(decoration3);

    sf::CircleShape decoration4(6);
    decoration4.setFillColor(sf::Color(160, 130, 70));
    decoration4.setPosition(windowWidth / 2 + 384, 160);
    window.draw(decoration4);
}

void ChessGame::drawInstructions(sf::RenderWindow& window, sf::Font& font) {
    if (backgroundTex.getSize().x > 0) {
        sf::Sprite bgSprite(backgroundTex);
        float scaleX = windowWidth / backgroundTex.getSize().x;
        float scaleY = windowHeight / backgroundTex.getSize().y;
        float scale = std::max(scaleX, scaleY);
        bgSprite.setScale(scale, scale);
        float offsetX = (windowWidth - backgroundTex.getSize().x * scale) / 2;
        float offsetY = (windowHeight - backgroundTex.getSize().y * scale) / 2;
        bgSprite.setPosition(offsetX, offsetY);
        window.draw(bgSprite);

        sf::RectangleShape overlay(sf::Vector2f(windowWidth, windowHeight));
        overlay.setFillColor(sf::Color(0, 0, 0, 180));
        window.draw(overlay);
    }
    else {
        sf::RectangleShape bg(sf::Vector2f(windowWidth, windowHeight));
        bg.setFillColor(sf::Color(30, 20, 15));
        window.draw(bg);
    }

    sf::RectangleShape mainPanel(sf::Vector2f(850, 650));
    mainPanel.setPosition(windowWidth / 2 - 425, windowHeight / 2 - 325);
    mainPanel.setFillColor(sf::Color(20, 15, 10, 240));
    mainPanel.setOutlineColor(sf::Color(218, 165, 32));
    mainPanel.setOutlineThickness(4);
    window.draw(mainPanel);

    sf::Text title("HOW TO PLAY", font, 60);
    title.setFillColor(sf::Color(255, 215, 0));
    title.setStyle(sf::Text::Bold);
    title.setPosition(windowWidth / 2 - title.getGlobalBounds().width / 2, windowHeight / 2 - 285);
    window.draw(title);

    std::vector<std::string> instructions = {
        "Click on a piece to select it",
        "Click on highlighted square to move",
        "Drag and drop pieces to move",
        "",
        "Press H to toggle hints",
        "Press U to undo move",
        "",
        "10 minute timer for each player",
        "Choose AI or play with friend"
    };

    float startY = windowHeight / 2 - 190;
    int actualLine = 0;

    for (int i = 0; i < instructions.size(); i++) {
        if (instructions[i] == "") {
            sf::RectangleShape divider(sf::Vector2f(700, 2));
            divider.setPosition(windowWidth / 2 - 350, startY + actualLine * 45 + 20);
            divider.setFillColor(sf::Color(218, 165, 32, 100));
            window.draw(divider);
            actualLine++;
            continue;
        }

        sf::CircleShape bullet(5);
        bullet.setFillColor(sf::Color(218, 165, 32));
        bullet.setPosition(windowWidth / 2 - 350, startY + actualLine * 45 + 5);
        window.draw(bullet);

        sf::Text text(instructions[i], font, 24);
        text.setFillColor(sf::Color(240, 240, 240));
        text.setPosition(windowWidth / 2 - 330, startY + actualLine * 45);
        window.draw(text);
        actualLine++;
    }

    

    sf::RectangleShape backBtn(sf::Vector2f(300, 65));
    backBtn.setPosition(windowWidth / 2 - 150, windowHeight / 2 + 230);
    backBtn.setFillColor(sf::Color(40, 26, 13));
    backBtn.setOutlineColor(sf::Color(218, 165, 32));
    backBtn.setOutlineThickness(3);
    window.draw(backBtn);

    sf::Text backText("BACK TO MENU", font, 28);
    backText.setFillColor(sf::Color(255, 255, 255));
    backText.setStyle(sf::Text::Bold);
    backText.setPosition(windowWidth / 2 - backText.getGlobalBounds().width / 2, windowHeight / 2 + 243);
    window.draw(backText);
}

void ChessGame::drawGameOver(sf::RenderWindow& window, sf::Font& font) {
    sf::RectangleShape fullOverlay(sf::Vector2f(windowWidth, windowHeight));
    fullOverlay.setFillColor(sf::Color(0, 0, 0, 180));
    window.draw(fullOverlay);

    sf::RectangleShape bg(sf::Vector2f(600, 400));
    bg.setPosition(windowWidth / 2 - 300, windowHeight / 2 - 200);
    bg.setFillColor(sf::Color(40, 30, 20));
    bg.setOutlineColor(sf::Color(210, 180, 140));
    bg.setOutlineThickness(5);
    window.draw(bg);

    std::string message;
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
    title.setPosition(windowWidth / 2 - title.getGlobalBounds().width / 2, windowHeight / 2 - 120);
    window.draw(title);

    sf::Text subtext(winner == NONE ? "DRAW" : "CHECKMATE", font, 35);
    subtext.setFillColor(sf::Color(210, 180, 140));
    subtext.setPosition(windowWidth / 2 - subtext.getGlobalBounds().width / 2, windowHeight / 2 - 50);
    window.draw(subtext);

    sf::RectangleShape menuBtn(sf::Vector2f(300, 80));
    menuBtn.setPosition(windowWidth / 2 - 150, windowHeight / 2 + 50);
    menuBtn.setFillColor(sf::Color(101, 67, 33));
    menuBtn.setOutlineColor(sf::Color(210, 180, 140));
    menuBtn.setOutlineThickness(3);
    window.draw(menuBtn);

    sf::Text menuText("MAIN MENU", font, 40);
    menuText.setFillColor(sf::Color::White);
    menuText.setStyle(sf::Text::Bold);
    menuText.setPosition(windowWidth / 2 - menuText.getGlobalBounds().width / 2, windowHeight / 2 + 70);
    window.draw(menuText);
}

void ChessGame::drawPromotionMenu(sf::RenderWindow& window, sf::Font& font) {
    sf::RectangleShape overlay(sf::Vector2f(windowWidth, windowHeight));
    overlay.setFillColor(sf::Color(0, 0, 0, 200));
    window.draw(overlay);

    sf::RectangleShape bg(sf::Vector2f(400, 350));
    bg.setPosition(windowWidth / 2 - 200, windowHeight / 2 - 175);
    bg.setFillColor(sf::Color(40, 30, 20));
    bg.setOutlineColor(sf::Color(210, 180, 140));
    bg.setOutlineThickness(4);
    window.draw(bg);

    sf::Text title("Promote Pawn To:", font, 35);
    title.setFillColor(sf::Color::White);
    title.setStyle(sf::Text::Bold);
    title.setPosition(windowWidth / 2 - title.getGlobalBounds().width / 2, windowHeight / 2 - 140);
    window.draw(title);

    std::vector<std::string> pieces = { "Queen", "Rook", "Bishop", "Knight" };
    for (int i = 0; i < 4; i++) {
        sf::RectangleShape btn(sf::Vector2f(350, 55));
        btn.setPosition(windowWidth / 2 - 175, windowHeight / 2 - 70 + i * 70);
        btn.setFillColor(sf::Color(101, 67, 33));
        btn.setOutlineColor(sf::Color(210, 180, 140));
        btn.setOutlineThickness(2);
        window.draw(btn);

        sf::Text text(pieces[i], font, 30);
        text.setFillColor(sf::Color::White);
        text.setStyle(sf::Text::Bold);
        text.setPosition(windowWidth / 2 - text.getGlobalBounds().width / 2, windowHeight / 2 - 60 + i * 70);
        window.draw(text);
    }
}

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
        bg.setFillColor(sf::Color(90, 60, 40));
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
        bg.setFillColor(sf::Color(90, 60, 40));
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
        if (mousePos.x >= windowWidth / 2 - 225 && mousePos.x <= windowWidth / 2 + 225) {
            if (mousePos.y >= 260 && mousePos.y <= 328) {
                gameMode = PVP;
                gameState = PLAYING;
            }
            else if (mousePos.y >= 342 && mousePos.y <= 410) {
                gameMode = PVE_EASY;
                gameState = PLAYING;
            }
            else if (mousePos.y >= 424 && mousePos.y <= 492) {
                gameMode = PVE_MEDIUM;
                gameState = PLAYING;
            }
            else if (mousePos.y >= 506 && mousePos.y <= 574) {
                gameMode = PVE_HARD;
                gameState = PLAYING;
            }
            else if (mousePos.y >= 588 && mousePos.y <= 656) {
                gameState = INSTRUCTIONS;
            }
        }
    }
    else if (gameState == INSTRUCTIONS) {
        gameState = MENU;
    }
    else if (gameState == INSTRUCTIONS) {
        if (mousePos.x >= windowWidth / 2 - 150 && mousePos.x <= windowWidth / 2 + 150 &&
            mousePos.y >= windowHeight / 2 + 230 && mousePos.y <= windowHeight / 2 + 295) {
            gameState = MENU;
        }
    }
    else if (gameState == PLAYING && !isPromoting) {
        if (mousePos.x >= boardOffsetX + 8 * cellSize + 20 &&
            mousePos.x <= boardOffsetX + 8 * cellSize + 20 + cellSize * 1.5f &&
            mousePos.y >= boardOffsetY + cellSize * 7 &&
            mousePos.y <= boardOffsetY + cellSize * 7 + cellSize * 0.6f) {
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
                    dragOffset = sf::Vector2f(mousePos.x - cellX, mousePos.y - cellY);
                }
                else {\\coding

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
                    dragOffset = sf::Vector2f(mousePos.x - cellX, mousePos.y - cellY);
                    calculateValidMoves(row, col);
                    isDragging = true;
                }
            }
        }
    }
    else if (gameState == PLAYING && isPromoting) {
        if (mousePos.x >= windowWidth / 2 - 175 && mousePos.x <= windowWidth / 2 + 175) {
            if (mousePos.y >= windowHeight / 2 - 70 && mousePos.y < windowHeight / 2) {
                board[promoteRow][promoteCol].type = QUEEN;
                isPromoting = false;
                checkGameEnd();
            }
            else if (mousePos.y >= windowHeight / 2 && mousePos.y < windowHeight / 2 + 70) {
                board[promoteRow][promoteCol].type = ROOK;
                isPromoting = false;
                checkGameEnd();
            }
            else if (mousePos.y >= windowHeight / 2 + 70 && mousePos.y < windowHeight / 2 + 140) {
                board[promoteRow][promoteCol].type = BISHOP;
                isPromoting = false;
                checkGameEnd();
            }
            else if (mousePos.y >= windowHeight / 2 + 140 && mousePos.y < windowHeight / 2 + 210) {
                board[promoteRow][promoteCol].type = KNIGHT;
                isPromoting = false;
                checkGameEnd();
            }
        }
    }
    else if (gameState == GAME_OVER) {
        if (mousePos.x >= windowWidth / 2 - 150 && mousePos.x <= windowWidth / 2 + 150 &&
            mousePos.y >= windowHeight / 2 + 50 && mousePos.y <= windowHeight / 2 + 130) {
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