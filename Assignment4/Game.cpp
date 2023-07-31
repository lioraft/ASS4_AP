//
// Created by lior on 12/29/22.
//

#include "Game.h"

// a function that prints out the menu.
void Game::printMenu() {
    cout << "Robot Control Menu" << endl;
    cout << "1. Add Robot" << endl;
    cout << "2. Delete Robot" << endl;
    cout << "3. Move Robot" << endl;
    cout << "4. Operator +" << endl;
    cout << "5. Operator +=" << endl;
    cout << "6. Operator =" << endl;
    cout << "7. Operator ==" << endl;
    cout << "8. Operator <<" << endl;
    cout << "9. Quit" << endl;
    cout << "Input your option:" << endl;
}

// function takes in map number and coordinates from user, and adds robot to map.
// if can't add, print invalid location error message.
bool Game::addRobot(int mapnum, int x, int y) {
    // setting pointer to current robot map
    Map *map;
    if (mapnum == 1) {
        map = &m_map1;
    } else {
        map = &m_map2;
    }
    // check location is valid in the specified map
    // if indexes are out of range or if there is wall in current location
    if (!map->canMove(x, y) || map->outOfReach(x,y)) {
        cout << "Invalid location" << endl;
        return false;
    }
    // if can create robot, create and add to vector of robots
    Robot cur_rob = Robot(mapnum, x, y);
    m_robots.push_back(cur_rob);
    return true;
}

// function takes in the serial number of a robot, and deletes it from vector of robots
void Game::deleteRobot(int rob_serial) {
    // create iterator to go through all robots
    auto iter = m_robots.begin();
    // loop until reaches end of robots vector. when finds robot, delete it
    while (iter != m_robots.end()) {
        if (iter->m_serial == rob_serial) {
            // print confirmation message of robot deletion
            std::cout << "Robot deleted: " << iter->m_serial << " MAP: " << iter->m_maptype << " GPS: " << iter->m_x << "," << iter->m_y << std::endl;
            iter = m_robots.erase(iter);
        }
        else
            iter++;
    }
}

// function that takes in robot serial number and direction, and moves the robot to these coordinates if possible. if not, move robot
// to coordinates (-1,-1) and stop communicating with robot.
void Game::moveRobot(int rob_serial, char dir) {
    // create iterator to go through all robots and find robot
    auto iter = m_robots.begin();
    while (iter != m_robots.end()) {
        if (iter->m_serial == rob_serial)
            break;
        else
            iter++;
    }
    // if robot is out of reach, return and do nothing
    if (iter->m_x == -1 || iter->m_y == -1)
        return;
    // if can reach robot, try to move
    int mapnum = iter->m_maptype;
    // setting pointer to current robot map
    Map *map;
    if (mapnum == 1) {
        map = &m_map1;
    } else {
        map = &m_map2;
    }
    // if needs to move right and can move, move it
    if (dir == 'R') {
        if (map->outOfReach(iter->m_x + 1, iter->m_y)) {
            iter->m_x = -1;
            iter->m_y = -1;
            return;
        }
        if (map->canMove(iter->m_x + 1, iter->m_y)) {
            iter->m_x = iter->m_x + 1;
            cout << *iter;
            return;
        }
        cout << *iter;
        return;
    }
    // if needs to move left and can move, move it
    if (dir == 'L') {
        if (map->outOfReach(iter->m_x - 1, iter->m_y)) {
            iter->m_x = -1;
            iter->m_y = -1;
            return;
        }
        if (map->canMove(iter->m_x - 1, iter->m_y)) {
            iter->m_x = iter->m_x - 1;
            cout << *iter;
            return;
        }
        cout << *iter;
        return;
    }
    // if needs to move up and can move, move it
    if (dir == 'U') {
        if (map->outOfReach(iter->m_x, iter->m_y + 1)) {
            iter->m_x = -1;
            iter->m_y = -1;
            return;
        }
        if (map->canMove(iter->m_x, iter->m_y + 1)) {
            iter->m_y = iter->m_y + 1;
            cout << *iter;
            return;
        }
        cout << *iter;
        return;
    }
    // if needs to move down and can move, move it
    if (dir == 'D') {
        if (map->outOfReach(iter->m_x, iter->m_y - 1)) {
            iter->m_x = -1;
            iter->m_y = -1;
            return;
        }
        if (map->canMove(iter->m_x, iter->m_y - 1)) {
            iter->m_y = iter->m_y - 1;
            cout << *iter;
            return;
        }
        cout << *iter;
        return;
    }
}

// operator + of the maps: it adds the maps, and prints the result. if can "transfer" robots, it prints them.
void Game::opAdd() {
    // calculating the sum map of the two maps
    Map sumMap = m_map1+m_map2;
    // print map
    cout << sumMap << endl;
    // create iterator to go through all robots and find robots that can be "transfered" to sum map
    auto iter = m_robots.begin();
    while (iter != m_robots.end()) {
        // if can transfer, print
        if (sumMap.canMove(iter->m_x, iter->m_y) && !sumMap.outOfReach(iter->m_x, iter->m_y))
            cout << "Robot: " << iter->m_serial << " GPS: " << iter->m_x << "," << iter->m_y << endl;
        iter++;
    }
}

// operator += of the maps: it adds the maps to specified map. if cant "transfer" robots to new result map, it deletes them.
void Game::opAddEq(int mapToOverride) {
    Map *map;
    // calculating the sum map of the two maps and setting pointer to override map
    if (mapToOverride == 1) {
        m_map1+=m_map2;
        map = &m_map1;
    }
    else {
        m_map2+=m_map1;
        map = &m_map2;
    }
    // create iterator to go through all robots and find robots that needs to be deleted
    auto iter = m_robots.begin();
    while (iter != m_robots.end()) {
        // if cant transfer, delete robot
        if (iter->m_maptype == mapToOverride && !map->canMove(iter->m_x, iter->m_y))
            iter = m_robots.erase(iter);
        else {
            iter++;
        }
    }
}

// Operator = : a function that takes in the number of map to override, and adds the walls of the other map to it. if some of the robots
// are in a location that now is a wall, they will be deleted.
void Game::opEq(int mapToOverride) {
    Map *map;
    // override map with = operator and set pointer to map
    if (mapToOverride == 1) {
        m_map1=m_map2;
        map = &m_map1;
    }
    else {
        m_map2=m_map1;
        map = &m_map2;
    }
    // create iterator to go through all robots and find robots that needs to be deleted
    auto iter = m_robots.begin();
    while (iter != m_robots.end()) {
        // if cant transfer, delete robot
        if (iter->m_maptype == mapToOverride && !map->canMove(iter->m_x, iter->m_y))
            iter = m_robots.erase(iter);
        else
            iter++;
    }
}

// print map: function that takes in the number of the map in the game, and prints the map and its robots
void Game::printMap(int mapnum) {
    // setting pointer to current map
    Map *map;
    if (mapnum == 1) {
        map = &m_map1;
    } else {
        map = &m_map2;
    }
    // print map
    cout << *map;
    // create iterator to go through all robots and find robots that needs to be printed
    auto iter = m_robots.begin();
    while (iter != m_robots.end()) {
        // if robot is in reach, print it
        if (iter->m_maptype == mapnum && !map->outOfReach(iter->m_x, iter->m_y) && map->canMove(iter->m_x, iter->m_y))
            cout << *iter;
        iter++;
    }
}

// function that runs the game with switch case, by using the functions of the class.
void Game::startGame() {
        int input = 0;
        string inputstr;
        // while loop until user chooses to exit
        while (input != 9) {
            this->printMenu();
            cin >> inputstr;
            // if invalid input, print message and repeat loop. else, cast input to int and proceed to switch case
            if (inputstr.length() != 1) {
                input = 0;
            } else {
                if (isdigit(inputstr[0]))
                    input = stoi(inputstr);
                else {
                    input = 0;
                }
            }
            switch (input) {
                case 1: { // Add Robot
                    // take input of map number
                    cout << "Enter MAP number: " << endl;
                    int mapnum;
                    cin >> mapnum;
                    // take input of coordinates
                    cout << "Enter Coordinates (X,Y): " << endl;
                    int x, y;
                    cin >> x;
                    cin >> y;
                    this->addRobot(mapnum, x, y);
                    break;
                }
                case 2: { // Delete Robot
                    // take input of robot number
                    cout << "Enter Robot number: " << endl;
                    int rob_serial;
                    cin >> rob_serial;
                    this->deleteRobot(rob_serial);
                    break;
                }
                case 3: { // Move Robot
                    // take input of robot number
                    cout << "Enter Robot number: " << endl;
                    int rob_serial;
                    cin >> rob_serial;
                    // take input of direction
                    cout << "Enter direction: " << endl;
                    char dir;
                    cin >> dir;
                    this->moveRobot(rob_serial, dir);
                    break;
                }
                case 4: { // Operator +
                    this->opAdd();
                    break;
                }
                case 5: { // Operator +=
                    // take input of map to override number
                    cout << "Override MAP number: " << endl;
                    int mapnum;
                    cin >> mapnum;
                    if (mapnum != 1 && mapnum != 2) {
                        cout << "Invalid MAP number" << endl;
                    }
                    else {
                        this->opAddEq(mapnum);
                    }
                    break;
                }
                case 6: { // Operator =
                    // take input of map to override number
                    cout << "Override MAP number: " << endl;
                    int mapnum;
                    cin >> mapnum;
                    if (mapnum != 1 && mapnum != 2) {
                        cout << "Invalid MAP number" << endl;
                    }
                    else {
                        this->opEq(mapnum);
                    }
                    break;
                }
                case 7: { // Operator ==
                    if (m_map1 == m_map2) {
                        cout << "TRUE" << endl;
                    }
                    else
                        cout << "FALSE" << endl;
                    break;
                }
                case 8: { // Operator <<
                    // take input of map to override number
                    cout << "Please enter MAP number: " << endl;
                    int mapnum;
                    cin >> mapnum;
                    if (mapnum != 1 && mapnum != 2) {
                        cout << "Invalid MAP number" << endl;
                    }
                    else {
                        this->printMap(mapnum);
                    }
                    break;
                }
                case 9: // exit
                    break;
                default: {
                    cout << "Invalid input" << endl;
                    break;
                }
            }
        }
}

// default destructor - objects destroy themselves
Game::~Game() = default;