chess: ChessMain.o ChessBoard.o ChessPiece.o Square.o
	g++ ChessMain.o ChessBoard.o ChessPiece.o Square.o -o chess

ChessMain.o: ChessMain.cpp ChessBoard.hpp
	g++ -Wall -g -c ChessMain.cpp 

ChessBoard.o: ChessBoard.cpp ChessBoard.hpp ChessPiece.h Square.h
	g++ -Wall -g -c ChessBoard.cpp 

ChessPiece.o: ChessPiece.cpp ChessPiece.h Square.h
	g++ -Wall -g -c ChessPiece.cpp

Square.o: Square.cpp Square.h
	g++ -Wall -g -c Square.cpp

clean:
	rm -rf *o chess



