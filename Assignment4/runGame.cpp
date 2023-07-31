//
// Created by lior on 1/1/23.
//

#include "Game.h"

// main program: initialize and starts the game with the start game function that uses all the game class functions
int main() {
    // initialize the input of map 1
    int coordinates1[7][7] = {{1, 0, 0, 0, 0, 0, 0} , {1, 0, 1, 0, 0, 1, 0}, {1, 0, 1, 1, 0, 1, 0}, {0, 0, 0, 1, 1, 1, 0}, {0, 1, 0, 1, 1, 1, 0}, {1, 1, 0, 0, 0, 0, 1}, {1, 0, 0, 1, 1, 0, 1}};
    // initialize the input of map 2
    int coordinates2[7][7] = {{1, 0, 1, 0, 0, 0, 0} , {1, 1, 0, 1, 1, 1, 0}, {0, 0, 0, 0, 0, 1, 1}, {0, 1, 1, 1, 0, 1, 1}, {1, 1, 0, 0, 0, 1, 1}, {1, 1, 0, 1, 1, 1, 1}, {1, 1, 0, 0, 0, 1, 1}};
    // initialize game
    Game game = Game(coordinates1, coordinates2);
    // run the game with start game function
    game.startGame();
    return 0;
}