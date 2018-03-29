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

    // std::cout << piece << std::endl;
    // no piece at original position
    if (piece == ' '){
        return 1;
    }

    // move piece and reset pieces initial position
    board[row1][col1] = ' ';
    board[row2][col2] = piece;


    return 0;

}

void Board::print_board()
{
    for(int i = 7;i>=0; i--){
         for(int j = 0;j<8; j++){
            std::cout << board[i][j];
        }
        std::cout << std::endl;
    }

}

std::string Board::board_to_FEN(colour_ active_colour)
{

    int blank_count = 0; // count how many blank tiles for each row
    bool counting_blanks = false;
    std::string FEN_board;

    for(int i=0;i<8;i++) {
        counting_blanks = false;
        for(int j=0;j<8;j++) {
            if (board[i][j] == ' '){
                blank_count++;
                counting_blanks=true;
            } else { // there is a piece

                if(blank_count>=1 && counting_blanks){
                    FEN_board += std::to_string(blank_count);
                    counting_blanks = false;
                    
                }
                blank_count = 0;
                FEN_board +=  board[i][j];

            }
            
        }
        if(blank_count>0){
            FEN_board += std::to_string(blank_count);
            blank_count = 0;
        }
        FEN_board += "/";
    }

    // set active colour
    if (active_colour == WHITE_){
        FEN_board += " w";
    } else {
        FEN_board += " b";
    }
    return FEN_board;
}