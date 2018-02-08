#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H

enum colour {
    WHITE,
    BLACK
};

struct position
{
    int row;
    int column;
};

class ChessPiece
{
public:
    colour piece_colour;
    ChessPiece(colour piece_colour);
    // returns 1 if valid and 0 if invalid
    int valid_move(position start_position, position end_position);

};

class Knight : public ChessPiece
{
public:
    using ChessPiece::ChessPiece;
    int valid_move(position start_position, position end_position);

};

class King : public ChessPiece
{
public:
    using ChessPiece::ChessPiece;
    int valid_move(position start_position, position end_position);
};


#endif