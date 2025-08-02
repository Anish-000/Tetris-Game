# ifndef TETROMINO_H
#define TETROMINO_H

class Tetromino{
    public:
    
        static const int size = 4;
        int shape[size][size];
        int x,y;
        int type;

        Tetromino(int type);

        void rotateClockWise();
        void rotateCounterClockWise();

    private :

        void copyShape(const int source[size][size]);
        static const int shapes[7][size][size];
};

# endif
