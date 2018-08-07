#include "qteditor.h"
#include <QApplication>
#include <QtWidgets>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Qteditor w;

    w.show();

    return a.exec();
}
