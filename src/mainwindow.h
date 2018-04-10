#include "main.h"

class Window : public QWidget
{
Q_OBJECT
public:
// default constructor
    Window();
private:
protected:
// a graphical thermometer
    QwtThermo thermo;
}  