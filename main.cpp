#include <iostream>
#include "Tetris.h"

int main() {
    std::cout << "Starting game..." << std::endl;

    TetrisGame game;
    std::cout << "Created game object" << std::endl;

    game.run();
    std::cout << "Exited game loop" << std::endl;

    return 0;
}
