#include <iostream>
#include <list>
#include <string>
using namespace std;
#include "board.hpp"
#include "chess_piece.hpp"


//Stockfish Includes [TODO fix relative paths]
#include "Stockfish/src/bitboard.h"
#include "Stockfish/src/position.h"
#include "Stockfish/src/search.h"
#include "Stockfish/src/thread.h"
#include "Stockfish/src/tt.h"
#include "Stockfish/src/uci.h"
#include "Stockfish/src/syzygy/tbprobe.h"
#include <pthread.h>

char board[8][8];

namespace PSQT {
  void init();
}

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
  
  char * argss[] = {" ", "position", "startpos", "moves", "e2e4"};
  UCI::loop(5,argss);
  char * argsb[] = {" ", "go"};
  UCI::loop(2, argsb);

  Threads.set(0);
  
  cout << "GhostChess" << endl;
    Board test;

    // std::stringstream stream;    
    // std::system("./src/Stockfish/stockfish");

    //test.move_piece(1,0, 2,0);
    test.print_board();

    test.move_piece(0,0, 2,1);
    test.print_board();

    Rook rook1 = Rook(WHITE_);
    cout << rook1.valid_move(position{7,3},position{1,3}) << endl;
    cout << rook1.piece_colour << endl;

    return(0);

}
