#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H

#include <QLabel>

#define X_OFFSET 12
#define Y_OFFSET 388
#define IMAGE_SIZE 53


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
    position pos;
    ChessPiece(colour_ col, position pos, QWidget* pwindow, QString path);
    //*piece pointer to Qlabel for specific piece
    QLabel *piece_image;
    // returns 1 if valid and 0 if invalid
    virtual int valid_move(position start_position, position end_position) =0;
    virtual void set_image(QString path) =0;
    //virtual int move(int x, int y) =0;

};

class Knight : public ChessPiece
{
public:
    using ChessPiece::ChessPiece;
    int valid_move(position start_position, position end_position);
    void set_image(QString path);

};

class King : public ChessPiece
{
public:
    using ChessPiece::ChessPiece;
    int valid_move(position start_position, position end_position);
    void set_image(QString path);
    int move(int x,int y);
};

class Bishop : public ChessPiece
{
public:
    using ChessPiece::ChessPiece;
    int valid_move(position start_position, position end_position);
    void set_image(QString path);
};

class Rook : public ChessPiece
{
public:
    using ChessPiece::ChessPiece;
    void set_image(QString path);
    int valid_move(position start_position, position end_position);
};

class Pawn : public ChessPiece
{
public:
    using ChessPiece::ChessPiece;
    void set_image(QString path);
    int valid_move(position start_position, position end_position);
};

class Queen : public ChessPiece
{
public:
    using ChessPiece::ChessPiece;
    int valid_move(position start_position, position end_position);
    void set_image(QString path);
};


#endif