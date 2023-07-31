//
// Created by lior on 12/29/22.
//

#ifndef HW4_ROBOTS_GAME_H
#define HW4_ROBOTS_GAME_H

#include <iostream>
#include <vector>
using namespace std;
#include "Robot.h"
#include "Map.h"


class Game {
    // two maps
    Map m_map1;
    Map m_map2;
    // dynamic array (vector) of robots
    vector<Robot> m_robots;

public:
    // constructor - initialize maps
    Game(int map1[7][7], int map2[7][7]) : m_map1(Map(map1)), m_map2(Map(map2)) {};
    // start game: the function that runs the game
    void startGame();
    // static function that prints menu
    static void printMenu();
    // case 1 - add robot to game
    bool addRobot(int mapnum, int x, int y);
    // case 2 - delete robot from game
    void deleteRobot(int rob_serial);
    // case 3 - move robot
    void moveRobot(int rob_serial, char dir);
    // case 4 - operator + in the game
    void opAdd();
    // case 5 -operator += in the game
    void opAddEq(int mapToOverride);
    // case 6 - operator = in the game
    void opEq(int mapToOverride);
    // case 8 - print map and its robots
    void printMap(int mapnum);
    // destructor
    ~Game();
};


#endif //HW4_ROBOTS_GAME_H
