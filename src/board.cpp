#include <string>
#include "board.hpp"
#include <iostream>
#include <QCoreApplication>
#include "main.h"

//init the board
Board::Board(QWidget* pwindow)
{
    QString assets_path = QCoreApplication::applicationDirPath() + "/src/assets/";
    std::vector< std::vector <ChessPiece*>> chessBoard;
    chessBoard.resize(8,std::vector<ChessPiece*>(8));

    for(int i = 0; i < 8;i++){
        Pawn* tmp = new Pawn(WHITE_,position{i,1},pwindow,assets_path);
        tmp->set_image(assets_path);
        chessBoard[i][1] = tmp;
    }

    for(int i = 0; i < 8;i++){
        Pawn* tmp = new Pawn(BLACK_,position{i,6},pwindow,assets_path);
        tmp->set_image(assets_path);
        chessBoard[i][6] = tmp;
    }

    //rooks
    Rook* rook = new Rook(WHITE_,position{0,0},pwindow,assets_path);
    rook->set_image(assets_path);
    chessBoard[0][0] = rook;
    Rook* rook1 = new Rook(WHITE_,position{7,0},pwindow,assets_path);
    rook1->set_image(assets_path);
    chessBoard[7][0] = rook1;
    Rook* rookb = new Rook(BLACK_,position{0,7},pwindow,assets_path);
    rookb->set_image(assets_path);
    chessBoard[0][7] = rookb;
    Rook* rookb1 = new Rook(BLACK_,position{7,7},pwindow,assets_path);
    rookb1->set_image(assets_path);
    chessBoard[7][7] = rookb1;

    // Knights
    Knight* knight = new Knight(WHITE_,position{1,0},pwindow,assets_path);
    knight->set_image(assets_path);
    chessBoard[1][0] = knight;
    Knight* knight1 = new Knight(WHITE_,position{6,0},pwindow,assets_path);
    knight1->set_image(assets_path);
    chessBoard[6][0] = knight1;
    Knight* knightb = new Knight(BLACK_,position{1,7},pwindow,assets_path);
    knightb->set_image(assets_path);
    chessBoard[1][7] = knightb;
    Knight* knightb1 = new Knight(BLACK_,position{6,7},pwindow,assets_path);
    knightb1->set_image(assets_path);
    chessBoard[6][7] = knightb1;


    Bishop* bish = new Bishop(WHITE_,position{2,0},pwindow,assets_path);
    bish->set_image(assets_path);
    chessBoard[2][0] = bish;
     Bishop* bish1 = new Bishop(WHITE_,position{5,0},pwindow,assets_path);
    bish1->set_image(assets_path);
    chessBoard[5][0] = bish1;
     Bishop* bishb = new Bishop(BLACK_,position{2,7},pwindow,assets_path);
    bishb->set_image(assets_path);
    chessBoard[2][7] = bishb;
     Bishop* bishb1 = new Bishop(BLACK_,position{5,7},pwindow,assets_path);
    bishb1->set_image(assets_path);
    chessBoard[5][7] = bishb1;

    Queen* queen = new Queen(WHITE_,position{3,0},pwindow,assets_path);
    queen->set_image(assets_path);
    chessBoard[3][0] = queen;
    Queen* queenb = new Queen(BLACK_,position{3,7},pwindow,assets_path);
    queenb->set_image(assets_path);
    chessBoard[3][7] = queenb;

    King* king = new King(WHITE_,position{4,0},pwindow,assets_path);
    king->set_image(assets_path);
    chessBoard[4][0] = king;
    King* kingb = new King(BLACK_,position{4,7},pwindow,assets_path);
    kingb->set_image(assets_path);
    chessBoard[4][7] = kingb;

    this->chessBoard = chessBoard;

}

char Board::get_position(int row, int col)
{
    return board[col][row];
}

// eg e2e4
void Board::move_piece(std::string move)
{
    system("src/main.py test");
    move_history.append(move);
    move_history.append(" ");
    //move_box->append(QString::fromStdString(move));

    int tempy_start = move[1] - '0' -1;
    int tempy_end = move[3] - '0' -1;
    this->move(position{charToInt(move[0]),tempy_start},
                position{charToInt(move[2]),tempy_end});
    
    const char* cmoves = move_history.c_str();
    std::cout << "Move List -> " << cmoves << std::endl;
    //runEngine(cmoves);
}

void Board::runEngine(const char* moves)
{
    char setup[100] = "position startpos moves ";
    const char *argse[4] = {"uci", strcat(setup, moves), "isready", "go"};
    
    //silence cout from the engine
    std::cout.setstate(std::ios_base::badbit); 
    // Run the engine
    UCI::loop(4, argse);
    Search::clear(); // Join the best move search threads

    std::cout.clear(); // reenable cout
    std::cout << "Engines Move -> "<< best_move_buffer << std::endl;

}

int Board::move(position startpos, position endpos)
{
    ChessPiece* piece = this->chessBoard[startpos.row][startpos.column];
    
    // != NULL then There is a piece to be taken
    if (this->chessBoard[endpos.row][endpos.column] != NULL) {
        ChessPiece* end_piece = this->chessBoard[endpos.row][endpos.column];
        end_piece->piece_image->~QLabel(); // free the area at
    }

    // move piece to new position
    piece->piece_image->setGeometry(X_OFFSET + IMAGE_SIZE*endpos.row,Y_OFFSET-IMAGE_SIZE*endpos.column, IMAGE_SIZE,IMAGE_SIZE);
 
    //NULL since the piece at this position has been moved
    this->chessBoard[startpos.row][startpos.column] = NULL;
    this->chessBoard[endpos.row][endpos.column] = piece;

    //this->chessBoard[startpos.row][startpos.column] = piece
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

int Board::charToInt(char val)
{
    int tmp = val;
    return tmp-97; // 97 to get a = 0, b = 1 etc..
}