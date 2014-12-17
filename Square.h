////////////////////////////////////////////////////////////////////////////////
// File: Square.h
// Author: Erik Grabljevec
// Email: erikgrabljevec5@gmail.com
// Description: Header file for class Square. Everything is pretty
//              straightforward. For more info refer to class
//              Square description.
////////////////////////////////////////////////////////////////////////////////

#ifndef SQUARE_H_
#define SQUARE_H_

#include <iostream>
#include <string>

using namespace std;


// CLASS: Square
// =============
// Simple container that acts the same way as pair. As it is used in content
// of chessboard we name it Square. X and Y are limited between 0 and 7. If
// we try to initialize them with any other value, it will be set to 0.
// Square can also be initialized with number. In that case selected square
// is initialized with (number/8, number%8). This constructor helps with
// itterations.
// NOTE: for simplicity of the use and as there is nothing to really "hide", we
// set entire class to public.
class Square {
public:
    int x; // X coordinate of square.
    int y; // Y coordinate of square.

    // CONSTRUCTORS/DESTRUCTORS
    // ========================
    Square();
    Square(int _x, int _y);
    Square(int number); // <- This constructor is used to easily iterator board.
    Square(const Square& new_square);
    virtual ~Square();

    // OPERATOR: ==
    // ============
    friend bool operator==(Square a, Square b);

    // OPERATOR: <<
    // ============
    friend ostream& operator<<(ostream& outs, Square square);
};

// Function that converts string to square.
// Input string is "square_str". Expected input is in format [A-H][0-7].
// If converted result gets writen in Square "square". Function returns true
// if conversion is successful and false if not.
bool string_to_square(string square_str, Square& square);


#endif // SQUARE_H_
