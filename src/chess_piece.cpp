#include "chess_piece.hpp"
#include <cmath>
#include <stdlib.h>     /* abs */
#include <stdio.h>




ChessPiece::ChessPiece(colour_ col, int x, int y)
{
    piece_colour = col;
    this->x = x;
    this->y = y;
};


int Knight::valid_move(position start_position, position end_position)
{
    //if abs(start_position.row )
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

int King::move(int x, int y)
{
    return 0;
}


int Queen::valid_move(position start_position, position end_position)
{
    // if moving diagonally OR vertically
    if(abs(start_position.row - end_position.row) == abs(start_position.column - end_position.column)) {
        return 0;
    } else {
        return (!(abs(start_position.row - end_position.row)==0) != !(abs(start_position.column - end_position.column)==0));
    }
}


int Bishop::valid_move(position start_position, position end_position)
{
    //if abs(start_position.row )
    return (abs(start_position.row - end_position.row) == abs(start_position.column - end_position.column));

}


int Rook::valid_move(position start_position, position end_position)
{
    // XOR left or right movement of piece
    return (!(abs(start_position.row - end_position.row)==0) != !(abs(start_position.column - end_position.column)==0));
}


int Pawn::valid_move(position start_position, position end_position)
{
    //if abs(start_position.row )
    return 1;
}