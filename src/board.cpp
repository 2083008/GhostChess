#include <string>
#include "board.hpp"
#include <iostream>
#include <QCoreApplication>


//init the board
Board::Board(QWidget* pwindow)
{
    QString assets_path = QCoreApplication::applicationDirPath() + "/src/assets/";
    std::vector< std::vector <ChessPiece*>> chessBoard;
    chessBoard.resize(8,std::vector<ChessPiece*>(8));
    for(int i = 0; i < 8;i++){
        Pawn* tmp = new Pawn(WHITE_, X_OFFSET, Y_OFFSET);
        tmp->piece_image = new QLabel(pwindow);
        tmp->piece_image->setGeometry(X_OFFSET + i*IMAGE_SIZE,Y_OFFSET-IMAGE_SIZE, IMAGE_SIZE,IMAGE_SIZE);
        QPixmap pixk(assets_path + "pawn_white.png");
        tmp->piece_image->setPixmap(pixk);
        chessBoard[1][i] = tmp;
    }

    for(int i = 0; i < 8;i++){
        Pawn* tmp = new Pawn(WHITE_, X_OFFSET, Y_OFFSET);
        tmp->piece_image = new QLabel(pwindow);
        tmp->piece_image->setGeometry(X_OFFSET + i*IMAGE_SIZE,Y_OFFSET-IMAGE_SIZE-5*IMAGE_SIZE, IMAGE_SIZE,IMAGE_SIZE);
        QPixmap pixk(assets_path + "pawn_black.png");
        tmp->piece_image->setPixmap(pixk);
        chessBoard[2][i] = tmp;
    }

    Rook* tmp = new Rook(WHITE_, X_OFFSET, Y_OFFSET);
    tmp->piece_image = new QLabel(pwindow);
    tmp->piece_image->setGeometry(X_OFFSET,Y_OFFSET, IMAGE_SIZE,IMAGE_SIZE);
    QPixmap pixk(assets_path + "rook_white.png");
    tmp->piece_image->setPixmap(pixk);
    chessBoard[0][0] = tmp;
    //p.reserve(8);
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