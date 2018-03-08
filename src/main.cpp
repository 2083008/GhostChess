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

char board[8][8];

char command[200];

namespace PSQT {
  void init();
}

void update_command(char *new_command);

int main(void) {

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

  //char * argsb[] = {" ","position","startpos", "moves", "e2e4", "d7d5"};
  //UCI::loop(6, argsb);
  //update_command("uci");
  cout << "GLOB COMMAND -> " << endl;

  char * argse[] = {" ", "uci"};
  UCI::loop(2, argse); // GO
  Threads.set(0); // this must come after moves command


  // std::stringstream stream;
  //test.move_piece(1,0, 2,0);

  //test.print_board();

 // test.move_piece(0,0, 2,1);
  //test.print_board();
 // cout<< test.board_to_FEN(BLACK_) << endl;

  //Rook rook1 = Rook(WHITE_);
  //cout << rook1.valid_move(position{7,3},position{1,3}) << endl;
  //cout << rook1.piece_colour << endl;

  return(0);

}


void update_command(char *new_command)
{
    size_t maxlen = strlen(new_command);
    cout << "maxlen -> "<< maxlen << endl;
    strcpy(command, new_command);
}
