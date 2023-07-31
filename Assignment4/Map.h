//
// Created by lior on 12/29/22.
//

#ifndef HW4_ROBOTS_MAP_H
#define HW4_ROBOTS_MAP_H

#include <iostream>
using namespace std;


class Map {
    int m_coordinates[7][7]; // nested array that represents map coordinates
public:
    // constructor
    Map(int maparr[7][7]);
    // function to check if current index is a passage
    bool canMove(int x, int y);
    // static function that checks if an index of a robot is out of reach
    bool outOfReach(int x, int y);
    // operator +
    Map operator+(const Map& other)const;
    // operator +=
    Map& operator+=(const Map& other);
    // operator =
    Map& operator=(const Map& other);
    // operator ==
    bool operator ==(const Map& other)const;
    // operator <<
    friend ostream& operator<<(ostream &out, const Map& map);
    // destructor
    ~Map();
};


#endif //HW4_ROBOTS_MAP_H
