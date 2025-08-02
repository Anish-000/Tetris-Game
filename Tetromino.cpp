# include "Tetromino.h"

const int Tetromino :: shapes[7][Tetromino :: size][Tetromino :: size] = {
    // I-Shape
    {
        {0, 0, 0, 0},
        {1, 1, 1, 1},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },
    // O-Shape
    {
        {0, 0, 0, 0},
        {0, 1, 1, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0}
    },
    // T-Shape
    {
        {0, 0, 0, 0},
        {1, 1, 1, 0},
        {0, 1, 0, 0},
        {0, 0, 0, 0}
    },
    // L-Shape
    {
        {0, 1, 0, 0},
        {0, 1, 0, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0}
    },
    // J-Shape
    {
        {0, 0, 1, 0},
        {0, 0, 1, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0}
    },
    // S-Shape
    {
        {0, 1, 1, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },
    // Z-Shape
    {
        {1, 1, 0, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    }

};

Tetromino :: Tetromino(int t){
    type = t;
    x = 3;
    y = 0;
    copyShape(shapes[type]);
}

void Tetromino :: rotateClockWise(){
    int temp[size][size];
    for (int i = 0; i < size; ++i){
        for (int j = 0; j < size; ++j){
            temp[j][size - i - 1] = shape[i][j];
        }
    }

    for( int i = 0; i < size; ++i ){
        for( int j = 0; j < size; ++j ){
            shape[i][j] = temp[i][j];
        }
    }
}

void Tetromino :: rotateCounterClockWise(){
    int temp[size][size];
    for (int i = 0; i < size; ++i){
        for (int j = 0; j < size; ++j){
            temp[size - 1 - j][i] = shape[i][j];
        }
    }

    for( int i = 0; i < size; ++i ){
        for( int j = 0; j < size; ++j ){
            shape[i][j] = temp[i][j];
        }
    }
}

void Tetromino :: copyShape(const int source[size][size]){
    for (int i = 0; i < size; ++i){
        for (int j = 0; j < size; ++j){
            shape[i][j] = source[i][j];
        }
    }
}