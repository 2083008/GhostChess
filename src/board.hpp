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

    public:
        Board(QWidget* pwindow);

        //returns piece at that position
        char get_position(int row, int col);

        void move_piece(std::string move);

        int move(position startpos, position endpos);

        // print board layout to stdout
        void print_board();

        int charToInt(char val);

        std::string board_to_FEN(colour_ active_colour);

};


#endif