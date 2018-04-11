#include "main.h"
#include <QMainWindow>

class MainWindow : public QMainWindow
{
Q_OBJECT
public:
// default constructor
    explicit MainWindow();
    QWidget* window;
    QTextEdit *move_entry;
    QTextEdit *move_box;
    Board *chessBoard;
    
    void setBoard(Board* chessBoard);

    
    
private slots:
    void confirm();

private:
    QLabel *board;
    
protected:
// a graphical thermometer
    //QwtThermo thermo;
};