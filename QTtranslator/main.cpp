#include "widget.h"
#include <QApplication>
#include <QtWidgets>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QTranslator translator;

    translator.load("hello_ko");
    app.installTranslator(&translator);

    QPushButton hello(QObject::tr("Hello world"));
    hello.resize(100,30);
    hello.show();

    return app.exec();
}
