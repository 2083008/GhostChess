#include "mainwindow.h"

Window::Window() : plot( QString("Example Plot") )
{
    // set up the thermometer
    thermo.setFillBrush( QBrush(Qt::red) );
    thermo.setRange(0, 20);
    thermo.show();
}