#include "MainWindow.h"
#include "main.h"
MainWindow::MainWindow()
{
    QWidget window;

    this->setFixedSize(975, 465);
    this->setWindowTitle("GhostChess");

    QString assets_path = QCoreApplication::applicationDirPath() + "/src/assets/";
    QLabel *board = new QLabel(this);
    QPixmap pix(assets_path + "chess_board.png");
    board->setPixmap(pix);
    board->setGeometry(QRect(QPoint(0,0),QSize(500,460)));
    QLabel* button_label = new QLabel("Select difficulty:",this);
    button_label->setGeometry(QRect(QPoint(500, 0),QSize(300, 50)));

    //QButtonGroup group;
    QRadioButton* easy_button = new QRadioButton("Easy",this);
    // set size and location of the button
    easy_button->setGeometry(QRect(QPoint(500, 50),QSize(100, 50)));
    QRadioButton* medium_button = new QRadioButton("Medium",this);
    // set size and location of the button
    medium_button->setGeometry(QRect(QPoint(600, 50),QSize(150, 50)));
    QRadioButton* hard_button = new QRadioButton("Hard",this);
    // set size and location of the button
    hard_button->setGeometry(QRect(QPoint(750, 50),QSize(150, 50)));
    //group->addButton(easy_button,0);

    QLabel* entry_label = new QLabel("Enter Move:",this);
    entry_label->setGeometry(QRect(QPoint(500, 100),QSize(300, 50)));
    QTextEdit* move_entry = new QTextEdit(this);
    move_entry->setGeometry(QRect(QPoint(500, 150),QSize(150, 50)));
    this->move_entry = move_entry;
    QPushButton* enter_move_button = new QPushButton("Confirm",this);
    // set size and location of the button
    enter_move_button->setGeometry(QRect(QPoint(650, 150),QSize(150, 50)));
    connect(enter_move_button, &QPushButton::clicked, this, &MainWindow::confirm);

    QTextEdit* move_box = new QTextEdit(this);
    this->move_box = move_box;
    move_box->setGeometry(QRect(QPoint(500, 200),QSize(300, 200)));
    
}

void MainWindow::confirm()
{
    QString move;
    std::string line;
    move = this->move_entry->toPlainText();
    std::cout << move.toStdString() << std::endl;
    this->chessBoard->move_piece(move.toStdString());
    

    this->chessBoard->runEngine(move_history.c_str());
    this->chessBoard->move_piece(best_move_buffer);
    this->move_box->clear();
    this->move_box->append(QString::fromStdString(move_history));
}

void MainWindow::setBoard(Board* chessBoard)
{
    this->chessBoard = chessBoard;
}