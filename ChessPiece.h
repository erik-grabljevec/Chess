////////////////////////////////////////////////////////////////////////////////
// File: ChessPiece.h
// Author: Erik Grabljevec
// Email: erikgrabljevec5@gmail.com
// Description: Most important part of this file is class "ChessPiece". This is
//              abstract class holding frame-work for chess piece classes.
//              There are several chess-pieces derived from this abstract class.
//              These are: King, Queen, Bishop, Knight, Rook and Pawn.
//              As support we also implement enumerator Color, which stores
//              color of chess piece (white/black).
////////////////////////////////////////////////////////////////////////////////

#ifndef CHESSPIECE_H_
#define CHESSPIECE_H_

#include <iostream>
#include <cstdlib>

#include "Square.h"

using namespace std;


// Enumerator: Color that is used to mark color of chess pieces.
enum Color {
    WHITE,
    BLACK
};

// Function that Color "color" as input and inverts it.
// It turns WHITE in BLACK and vice versa.
Color inverse_color(Color color);

// Function that takes color and returns it's string representation.
// For example WHITE gets converted to "White".
string color_to_string(Color color);

// CLASS: ChessPiece
// =================
// This is abstract class that represents chess piece. All actual chess pieces
// are derived from this class. This class has two important methods:
// "is_valid_move": validates if certain move is valid.
// "print": prints ASCII representation of piece.
//
// All attributes are set when class is constructed. Therefore we have only
// one get function and none set functions.
class ChessPiece {
private:
    // Atributes
    // =========
    char symbol; // symbol, that is used to represent piece on ASCII board
    string name; // name of the piece
    Color color; // color: WHITE/BLACK
    bool jumps; // does piece jump. It is true for knight only.

public:
    // CONSTRUCTORS / DESTRUCTORS
    // ==========================
    ChessPiece();
    ChessPiece(const ChessPiece& new_piece);
    virtual ~ChessPiece();

    // CLONE
    // =====
	// Clone function is used when we make duplicate of chess board.
    virtual ChessPiece * clone() const;

    // ASSIGNMENT OPERATOR
    // ===================
    ChessPiece& operator=(const ChessPiece& new_piece);

    // SET / GET
    // =========
    // Package of set and get methods.
    void set_symbol(char new_symbol);
    void set_name(string new_name);
    void set_color(Color new_color);
    void set_jumps(bool new_jumps);
    bool get_jumps();
    Color get_color();
    string get_name();

    // PUBLIC METHOD: is_valid_move
    // ============================
    // This method takes as input pair (dx, dy) that represents the
    // movement of chess piece. Furthermore it takes bool "eats" that tells
    // whether this piece has eaten another piece during this move.
    // It also takes bool "first" that tells if this move was piece's first
    // move. Both bool arguments only influence movement of PAWN.
    virtual bool is_valid_move(int dx, int dy,
                               bool eats=false, bool first=false);

    // PUBLIC METHOD: print
    // ====================
    // "print_ascii" prints ASCII representation. For example =P= for
    // black pawn. Another example would be  K  for white king.
    void print_ascii(ostream& outs);
    // This method prints piece's name. For example: Blacks' pawn, or White's
    // queen.
    void print_name(ostream& outs);
};

// CLASS: King
// ===========
// Class representing chess piece King. It is derived from abstract class
// chess piece.
class King: public ChessPiece {
    public:
        // CONSTRUCTORS / DESTRUCTORS
        // ==========================
        King(Color color);
        virtual ~King();

        // CLONE
        // =====
        King * clone() const;

        // PUBLIC METHOD: is_valid_move
        // ============================
        // Refer to class ChessPiece for description.
        bool is_valid_move(int dx, int dy, bool eats=false, bool first=false);
};

// CLASS: Queen
// ============
// Class representing chess piece Queen. It is derived from abstract class
// chess piece.
class Queen: public ChessPiece {
    public:
        // CONSTRUCTORS / DESTRUCTORS
        // ==========================
        Queen(Color color);
        virtual ~Queen();

        // CLONE
        // =====
        Queen * clone() const;

        // PUBLIC METHOD: is_valid_move
        // ============================
        // Refer to class ChessPiece for description.
        bool is_valid_move(int dx, int dy, bool eats=false, bool first=false);
};

// CLASS: Bishop
// ============
// Class representing chess piece Bishop. It is derived from abstract class
// chess piece.
class Bishop: public ChessPiece {
    public:
        // CONSTRUCTORS / DESTRUCTORS
        // ==========================
        Bishop(Color color);
        virtual ~Bishop();

        // CLONE
        // =====
        Bishop * clone() const;

        // PUBLIC METHOD: is_valid_move
        // ============================
        // Refer to class ChessPiece for description.
        bool is_valid_move(int dx, int dy, bool eats=false, bool first=false);
};

// CLASS: Knight
// =============
// Class representing chess piece Knight. It is derived from abstract class
// chess piece.
class Knight: public ChessPiece {
    public:
        // CONSTRUCTORS / DESTRUCTORS
        // ==========================
        Knight(Color color);
        virtual ~Knight();

        // CLONE
        // =====
        Knight * clone() const;

        // PUBLIC METHOD: is_valid_move
        // ============================
        // Refer to class ChessPiece for description.
        bool is_valid_move(int dx, int dy, bool eats=false, bool first=false);
};

// CLASS: Rook
// ===========
// Class representing chess piece Rook. It is derived from abstract class
// chess piece.
class Rook: public ChessPiece {
    public:
        // CONSTRUCTORS / DESTRUCTORS
        // ==========================
        Rook(Color color);
        virtual ~Rook();

        // CLONE
        // =====
        Rook * clone() const;

        // PUBLIC METHOD: is_valid_move
        // ============================
        // Refer to class ChessPiece for description.
        bool is_valid_move(int dx, int dy, bool eats=false, bool first=false);
};

// CLASS: Pawn
// ===========
// Class representing chess piece Pawn. It is derived from abstract class
// chess piece.
class Pawn: public ChessPiece {
    public:
        // CONSTRUCTORS / DESTRUCTORS
        // ==========================
        Pawn(Color color);
        virtual ~Pawn();

        // CLONE
        // =====
        Pawn * clone() const;

        // PUBLIC METHOD: is_valid_move
        // ============================
        // Refer to class ChessPiece for description.
        bool is_valid_move(int dx, int dy, bool eats=false, bool first=false);
};

#endif // CHESSPIECE_H_
