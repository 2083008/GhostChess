#include "chess_piece.hpp"
#include <cmath>
#include <stdlib.h>     /* abs */
#include <stdio.h>
#include <iostream>






ChessPiece::ChessPiece(colour_ col, position pos, QWidget* pwindow, QString path)
{
    this->piece_colour = col;
    this->pos = pos;
    this->piece_image = new QLabel(pwindow);
    this->piece_image->setGeometry(X_OFFSET + IMAGE_SIZE*pos.row,Y_OFFSET-IMAGE_SIZE*pos.column, IMAGE_SIZE,IMAGE_SIZE);
    
    

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

void Rook::set_image(QString path)
{
    QString piece_token;
    if (this->piece_colour == BLACK_) {
        piece_token = "rook_black";
    } else {
        piece_token = "rook_white";
    }
    QPixmap pixk(path + piece_token);
    this->piece_image->setPixmap(pixk);
}


void Pawn::set_image(QString path)
{
    QString piece_token;
    if (this->piece_colour == BLACK_) {
        piece_token = "pawn_black";
    } else {
        piece_token = "pawn_white";
    }
    QPixmap pixk(path + piece_token);
    this->piece_image->setPixmap(pixk);
}

int Pawn::valid_move(position start_position, position end_position)
{
    //if abs(start_position.row )
    return 1;
}