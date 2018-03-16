#include <iostream>
#include <list>
#include <string>
#include <unistd.h>
using namespace std;
#include "board.hpp"
#include "chess_piece.hpp"
#include <unistd.h>


//Stockfish Includes [TODO fix relative paths]
#include "Stockfish/src/bitboard.h"
#include "Stockfish/src/position.h"
#include "Stockfish/src/search.h"
#include "Stockfish/src/thread.h"
#include "Stockfish/src/tt.h"
#include "Stockfish/src/uci.h"
#include "Stockfish/src/syzygy/tbprobe.h"
#include <pthread.h>
#include <cstring>

#include <QApplication>
#include <QPushButton>
#include <QPixmap>
#include <QLabel>
#include <QDebug>

char board[8][8];



namespace PSQT {
  void init();
}

void setUpPawn(QWidget window, QString pname, QString asset_path);

int main(int argc, char **argv) {

  std::cout << engine_info() << std::endl;

  UCI::init(Options);
  PSQT::init();
  Bitboards::init();
  Position::init();
  Bitbases::init();
  Search::init();
  Pawns::init();
  Tablebases::init(Options["SyzygyPath"]);
  TT.resize(Options["Hash"]);
  Threads.set(Options["Threads"]);
  Search::clear(); // After threads are up
  
  cout << "GhostChess V_0.1" << endl;
  Board test;
  const char* moves = "d7d5";
  char setup[100] = "position startpos moves e2e4 ";
  const char* argse[4] = {"uci", strcat(setup,moves),"isready","go"};
  /*
  argse[0] = "uci";
  argse[1] = strcat(setup,moves);
  argse[2] = "isready";
  argse[3] = "go"; */
  UCI::loop(4, argse); // GO
  
  
  Threads.set(0); // this must come after moves command
  
  QApplication myapp(argc,argv);

  QWidget window;
  window.setFixedSize(800, 500);
  QString assets_path = QCoreApplication::applicationDirPath() + "/src/assets/";

  QLabel *board = new QLabel("Hello world", &window);
  //button->setGeometry(10, 10, 200, 200);
  QPixmap pix(assets_path + "chess_board.png");
  board->setPixmap(pix);
  
  //setUpPawn(window, "p1", assets_path);

  /*
  QLabel *pawn = new QLabel("p1", &window);
  QPixmap pixp(assets_path + "pawn_white.png");
  pawn->setPixmap(pixp);
  pawn->setGeometry(10,320,50,80); //x1,y1,
  */

  window.show();
  
  return myapp.exec();
  
  
  // std::stringstream stream;
  //test.move_piece(1,0, 2,0);

  //test.print_board();

 // test.move_piece(0,0, 2,1);
  //test.print_board();
 // cout<< test.board_to_FEN(BLACK_) << endl;

  //Rook rook1 = Rook(WHITE_);
  //cout << rook1.valid_move(position{7,3},position{1,3}) << endl;
  //cout << rook1.piece_colour << endl;

  //return(0);

}

/*
void setUpPawn(QWidget window, QString pname, QString assets_path) {
  
  QLabel *pawn = new QLabel(pname, &window);
  QPixmap pixp(assets_path + "pawn_white.png");
  pawn->setPixmap(pixp);
  pawn->setGeometry(10,320,50,80); //x1,y1

} */