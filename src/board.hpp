#ifndef Board_H
#define Board_H

#include <string>

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
    //std::string player1;
    //std::string player2;

    public:
        Board();

        //returns piece at that position
        char get_position(int row, int col);

        // returns 0 if succesful, else 1 for invalid move
        // row1 col1 initial position : row2,col2 final position
        int move_piece(int row1, int col1, int row2, int col2);

        // print board layout to stdout
        void print_board();

        std::string board_to_FEN();

};


#endif