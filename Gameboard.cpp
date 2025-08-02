#include "Gameboard.h"
#include <iostream>

// Constructor: initializes the board with zeros
GameBoard::GameBoard() {
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            grid[i][j] = 0;
        }
    }
}

// Check if the Tetromino collides with the board or existing blocks
bool GameBoard::checkCollision(const Tetromino& t) {
    for (int i = 0; i < Tetromino::size; ++i) {
        for (int j = 0; j < Tetromino::size; ++j) {
            if (t.shape[i][j]) {
                int newX = t.x + j;
                int newY = t.y + i;

                // Check out-of-bounds
                if (newX < 0 || newX >= WIDTH || newY < 0 || newY >= HEIGHT)
                    return true;

                // Check existing block collision
                if (grid[newY][newX] != 0)
                    return true;
            }
        }
    }
    return false;
}

// Lock the Tetromino into the board
void GameBoard::lockPiece(const Tetromino& t) {
    for (int i = 0; i < Tetromino::size; ++i) {
        for (int j = 0; j < Tetromino::size; ++j) {
            if (t.shape[i][j]) {
                int newX = t.x + j;
                int newY = t.y + i;

                if (newX >= 0 && newX < WIDTH && newY >= 0 && newY < HEIGHT) {
                    grid[newY][newX] = 1;
                }
            }
        }
    }
}

// Check and clear full lines
int GameBoard::clearLines() {
    int linesCleared = 0;
    for (int i = HEIGHT - 1; i >= 0; --i) {
        if (isLineFull(i)) {
            removeLine(i);
            linesCleared++;
            i++; // re-check same row after shift
        }
    }
    return linesCleared;
}

// Check if a row is full (helper)
bool GameBoard::isLineFull(int row) {
    for (int j = 0; j < WIDTH; ++j) {
        if (grid[row][j] == 0)
            return false;
    }
    return true;
}

// Remove a full row and shift everything down
void GameBoard::removeLine(int row) {
    for (int i = row; i > 0; --i) {
        for (int j = 0; j < WIDTH; ++j) {
            grid[i][j] = grid[i - 1][j];
        }
    }
    // Clear top row
    for (int j = 0; j < WIDTH; ++j) {
        grid[0][j] = 0;
    }
}

// Simple print function for console output
void GameBoard::print() {
    system("cls"); // Clear console (Windows only)

    for (int i = 0; i < HEIGHT; ++i) {
        std::cout << "|";
        for (int j = 0; j < WIDTH; ++j) {
            std::cout << (grid[i][j] ? "#" : " ");
        }
        std::cout << "|\n";
    }

    // Bottom border
    std::cout << "+";
    for (int j = 0; j < WIDTH; ++j) std::cout << "-";
    std::cout << "+\n";
}
