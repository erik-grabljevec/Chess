////////////////////////////////////////////////////////////////////////////////
// File: Square.cpp
// Author: Erik Grabljevec
// Email: erikgrabljevec5@gmail.com
// Description: Refer to Square.h
////////////////////////////////////////////////////////////////////////////////

#include "Square.h"


// Basic constructor for Square class.
Square::Square() {
    // Deliberately empty.
}

// Constructor for Square class that takes for argument both coordinates.
Square::Square(int _x, int _y) {
    if(_x < 0 || 7 < _x) _x = 0; // Correct invalid input to 0.
    if(_y < 0 || 7 < _y) _y = 0; // -||-

    x = _x;
    y = _y;
}

// Constructor for Square class. It takes only one number, that is converted
// to two coordinates.
Square::Square(int number) {
    int _x = number / 8;
    int _y = number % 8;

    if(_x < 0 || 7 < _x) _x = 0; // Correct invalid input to 0.
    if(_y < 0 || 7 < _y) _y = 0; // -||-

    x = _x;
    y = _y;
}

// Copy constructor.
Square::Square(const Square& new_square) {
    x = new_square.x;
    y = new_square.y;
}

// Destructor.
Square::~Square() {
    // Deliberately empty.
}

// Compare two squares.
bool operator==(Square a, Square b) {
    return (a.x==b.x) && (a.y==b.y);
}

// Print square in format [A-H][1-8]
ostream& operator<<(ostream& outs, Square square) {
    char first, second;

    first = static_cast<char>(static_cast<int>('A') + square.x);
    second = static_cast<char>(static_cast<int>('1') + square.y);

    outs << first << second;

    return outs;
}

// Function that converts string to square.
bool string_to_square(string square_str, Square& square) {
    if(square_str.length() != 2) return false;
    if(square_str[0] < 'A' || 'H' < square_str[0]) return false;
    if(square_str[1] < '1' || '8' < square_str[1]) return false;

    square.x = static_cast<int>(square_str[0]) - static_cast<int>('A');
    square.y = static_cast<int>(square_str[1]) - static_cast<int>('1');

    return true;
}


