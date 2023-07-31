//
// Created by lior on 12/29/22.
//

#ifndef HW4_ROBOTS_ROBOT_H
#define HW4_ROBOTS_ROBOT_H

#include <iostream>
using namespace std;

class Robot {
    int m_maptype;
    int m_x;
    int m_y;
    int m_serial;
public:
    // static number that represents the number of robots created
    static int numofRobots;
    // constructor
    Robot(int maptype, int x, int y);
    // destructor
    ~Robot();
    // operator <<
    friend ostream& operator<<(ostream &out, const Robot& robot);
    // game can use private variables of class
    friend class Game;
};


#endif //HW4_ROBOTS_ROBOT_H
