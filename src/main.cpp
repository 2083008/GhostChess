#include "main.h"
#include "MainWindow.h"

char board[8][8];

//constants
//#define X_OFFSET 12
//#define Y_OFFSET 385
//#define IMAGE_SIZE 54

namespace PSQT
{
void init();
}

//buffer that will be updated by the chess engine
std::string best_move_buffer;
// buffer to store move history of the game
std::string move_history;

void stockfishInit();
// returns a=1 b=2...
int charToInt(char val);
void parse_input(Board* pboard, QTextEdit* move_box);
void runEngine(const char* moves);
void on_some_pushButton_clicked();

int main(int argc, char **argv)
{

    // Initialise the Stockfish chess engine
    stockfishInit();

    std::cout << "GhostChess V_0.1" << std::endl;

    QApplication myapp(argc, argv);
    MainWindow mainWin;
    MainWindow* pmainWin = &mainWin;
    Board* test = new Board(pmainWin);
    mainWin.show();

    std::thread t1 = std::thread(parse_input, test,pmainWin->move_box);

    return myapp.exec();   
}

void on_some_pushButton_clicked()
{
    std::cout << "PRESSSED";
}
void runEngine(const char* moves)
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

// function for thread to parse user input for CLI
void parse_input(Board* pboard, QTextEdit* move_box)
{   
    std::cout << "Enter a move in Algebraic Notation (E.g e2e4) or q to quit " << std::endl;
    for (std::string line; std::getline(std::cin, line);) {
        if(line == "q"){
            //std::terminate(); should terminate the thread/join
            return;
        }
        
        if(line.length()!=4) {
            std::cout << "Invalid input!" << std::endl;
            
        } else {
            move_history.append(line);
            move_history.append(" ");
            move_box->append(QString::fromStdString(line));

            int tempy_start = line[1] - '0' -1;
            int tempy_end = line[3] - '0' -1;
            pboard->move(position{charToInt(line[0]),tempy_start},
                        position{charToInt(line[2]),tempy_end});
            
            const char* cmoves = move_history.c_str();
            std::cout << "Move List -> " << cmoves << std::endl;
            runEngine(cmoves);

            // BLACK MOVE
            int tempy_startb = best_move_buffer[1] - '0' -1;
            int tempy_endb = best_move_buffer[3] - '0' -1;
            pboard->move(position{charToInt(best_move_buffer[0]),tempy_startb},
                        position{charToInt(best_move_buffer[2]),tempy_endb});
            move_history += best_move_buffer;
            move_history += " ";
            move_box->append(QString::fromStdString(best_move_buffer));
            
        }
    }
}

int charToInt(char val)
{
    int tmp = val;
    return tmp-97; // 97 to get a = 0, b = 1 etc..
}