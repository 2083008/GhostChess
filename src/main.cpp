#include "main.h"


char board[8][8];

//constants
//#define X_OFFSET 12
//#define Y_OFFSET 385
//#define IMAGE_SIZE 54

namespace PSQT
{
void init();
}

std::string best_move_buffer;

void stockfishInit();
// returns a=1 b=2...
int charToInt(char val);
void parse_input(Board* pboard);

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
    Search::clear(); // Join the best move search threads
    std::cout <<"BEST MOVE -> "<< best_move_buffer << std::endl;

    QApplication myapp(argc, argv);

    QWidget window;
    QWidget* pwindow = &window;
    window.setFixedSize(800, 500);
    QString assets_path = QCoreApplication::applicationDirPath() + "/src/assets/";
    QLabel *board = new QLabel(&window);
    QPixmap pix(assets_path + "chess_board.png");
    board->setPixmap(pix);

   
    Board* test = new Board(pwindow);
    test->move(position{0,1},position{0,3});
    test->move(position{4,1},position{4,2});
    
    

    window.show();
    std::thread t1 = std::thread(parse_input, test);
    
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

void parse_input(Board* pboard)
{
    for (std::string line; std::getline(std::cin, line);) {
        if(line == "q"){
            return;
        }
        //std::cout << line << std::endl;
        if(line.length()!=4) {
            std::cout << "Invalid input!" << std::endl;
            
        } else {
            int tempy_start = line[1] - '0' -1;
            int tempy_end = line[3] - '0' -1;
            pboard->move(position{charToInt(line[0]),tempy_start},
                        position{charToInt(line[2]),tempy_end});
            //std::cout <<  << std::endl;
        }
    }
}

int charToInt(char val)
{
    int tmp = val;
    return tmp-97; // 97 to get a = 0, b = 1 etc..
}