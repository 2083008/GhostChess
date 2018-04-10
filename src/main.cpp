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

//buffer that will be updated by the chess engine
std::string best_move_buffer;
// buffer to store move history of the game
std::string move_history;

void stockfishInit();
// returns a=1 b=2...
int charToInt(char val);
void parse_input(Board* pboard, QTextEdit* move_box);
void runEngine(const char* moves);

int main(int argc, char **argv)
{

    // Initialise the Stockfish chess engine
    stockfishInit();

    std::cout << "GhostChess V_0.1" << std::endl;

    QApplication myapp(argc, argv);
    // TODO put this in a class
    QWidget window;
    QWidget* pwindow = &window;
    window.setFixedSize(800, 500);
    window.setWindowTitle("GhostChess");
    QString assets_path = QCoreApplication::applicationDirPath() + "/src/assets/";
    QLabel *board = new QLabel(&window);
    QPixmap pix(assets_path + "chess_board.png");
    board->setPixmap(pix);
    
    Board* test = new Board(pwindow);

    QLabel* button_label = new QLabel("Select difficulty:",&window);
    button_label->setGeometry(QRect(QPoint(500, 0),QSize(300, 50)));
    QRadioButton* easy_button = new QRadioButton("Easy", &window);
    // set size and location of the button
    easy_button->setGeometry(QRect(QPoint(500, 50),QSize(150, 50)));
    QRadioButton* medium_button = new QRadioButton("Medium", &window);
    // set size and location of the button
    medium_button->setGeometry(QRect(QPoint(500, 100),QSize(150, 50)));
    QRadioButton* hard_button = new QRadioButton("Hard", &window);
    // set size and location of the button
    hard_button->setGeometry(QRect(QPoint(500, 150),QSize(150, 50)));

    QTextEdit* move_box = new QTextEdit(&window);
    move_box->setGeometry(QRect(QPoint(500, 225),QSize(300, 200)));

    window.show();
    std::thread t1 = std::thread(parse_input, test,move_box);
    return myapp.exec();
    
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