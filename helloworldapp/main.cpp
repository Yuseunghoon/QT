#include "widget.h"
#include <QApplication>
#include <QPushButton>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Widget w;
    w.show();

    //QPushButton *quit = new QPushButton("Quit", 0);
    //quit->resize(75, 35);
    //quit->show();
    //QObject::connect(quit, SIGNAL(clicked()), &a, SLOT(quit()));
    return a.exec();
}
