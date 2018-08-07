#include "widget.h"
#include <QApplication>
#include <QLineEdit>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Widget w;
    w.show();
/*
    QLineEdit *lineEdit = new QLineEdit();
    //lineEdit->setEchoMode(QLineEdit::Password);
    lineEdit->setInputMask("099");
    lineEdit->setPlaceholderText("input the number");
    lineEdit->show();
*/
    return a.exec();
}
