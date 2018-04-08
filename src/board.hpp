#ifndef Board_H
#define Board_H

#include <string>
#include "chess_piece.hpp"

//constants

class Board {
    //0 0 is white rook 
    char board[8][8] = {
        {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'},
        {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
        {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'},
        
         
    };
    std::vector< std::vector <ChessPiece*>> chessBoard;
    //std::string player1;
    //std::string player2;

    public:
        Board(QWidget* pwindow);

        //returns piece at that position
        char get_position(int row, int col);

        // returns 0 if succesful, else 1 for invalid move
        // row1 col1 initial position : row2,col2 final position
        int move_piece(int row1, int col1, int row2, int col2);

        int move(position startpos, position endpos);

        // print board layout to stdout
        void print_board();

        std::string board_to_FEN(colour_ active_colour);

};


#endif