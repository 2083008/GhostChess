#include "chess_piece.hpp"
#include <cmath>
#include <stdlib.h>     /* abs */
#include <stdio.h>


ChessPiece :: ChessPiece(colour col)
{
    piece_colour = col;
};


int Knight::valid_move(position start_position, position end_position)
{


    return 1;

}


int King::valid_move(position start_position, position end_position)
{
    if (abs(start_position.row - end_position.row) <= 1
        && abs(start_position.column - end_position.column) <= 1) {
        return 0;
    }
    
    return 1;

}