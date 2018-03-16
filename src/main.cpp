#include "main.h"

char board[8][8];

namespace PSQT
{
void init();
}

void setUpPawn(QWidget window, QString pname, QString asset_path);
void stockfishInit();

int main(int argc, char **argv)
{

    // Initialise the Stockfish chess engine
    stockfishInit();

    std::cout << "GhostChess V_0.1" << std::endl;

    Board test;
    // Setup engine arguments, moves holds the moves, therefore state of board
    const char *moves = " e2e4 d7d5 e4e5 d5d4";
    char setup[100] = "position startpos moves";
    const char *argse[4] = {"uci", strcat(setup, moves), "isready", "go"};

    // Run the engine
    UCI::loop(4, argse);

    QApplication myapp(argc, argv);

    QWidget window;
    window.setFixedSize(800, 500);
    QString assets_path = QCoreApplication::applicationDirPath() + "/src/assets/";

    QLabel *board = new QLabel("Hello world", &window);
    //button->setGeometry(10, 10, 200, 200);
    QPixmap pix(assets_path + "chess_board.png");
    board->setPixmap(pix);

    //setUpPawn(window, "p1", assets_path);
    window.show();

    return myapp.exec();
}
void stockfishInit()
{
    //std::cout << engine_info() << std::endl;
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
}
/*
void setUpPawn(QWidget window, QString pname, QString assets_path) {
  
  QLabel *pawn = new QLabel(pname, &window);
  QPixmap pixp(assets_path + "pawn_white.png");
  pawn->setPixmap(pixp);
  pawn->setGeometry(10,320,50,80); //x1,y1

} */