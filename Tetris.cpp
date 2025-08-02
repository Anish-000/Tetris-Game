#include "Tetris.h"
#include <conio.h>     // For _kbhit() and _getch()
#include <windows.h>   // For Sleep()
#include <cstdlib>     // For rand()
#include <ctime>       // For seeding rand()
#include <iostream>

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
const int CONSOLE_WIDTH = 120;
const int CONSOLE_HEIGHT = 50;

enum Color {
    DEFAULT = 7,
    BLOCK = 11,
    BORDER = 8,
    SCORE = 14,
    GAME_OVER = 12
};

TetrisGame::TetrisGame() {
    std::cout << "Initializing TetrisGame...\n";
    srand(static_cast<unsigned>(time(0))); // Seed RNG
    currentPiece = nullptr;
    isGameOver = false;
    score = 0;

    std::cout << "Before spawnPiece()...\n";
    spawnPiece();
    std::cout << "After spawnPiece()...\n";

    std::cout << "TetrisGame initialized.\n";
}

void TetrisGame::run() {
    while (!isGameOver) {
        drawFrame();
        handleInput();
        moveDown();          // Automatic drop every frame
        Sleep(300);          // Delay for game speed (adjust as needed)
    }

    // Game Over
    SetConsoleTextAttribute(hConsole, GAME_OVER);
    system("cls");
    std::cout << "\n\n\t GAME OVER!\n";
    std::cout << "\t Your Score: " << score << "\n\n";
    SetConsoleTextAttribute(hConsole, DEFAULT);
}

// Spawns a new random Tetromino
void TetrisGame::spawnPiece() {
    int randomType = rand() % 7;
    currentPiece = new Tetromino(randomType);
    currentPiece->x = 3;
    currentPiece->y = 0;

    if (board.checkCollision(*currentPiece)) {
        isGameOver = true;
    }
}

// Handles user input
void TetrisGame::handleInput() {
    if (_kbhit()) {
        char ch = _getch();

        Tetromino temp = *currentPiece; // For testing movement

        switch (ch) {
        case 'a': // Move left
            temp.x--;
            if (!board.checkCollision(temp)) currentPiece->x--;
            break;

        case 'd': // Move right
            temp.x++;
            if (!board.checkCollision(temp)) currentPiece->x++;
            break;

        case 's': // Soft drop
            temp.y++;
            if (!board.checkCollision(temp)) currentPiece->y++;
            else moveDown(); // Force lock if can't move further
            break;

        case 'w': // Rotate
            currentPiece->rotateClockWise();
            if (board.checkCollision(*currentPiece)) {
                currentPiece->rotateCounterClockWise(); // Undo if invalid
            }
            break;

        case ' ': // Hard drop
            while (!board.checkCollision(*currentPiece)) {
                currentPiece->y++;
            }
            currentPiece->y--; // Step back to valid position
            moveDown();
            break;
        }
    }
}

// Moves the piece down; locks it if it hits bottom or another block
void TetrisGame::moveDown() {
    Tetromino temp = *currentPiece;
    temp.y++;

    if (!board.checkCollision(temp)) {
        currentPiece->y++;
    } else {
        mergeAndClear(); // Lock piece and clear lines
        spawnPiece();    // Next piece
    }
}

// Locks current piece into the board and clears lines
void TetrisGame::mergeAndClear() {
    board.lockPiece(*currentPiece);
    int lines = board.clearLines();
    score += lines * 100;
    delete currentPiece; // Free old piece
}

// Renders the frame (board + current piece)
void TetrisGame::drawFrame() {
    int boardWidth = GameBoard::WIDTH;
    int boardHeight = GameBoard::HEIGHT;

    int horizontalPadding = (CONSOLE_WIDTH - (boardWidth * 2 + 4)) / 2;  // 2 chars per block + borders
    int verticalPadding = (CONSOLE_HEIGHT - boardHeight) / 2;

    // Clear console
    static HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD topLeft = { 0, 0 };
    SetConsoleCursorPosition(hStdout, topLeft);

    // Copy board to tempGrid
    int tempGrid[GameBoard::HEIGHT][GameBoard::WIDTH];
    for (int i = 0; i < GameBoard::HEIGHT; ++i)
        for (int j = 0; j < GameBoard::WIDTH; ++j)
            tempGrid[i][j] = board.grid[i][j];

    // Overlay current piece
    for (int i = 0; i < Tetromino::size; ++i) {
        for (int j = 0; j < Tetromino::size; ++j) {
            if (currentPiece->shape[i][j]) {
                int x = currentPiece->x + j;
                int y = currentPiece->y + i;
                if (x >= 0 && x < GameBoard::WIDTH && y >= 0 && y < GameBoard::HEIGHT) {
                    tempGrid[y][x] = 2; // Different marker for active piece
                }
            }
        }
    }

    // Vertical padding
    for (int i = 0; i < verticalPadding; ++i)
        std::cout << "\n";

    // Print game board with color and horizontal padding
    for (int i = 0; i < GameBoard::HEIGHT; ++i) {
        std::cout << std::string(horizontalPadding, ' ');

        SetConsoleTextAttribute(hConsole, BORDER);
        std::cout << "||";

        for (int j = 0; j < GameBoard::WIDTH; ++j) {
            if (tempGrid[i][j] == 1) {
                SetConsoleTextAttribute(hConsole, BLOCK);
                std::cout << "[]";
            } else if (tempGrid[i][j] == 2) {
                SetConsoleTextAttribute(hConsole, BLOCK + 1); // Active piece color
                std::cout << "[]";
            } else {
                SetConsoleTextAttribute(hConsole, DEFAULT);
                std::cout << "  ";
            }
        }

        SetConsoleTextAttribute(hConsole, BORDER);
        std::cout << "||\n";
    }

    // Bottom border
    std::cout << std::string(horizontalPadding, ' ');
    SetConsoleTextAttribute(hConsole, BORDER);
    std::cout << "++";
    for (int j = 0; j < GameBoard::WIDTH; ++j) std::cout << "--";
    std::cout << "++\n";

    // Score display
    std::cout << std::string(horizontalPadding, ' ');
    SetConsoleTextAttribute(hConsole, SCORE);
    std::cout << "Score: " << score << "\n";

    SetConsoleTextAttribute(hConsole, DEFAULT);
}