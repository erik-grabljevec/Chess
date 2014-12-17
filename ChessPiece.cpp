////////////////////////////////////////////////////////////////////////////////
// File: ChessPiece.cpp
// Author: Erik Grabljevec
// Email: erikgrabljevec5@gmail.com
// Description: Refer to ChessPiece.h.
////////////////////////////////////////////////////////////////////////////////

#include "ChessPiece.h"


// Function that inverts color.
Color inverse_color(Color color) {
    return (color==WHITE ? BLACK : WHITE);
}

// Color_to_string.
string color_to_string(Color color) {
    return (color == WHITE ? "White" : "Black");
}

///////////////////////////////// ChessPiece ///////////////////////////////////

// Constructor.
ChessPiece::ChessPiece() {
    // Deliberately empty.
}

// Copy constructor.
ChessPiece::ChessPiece(const ChessPiece& new_piece) {
    symbol = new_piece.symbol;
    name = new_piece.name;
    color = new_piece.color;
    jumps = new_piece.jumps;
}

// Destructor.
ChessPiece::~ChessPiece() {
    // Deliberately empty.
}

// Clone.
ChessPiece * ChessPiece::clone() const {
    return (new ChessPiece(*this));
}

// Assignment.
ChessPiece& ChessPiece::operator=(const ChessPiece& new_piece) {
    symbol = new_piece.symbol;
    name = new_piece.name;
    color = new_piece.color;
    jumps = new_piece.jumps;

	return (*this);
}

// Set symbol.
void ChessPiece::set_symbol(char new_symbol) {
    symbol = new_symbol;
}

// Set name.
void ChessPiece::set_name(string new_name) {
    name = new_name;
}

// Set color.
void ChessPiece::set_color(Color new_color) {
    color = new_color;
}

// Set jumps.
void ChessPiece::set_jumps(bool new_jumps) {
    jumps = new_jumps;
}

// Get jumps.
bool ChessPiece::get_jumps() {
    return jumps;
}

// Get color.
Color ChessPiece::get_color() {
    return color;
}

// Get name.
string ChessPiece::get_name() {
    return name;
}

// Print function.
void ChessPiece::print_ascii(ostream& outs) {
    char side_char;

    side_char = (color == WHITE ? ' ' : '=');
    outs << side_char;
    outs << symbol;
    outs << side_char;
}

// Print name.
void ChessPiece::print_name(ostream& outs) {
    outs << color_to_string(color);
    outs << "'s ";
    outs << name;
}

// Dummy definition of virtual function.
bool ChessPiece::is_valid_move(int dx, int dy,
                               bool eats, bool first) {
    return false;
}

///////////////////////////////// King /////////////////////////////////////////

// Constructor.
King::King(Color _color) {
    set_symbol('K');
    set_name("King");
    set_color(_color);
    set_jumps(false);
}

// Destructor.
King::~King() {
    // Deliberately empty.
}

// Clone function.
King * King::clone() const {
    return (new King(*this));
}

// Method that tells if move is valid.
// Move is valid when king moves for 0-1 in each directon, but not 0 in both
// directions.
bool King::is_valid_move(int dx, int dy, bool eats, bool first) {
    if(dx==0 && dy==0) return false;
    if(abs(dx) > 1 || abs(dy) > 1) return false;
    return true;
}

///////////////////////////////// Queen ////////////////////////////////////////

// Constructor.
Queen::Queen(Color _color) {
    set_symbol('Q');
    set_name("Queen");
    set_color(_color);
    set_jumps(false);
}

// Destructor
Queen::~Queen() {
    // Deliberately empty.
}

// Clone function.
Queen * Queen::clone() const {
    return (new Queen(*this));
}

// Method that tells if move is valid.
// Move is valid when queen moves in diagonal or side-way direction.
bool Queen::is_valid_move(int dx, int dy, bool eats, bool first) {
    if(dx==0 && dy==0) return false; // not moving
    if(abs(dx) == abs(dy)) return true; // diagonal moves
    if(dx == 0 || dy == 0) return true; // side move

    return false; // all other moves are invalid
}

///////////////////////////////// Bishop ///////////////////////////////////////

// Constructor.
Bishop::Bishop(Color _color) {
    set_symbol('B');
    set_name("Bishop");
    set_color(_color);
    set_jumps(false);
}

// Destructor
Bishop::~Bishop() {
    // Deliberately empty.
}

// Clone function.
Bishop * Bishop::clone() const {
    return (new Bishop(*this));
}

// Method that tells if move is valid.
// Move is valid when bishop moves in diagonal direction.
bool Bishop::is_valid_move(int dx, int dy, bool eats, bool first) {
    if(dx==0 && dy==0) return false; // not moving
    if(abs(dx) == abs(dy)) return true; // diagonal moves

    return false; // all other moves are invalid
}

///////////////////////////////// Knight ///////////////////////////////////////

// Constructor.
Knight::Knight(Color _color) {
    set_symbol('N');
    set_name("Knight");
    set_color(_color);
    set_jumps(true);
}

// Destructor
Knight::~Knight() {
    // Deliberately empty.
}

// Clone function.
Knight * Knight::clone() const {
    return (new Knight(*this));
}


// Method that tells if move is valid.
// Move is valid when one coordinate change has absolute value of 2 and
// another one absolute value of 1.
bool Knight::is_valid_move(int dx, int dy, bool eats, bool first) {
    if(abs(dx) == 1 && abs(dy) == 2) return true; // jump direction 1
    if(abs(dy) == 1 && abs(dx) == 2) return true; // mirror jump direction

    return false; // all other moves are invalid
}

///////////////////////////////// Rook /////////////////////////////////////////

// Constructor.
Rook::Rook(Color _color) {
    set_symbol('R');
    set_name("Rook");
    set_color(_color);
    set_jumps(false);
}

// Destructor
Rook::~Rook() {
    // Deliberately empty.
}

// Clone function.
Rook * Rook::clone() const {
    return (new Rook(*this));
}

// Method that tells if move is valid.
// Move is valid when rook moves side-way.
bool Rook::is_valid_move(int dx, int dy, bool eats, bool first) {
    if(dx==0 && dy==0) return false; // not moving
    if(dx == 0 || dy == 0) return true; // side move

    return false; // all other moves are invalid
}

///////////////////////////////// Pawn /////////////////////////////////////////

// Constructor.
Pawn::Pawn(Color _color) {
    set_symbol('P');
    set_name("Pawn");
    set_color(_color);
    set_jumps(false);
}

// Destructor
Pawn::~Pawn() {
    // Deliberately empty.
}

// Clone function.
Pawn * Pawn::clone() const{
    return (new Pawn(*this));
}

// Method that tells if move is valid.
// Pawn is most complicated. Several options have to be checked.
bool Pawn::is_valid_move(int dx, int dy, bool eats, bool first) {
    // First block checks vertical movement.
    if(get_color() == BLACK) { // we mirror vertical movement for black.
        dy *= -1;
    }
    if(dy == 2 && !first) return false;
    if(dy != 2 && dy != 1) return false;

    // Second block check horizontal movement.
    if(eats && abs(dx)!=1) return false; // Always eat side-ways.
    if(!eats && dx!=0) return false;

    // We passed all test.
    return true;
}
