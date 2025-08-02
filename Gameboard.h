# ifndef GAMEBOARD_H
# define GAMEBOARD_H

# include "Tetromino.h"

class GameBoard{
    public:
        static const int WIDTH = 10;
        static const int HEIGHT = 20;

        int grid[HEIGHT][WIDTH];

        GameBoard();

        bool checkCollision(const Tetromino & t);
        void lockPiece(const Tetromino & t);

        int clearLines();
        void print();

    private :
        bool isLineFull(int row);
        void removeLine(int row);
};

# endif