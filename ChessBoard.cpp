////////////////////////////////////////////////////////////////////////////////
// File: ChessBoard.cpp
// Author: Erik Grabljevec
// Email: erikgrabljevec5@gmail.com
// Description: Refer to ChessBoard.h.
////////////////////////////////////////////////////////////////////////////////

#include "ChessBoard.hpp"

// Function dif.
int dif(int x1, int x2) {
    if(x1 == x2) return 0;
    return (x1-x2)/abs(x1-x2);
}

// Basic constructor. 
ChessBoard::ChessBoard() {
    turn = WHITE;
	set_board_null();
	resetBoard();
}

// Copy constructor.
// It utilizes "clone" method in ChessPiece.h.
ChessBoard::ChessBoard(ChessBoard& old_board) {
    // Next loop copies all chess pieces from old to new board.
    for(int i=0; i<64; i++) {
        if(old_board.get_square(Square(i)) == NULL)
            get_square(Square(i)) = NULL;
        else
            get_square(Square(i)) = old_board.get_square(Square(i))->clone();
    }
    game_finished = old_board.game_finished;
    turn = old_board.turn;
}

// Destructor.
ChessBoard::~ChessBoard() {
    // Deliberately empty.   
}

// PUBLIC METHOD: resetBoard
// =========================
void ChessBoard::resetBoard() {
    game_finished = false;
    reset_board();
    cout << "A new chess game is started!" << endl;
}

// PUBLIC METHOD: print board
// ==========================
// This function iterates through board and prints ASCII representations
// of all chess pieces.
void ChessBoard::print_board() const {
    for(int j=7; j>=0; j--) {
        print_new_line();
        cout << " " << j+1 << " ";
        for(int i=0; i<8; i++) {
            cout << "|";
            print_square(i, j);
        }
        cout << "|";
    }
    print_new_line();
    print_last_line();
}

// Method: print new line
// This method assists with printing out ASCII chess board.
void ChessBoard::print_new_line() const {
    cout << endl << "   ";
    for(int i=0; i<8; i++)
        cout << "+---";
    cout << "+" << endl;
}

// Method: print last line
// This method assists with printing out ASCII chess board.
void ChessBoard::print_last_line() const {
    cout << "    ";
    for(int i=0; i<8; i++) {
        cout << " ";
        // Next line prints i-th character after 'A'.
        cout << static_cast<char>(static_cast<int>('A') + i);
        cout << "  ";
    }
    cout << endl << endl;
}

// Method: print square
void ChessBoard::print_square(int i, int j) const {
    if(board[i][j] == NULL)
        cout << "   ";
    else
        board[i][j]->print_ascii(cout);
}

// Method: get square
// Get_square function takes square as input and returns chess piece
// at that square. This function is used to simplify access.
ChessPiecePtr& ChessBoard::get_square(Square square) {
    return board[square.x][square.y];
}

// Method: print equals line.
// This method assists with printing out ASCII chess board.
void ChessBoard::print_equals_line(int d) const {
    for(int i=0; i<d; i++)
        cout << "=";
    cout << endl;
}

// Method: print move
// This method is used to print out each move players do.
void ChessBoard::print_move(Square start, Square end) {
    if(get_square(start) == NULL) {  // Starting square shouldn't be NULL
        cerr << "ERROR";             // we just make double check here.
        return;
    }

    get_square(start)->print_name(cout);
    cout << " moves from " << start << " to " << end;
    if(get_square(end) != NULL) {
        cout << " taking ";
        get_square(end)->print_name(cout);
    }
    cout << endl;
}

// Method: print game state
// This method prints current state of game, e. g: "White's in chess".
// Game state always refers to state of game that was valid entire game.
// It also refers to just before a player does move.
void ChessBoard::print_game_state() {
    bool has_move, in_chess;

    has_move = has_valid_move(turn);
    in_chess = is_in_chess(turn);

    // If current player to move is either in check or has no move.
    // Game will end.
    if(!has_move || in_chess) {
        cout << color_to_string(turn) << " is in ";
        if(!has_move && in_chess) cout << "checkmate";
        else if(!has_move) cout << "stellmate";
        else cout << "check";
        cout << endl;
    }
}

// Method: reset board
void ChessBoard::reset_board() {
    clear_board();
    set_board_null();
    set_starting_set(WHITE);
    set_starting_set(BLACK);
	turn = WHITE;
}

// Method: clear board
void ChessBoard::clear_board() {
    for(int i=0; i<64; i++) {
        delete_square(Square(i));
    }
}

// Method: delete square
void ChessBoard::delete_square(Square square) {
    if(get_square(square) != NULL)
        delete get_square(square);
    get_square(square) = NULL;
}

// Method: set board null
void ChessBoard::set_board_null() {
    for(int i=0; i<64; i++)
        get_square(Square(i)) = NULL;
}

// Method: set starting set
void ChessBoard::set_starting_set(Color color) {
    int first_line, second_line, king_position;

    first_line = (color==WHITE ? 0 : 7);
    second_line = (color==WHITE ? 1 : 6);
    king_position = 4;

    for(int i=0; i<8; i++)
        board[i][second_line] = new Pawn(color);

    board[0][first_line] = new Rook(color);
    board[7][first_line] = new Rook(color);

    board[1][first_line] = new Knight(color);
    board[6][first_line] = new Knight(color);

    board[2][first_line] = new Bishop(color);
    board[5][first_line] = new Bishop(color);

    board[king_position][first_line] = new King(color);
    board[7-king_position][first_line] = new Queen(color);
}

// Method: has_valid_move
// This is the bottleneck method, but it still manages to be fast enough for
// us to use it. It simply bruteforces entire board. For more explanation
// refer to ChessBoard class description.
bool ChessBoard::has_valid_move(Color color) {
    for(int i=0; i<64; i++) {
        if(get_square(Square(i)) != NULL
           && get_square(Square(i))->get_color() == color)
        {
            for(int j=0; j<64; j++) {
                ChessBoard new_board(*this);
                if(new_board.valid_move(Square(i), Square(j), color, false)) {
                    return true;
                }
            }
        }
    }
    return false;
}

// Method: is in chess
// Tells if player of Color "color" is in chess.
// This function iterates entire board, searching for "inverse_color("color")"
// piece that could move to "color" king.
bool ChessBoard::is_in_chess(Color color) {
    Square king_square;
    Color opo_color;

    king_square = find_king(color);
    opo_color = inverse_color(color);

    for(int i=0; i<8; i++) {
        for(int j=0; j<8; j++) {
            if(board[i][j] != NULL && board[i][j]->get_color() == opo_color) {
                if(can_move(Square(i,j), king_square, false))
                    return true;
            }
        }
    }
    return false;
}

// Method: ok end position
// Method that checks if move from Square start to Square end won't put us in 
// chess. It creates new board and simulates move on it.
// NOTE: this method doesn't deal with invalid input.
bool ChessBoard::ok_end_position(Square start, Square end,
                                 Color color, bool verbose) {

    ChessBoard new_board(*this);
    new_board.make_move(start, end);
    if(new_board.is_in_chess(color)) {
        if(verbose)
            cerr << "This move leaves you in check!" << endl;
        return false;
    }
    return true;
}

// PUBLIC METHOD: enter move
// =========================
// Checks if input is valid and converts it in format of class Square.
// Execution continues on enter_move(Square, Square).
bool ChessBoard::submitMove(string start, string end) {
    bool conversion;
    Square start_square, end_square;

    if(game_finished) return false;  // If game is over you need to reset game.

    conversion = string_to_square(start, start_square);
    conversion &= string_to_square(end, end_square);

    if(!conversion) {
        cerr << "Invalid input!" << endl;
        return false;
    }

    return enter_move(start_square, end_square);
}

// Method: enter move
bool ChessBoard::enter_move(Square start, Square end) {
    if(!valid_move(start, end, turn, true))
        return false;

    print_move(start, end);
    make_move(start, end);

    pass_turn();
    print_game_state();

    if(check_game_end()) 
        end_game();

    //print_board(); // DELETE!!

    return true;
}

// Method: valid move. 
// Validates move from Square "start" to Square "end".
// Bool "verbose" tracks if we should output error log.
bool ChessBoard::valid_move(Square start, Square end,
                            Color color, bool verbose) {
    if(!ok_start_square(start, color, verbose)) return false;

	// Any of the next conditions means that piece can't make that move.
    if(!can_move(start, end, verbose)
    	|| !ok_end_square(end, color, verbose)
    	|| !ok_end_position(start, end, color, verbose)) {
		
		if(verbose) {
			get_square(start)->print_name(cerr);
			cerr << " cannot move to " << end << "!" << endl;
		}
		return false;
	}

    return true;
}

// Method: ok_start_square
bool ChessBoard::ok_start_square(Square square,
                                 Color color, bool verbose) {
    if(get_square(square) == NULL) {  // Start square can't be empty.
        if(verbose)
            cerr << "There is no piece at position " << square << "!" << endl;
        return false;
    }

    if(!validate_square_color(square, color)) {  // You have to move piece of
        if(verbose) {                            // your color.
            cerr << "It is not " << color_to_string(inverse_color(color))
                << "'s turn to move!" << endl;
        }
        return false;
    }

    return true;
}

// Method ok_end_square
bool ChessBoard::ok_end_square(Square square,
                               Color color, bool verbose) {
    if(get_square(square) == NULL) return true; // End square can be empty.

    if(validate_square_color(square, color)) {
            return false;
    }

    return true;
}

// Method: can move
// This method if piece at Square "start" can move to Square "end".
// It checks if anything is on path and if move is allowed according to chess
// rules.
// NOTE: doesn't check if end square is of the same color. That is what
// function "ok_end_square" takes care of.
bool ChessBoard::can_move(Square start, Square end, bool verbose) {
    // We make this just to ensure no unwanted erros are popped.
    if(get_square(start) == NULL) return false;

    if(!ok_piece_move(start, end, verbose)) 
        return false;
    
    if(!get_square(start)->get_jumps()) {  // If piece doesn't jump, check path.
        if(!free_path(start, end))
            return false;
    }
    return true;
}

// Method: ok piece move
// Checks if move at Square "start", can move from Square "start" to
// Square "end" if board is EMTPY!!!
bool ChessBoard::ok_piece_move(Square start, Square end, bool verbose) {
    Color piece_color;
    int pawn_line, dx, dy; // dx and dy present piece's move.
    bool first, eats; // "first" means if we are in pawn line.
                      // "eats" means if we we will eat piece with this move.

    piece_color = get_square(start)->get_color();
    pawn_line = get_pawn_line(piece_color);
    first = (pawn_line == start.y);
    eats = (get_square(end) != NULL);
    dx = end.x - start.x;
    dy = end.y - start.y;

    return ( get_square(start)->is_valid_move(dx, dy, eats, first) );
}

// Method: free_path
// This method checks if path between "start" and "end" square is free.
// This checks is exclusive, meaning it doesn't take in account first and
// last square.
bool ChessBoard::free_path(Square start, Square end) {
    int dx, dy, x, y;

    dx = dif(end.x, start.x);
    dy = dif(end.y, start.y);
    x = start.x + dx;
    y = start.y + dy;

    while(x!=end.x || y!=end.y) {
        if(board[x][y] != NULL)  // If square on path is non-empty return false.
            return false;

        x += dx;
        y += dy;
    }
    return true;
}

// Method: check game end
// Method that checks if player that is currently on play has no move.
bool ChessBoard::check_game_end() {
    return !has_valid_move(turn);
}

// Method: end game
void ChessBoard::end_game() {
    game_finished = true;
}

// Method: validate square color
// This function first checks if pointer isn't NULL pointer to avoid errors.
// Than it comparse color of piece at position "square" to color "color".
bool ChessBoard::validate_square_color(Square square, Color color) {
    if(get_square(square) == NULL) return false;
    return (get_square(square)->get_color() == color);
}

// Method: get pawn line.
int ChessBoard::get_pawn_line(Color color) {
    return (color == WHITE ? 1 : 6);
}

// Method: make move.
void ChessBoard::make_move(Square start, Square end) {
    delete_square(end);
    get_square(end) = get_square(start);
    get_square(start) = NULL;
}

// Method: pass turn.
void ChessBoard::pass_turn() {
    turn = inverse_color(turn);
}

// Method: find king.
// Function which returns Square on which king of Color "color" is.
// If it doesn't find king on board (which should never happen) it returns
// Square (0,0).
Square ChessBoard::find_king(Color color) {
    for(int i=0; i<64; i++) {
        ChessPiecePtr current_piece = get_square(Square(i));

        if(current_piece != NULL && current_piece->get_name() == "King"
            && current_piece->get_color() == color) {
                return Square(i);
            }
    }
    return Square(0);
}
