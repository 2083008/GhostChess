#include "main.h"
#include <vector>

char board[8][8];

//constants
//#define X_OFFSET 12
//#define Y_OFFSET 385
//#define IMAGE_SIZE 54

namespace PSQT
{
void init();
}

void stockfishInit();

int main(int argc, char **argv)
{

    // Initialise the Stockfish chess engine
    stockfishInit();

    std::cout << "GhostChess V_0.1" << std::endl;

    //Board test;
    // Setup engine arguments, moves holds the moves, therefore state of board
    const char *moves = " e2e4 d7d5 e4e5 d5d4";
    char setup[100] = "position startpos moves";
    const char *argse[4] = {"uci", strcat(setup, moves), "isready", "go"};

    // Run the engine
    UCI::loop(4, argse);

    QApplication myapp(argc, argv);

    QWidget window;
    QWidget* pwindow = &window;
    window.setFixedSize(800, 500);
    QString assets_path = QCoreApplication::applicationDirPath() + "/src/assets/";
    QLabel *board = new QLabel(&window);
    QPixmap pix(assets_path + "chess_board.png");
    board->setPixmap(pix);
    
    Board* test = new Board(pwindow);

    std::vector<ChessPiece*> p;
    p.reserve(8);
    std::vector<ChessPiece*> p1;
    p.reserve(8);

    /*
    for(int i = 0; i < 8;i++){
        Pawn* tmp = new Pawn(WHITE_, X_OFFSET, Y_OFFSET);
        tmp->piece_image = new QLabel(&window);
        tmp->piece_image->setGeometry(X_OFFSET + i*IMAGE_SIZE,Y_OFFSET-IMAGE_SIZE, IMAGE_SIZE,IMAGE_SIZE);
        QPixmap pixk(assets_path + "pawn_white.png");
        tmp->piece_image->setPixmap(pixk);
        p.emplace_back(tmp);
    }

    for(int i=0; i <8; i++){
        Pawn* tmp = new Pawn(BLACK_, X_OFFSET, Y_OFFSET);
        tmp->piece_image = new QLabel(&window);
        tmp->piece_image->setGeometry(X_OFFSET + i*IMAGE_SIZE,Y_OFFSET-IMAGE_SIZE-260, IMAGE_SIZE,IMAGE_SIZE);
        QPixmap pixk(assets_path + "pawn_black.png");
        tmp->piece_image->setPixmap(pixk);
        p.emplace_back(tmp);
    }

    p.at(0)->piece_image->setGeometry(X_OFFSET + 3*IMAGE_SIZE,Y_OFFSET-100, IMAGE_SIZE,IMAGE_SIZE);

    */
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