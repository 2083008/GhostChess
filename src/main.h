#ifndef MAIN_H
#define MAIN_H

#include "Stockfish/src/bitboard.h"
#include "Stockfish/src/position.h"
#include "Stockfish/src/search.h"
#include "Stockfish/src/thread.h"
#include "Stockfish/src/tt.h"
#include "Stockfish/src/uci.h"
#include "Stockfish/src/syzygy/tbprobe.h"
#include <pthread.h>
#include <cstring>

#include <iostream>
#include <list>
#include <string>
#include <unistd.h>
#include "board.hpp"
#include "chess_piece.hpp"
#include <unistd.h>
#include <vector>
#include <thread>

// QT includes
#include <QApplication>
#include <QPushButton>
#include <QPixmap>
#include <QLabel>
#include <QDebug>


extern std::string best_move_buffer;

#endif