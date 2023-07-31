//
// Created by lior on 12/29/22.
//

#include "Robot.h"
#include <iostream>
using namespace std;

// initialize static variable with 0
int Robot::numofRobots = 0;

// constructor: takes in the map type, and coordinates, creates a robot and prints creation message
Robot::Robot(int maptype, int x, int y) {
    // set map number and x,y coordinates
    m_maptype = maptype;
    m_x = x;
    m_y = y;
    // increase number of robots by 1 and set serial number
    numofRobots++;
    m_serial = numofRobots;
    // print confirmation message of robot creation
    std::cout << "New ";
    std::cout << *this;
}

// default destructor
Robot::~Robot() = default;

// operator << :
// function takes in an ostream and a reference to a robot, and prints the robot through the ostream.
ostream& operator<<(ostream& out, const Robot& robot) {
    // print robot information
    std::cout << "Robot: " << robot.m_serial << " MAP: " << robot.m_maptype << " GPS: " << robot.m_x << "," << robot.m_y << std::endl;
    return out;
}
