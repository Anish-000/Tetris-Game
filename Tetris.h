#ifndef TETRISGAME_H
#define TETRISGAME_H

#include "Tetromino.h"
#include "Gameboard.h"

class TetrisGame {
public:
    TetrisGame();

    void run(); 

private:
    GameBoard board;
    Tetromino* currentPiece;

    bool isGameOver;
    int score;

    void spawnPiece();
    void handleInput();
    void moveDown();
    void mergeAndClear();
    void drawFrame();

    bool canMove(Tetromino& t, int dx, int dy);
    bool canRotate(Tetromino& t);
};

#endif
