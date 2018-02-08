#include <string>
#include "board.hpp"
#include <iostream>


//init the board
Board::Board()
{

}

char Board::get_position(int row, int col)
{
    return board[col][row];
}

int Board::move_piece(int row1, int col1, int row2, int col2)
{
    char piece = get_position(row1, col1);

    std::cout << piece << std::endl;
    // no piece at original position
    if (piece == ' '){
        return 1;
    }

    // move piece and reset pieces initial position
    board[col1][row1] = ' ';
    board[col2][row2] = piece;


    return 0;

}

void Board::print_board()
{
    for(int i = 7;i >=0; i--){
         for(int j = 0;j <8; j++){
            std::cout << board[i][j];
        }
        std::cout << std::endl;
    }

}