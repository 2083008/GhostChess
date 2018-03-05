#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H

enum colour_ {
    WHITE_,
    BLACK_
};

struct position
{
    int row;
    int column;
};

class ChessPiece
{
public:
    colour_ piece_colour;
    ChessPiece(colour_ piece_colour);
    // returns 1 if valid and 0 if invalid
    virtual int valid_move(position start_position, position end_position) =0;

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

class Bishop : public ChessPiece
{
public:
    using ChessPiece::ChessPiece;
    int valid_move(position start_position, position end_position);
};

class Rook : public ChessPiece
{
public:
    using ChessPiece::ChessPiece;
    int valid_move(position start_position, position end_position);
};

class Pawn : public ChessPiece
{
public:
    using ChessPiece::ChessPiece;
    int valid_move(position start_position, position end_position);
};

class Queen : public ChessPiece
{
public:
    using ChessPiece::ChessPiece;
    int valid_move(position start_position, position end_position);
};


#endif