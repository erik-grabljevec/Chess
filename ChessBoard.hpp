////////////////////////////////////////////////////////////////////////////////
// File: ChessBoard.h
// Author: Erik Grabljevec
// Email: erikgrabljevec5@gmail.com
// Description: This is header file for class ChessBoard and related functions
//				and definitions. Class ChessBoard keeps track of current chess
//				game. First game is started when new object is created.
//				User can interfere with class only with 3 functions:
//				- resetBoard: sets new game
// 				- submitMove: make new move in game
//				- print_board: prints board state in ASCCI symbols.
//				For more information refere to class ChessBoard.
////////////////////////////////////////////////////////////////////////////////

#ifndef CHESSBOARD_H_
#define CHESSBOARD_H_

#include <iostream>
#include <cstdlib>

#include "ChessPiece.h"
#include "Square.h"

// Function dif calculates if "x1" is smaller, equal or bigger to "x2".
// If x1==x2 it returns 0, if x1<x2 it returns -1 and otherwise 1.
int dif(int x1, int x2);

// TYPEDEFs
// ========
typedef ChessPiece * ChessPiecePtr;

// CLASS: ChessBoard
// =============================================================================
// Class ChessBoard represents chess board. It uses 3 attributes to do so.
// With "game_finished" we keep track if the game is still running. Should
// game be finished, we can no longer input new moves. To start new game,
// resetBoard should be called. We keep track of who's turn it is with attribute
// "turn", which is of type Color. Board is presented with "board" that contains
// pointers to chess pieces. If pointer equals NULL, it means that given square
// is empty.
//
// User can interfere with class only with 3 functions:
//    - resetBoard: sets new game
// 	  - submitMove: make new move in game
//	  - print_board: prints board state in ASCCI symbols.
// Example of use would be next 4 lines:
//     ChessBoard cb;   <- creates new board and starts first game
//     cb.submitMove("E2", "E4");   <- moves white's pawn
//     cb.print_board();	<- print's board after first move.
//	   cb.resetBoard();
//
// Imported header 1 is ChessPiece: class ChessPiece is used to represent 
// pieces on board.
//
// Imported header 2 is Square: class Square is used for fast access to the
// board. NOTE THIS LOOP: for(int i=0; i<64; i++) Square(i).
//                        ^ this loop iterates entire board (refer to Square.h). 
//
// On algorithms used: reader might note, that all algorithms used (to determine
// chess, chessmate and stellmate) are brute force (O(n^6)). We realise that
// this is not optimal approach, but because problem isn't scalable, solution
// seems by far the best in terms of simplicity and readability. 
//
// On comments: private functions are not commented in header file. Reader
// should refer to .cpp file.
// =============================================================================
class ChessBoard {
private:
    // BASIC ATTRIBUTES
    // ================
    bool game_finished;  // Bool that keeps track, when game is finished.
    Color turn;   // Keep track who's turn it is.

    // MAIN CONTAINER
    // ==============
    ChessPiecePtr board[8][8];

    // GET FUNCTIONS
    // =================
    ChessPiecePtr& get_square(Square square);   // Very important functions used
												// for access.

    // SET BOARD FUNCTIONS
    // ===================
    void reset_board();
    void clear_board();
    void delete_square(Square square);
    void set_board_null();
    void set_starting_set(Color color);

    // PRINT METHODS
    // =============
    void print_new_line() const;
    void print_last_line() const;
    void print_square(int i, int j) const;
    void print_equals_line(int d) const;
    void print_move(Square start, Square end);
    void print_game_state();

    // GAME STATE METHODS
    // ==================
    bool has_valid_move(Color color);
    bool is_in_chess(Color color);
    bool ok_end_position(Square start, Square end, Color color, bool verbose);
    bool check_game_end();
    void end_game();

    // MOVE VALIDATION METHODS
    // =======================
    bool enter_move(Square start, Square end);
    bool valid_move(Square start, Square end, Color color, bool verbose);
    bool ok_start_square(Square square, Color color, bool verbose);
    bool ok_end_square(Square square, Color color, bool verbose);
    bool can_move(Square start, Square end, bool verbose);
    bool ok_piece_move(Square start, Square end, bool verbose);
    bool free_path(Square start, Square end);

    // MODIFICATION METHODS
    // ====================
    void make_move(Square start, Square end);
    void pass_turn();

    // HELPER FUNCTIONS
    // ================
    bool validate_square_color(Square square, Color color);
    int get_pawn_line(Color color);
    Square find_king(Color color);

public:
    // CONSTRUCTORS / DESTRUCTORS
    // ==========================
    ChessBoard();
    ChessBoard(ChessBoard& old);
    virtual ~ChessBoard();

    // PUBLIC METHOD: new game
    // =======================
    // This function resets the state of board. It sets all pieces to it's
    // starting positions. Sets "turn" to WHITE and "game_finished" to false.
    void resetBoard();

    // PUBLIC METHOD: print board
    // ==========================
    // This method prints chess board with ASCII signs.
    void print_board() const;

    // PUBLIC METHOD: submit move
    // ==========================
    // This method take starting and ending square. Both squares should be in
    // format [A-H][1-8]. If move is not valid in any way (invalid input,
    // against the rules, etc) function returns false. If function succeeds
    // it returns true.
    bool submitMove(string start, string end);
};


#endif // CHESSBOARD_H_
