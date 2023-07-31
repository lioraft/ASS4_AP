//
// Created by lior on 12/29/22.
//

#include "Map.h"

// constructor :
// takes in nested array of integers (filled with 0 as passage and 1 as wall), and initializes a map that represent that array.
Map::Map(int maparr[7][7]) {
    // initializing the map coordinates
    for (int row = 0; row < 7; row++) {
        for (int column = 0; column < 7; column++) {
            m_coordinates[row][column] = maparr[row][column];
        }
    }
}

// operator + :
// function takes in a reference of other map, and returns a new map that is the result of addition of the two maps.
// the addition of the maps is executed with "or" operator.
Map Map::operator+(const Map& other)const {
    int newmap[7][7];
    // initialize walls and passages
    for (int row = 0; row < 7; row++) {
        for (int column = 0; column < 7; column++) {
            newmap[row][column] = (this->m_coordinates[row][column] || other.m_coordinates[row][column]);
        }
    }
    // initialize new map and return it
    return Map(newmap);
}

// operator += :
// function takes in a reference of other map, and adds all the walls in the other map to current map.
Map& Map::operator+=(const Map& other) {
    // if same map, return this map
    if (this == &other)
        return *this;
    // if there is a wall in other map, add wall to this map
    for (int row = 0; row < 7; row++) {
        for (int column = 0; column < 7; column++) {
            if (other.m_coordinates[row][column] == 1)
                this->m_coordinates[row][column] = 1;
        }
    }
    // return a reference to this map
    return *this;
}

// operator = :
// function takes in a reference of other map, and copies the passages and walls of the other map to current map.
Map& Map::operator=(const Map& other) {
    // if same map, return this map
    if (this == &other)
        return *this;
    // copy all walls and passages of other map
    for (int row = 0; row < 7; row++) {
        for (int column = 0; column < 7; column++) {
            this->m_coordinates[row][column] = other.m_coordinates[row][column];
        }
    }
    // return a reference to this map
    return *this;
}

// operator == :
// if all the walls and the passages in the maps are identical, returns true. else, returns false.
bool Map::operator ==(const Map& other)const {
    // if same map, return true
    if (this == &other)
        return true;
    // compare all walls and passages of this map and other map
    for (int row = 0; row < 7; row++) {
        for (int column = 0; column < 7; column++) {
            // if finds they are not similar, return false
            if (this->m_coordinates[row][column] != other.m_coordinates[row][column])
                return false;
        }
    }
    // if similar, returns true
    return true;
}

// operator << :
// function takes in an ostream and a reference to a map, and prints the map through the ostream.
ostream& operator<<(ostream& out, const Map& map) {
    for (int row = 6; row >= 0; row--) {
        out << "[";
        for (int column = 0; column < 6; column++) {
            out << map.m_coordinates[row][column] << " ";
        }
        out << map.m_coordinates[row][6] << "]" << endl;
    }
    return out;
}

// function that takes in coordinates and return if there is a robot can move to there.
// if passage, return true. if wall, returns false.
bool Map::canMove(int x, int y) {
    return (!this->m_coordinates[y][x]);
}

// function that checks if an index is outside of the map. if out, returns true. if inside the map, returns false
bool Map::outOfReach(int x, int y) {
    if (x > 6 || x < 0 || y > 6 || y < 0)
        return true;
    return false;
}

// default constructor
Map::~Map() = default;