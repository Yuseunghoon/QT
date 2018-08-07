#include "widget.h"
#include <QLabel>
#include <QCloseEvent>

Widget::Widget(QWidget *parent)
    : QLabel(parent)
{
    setText("Hello World");
    resize(100, 30);
}

void Widget::moveEvent(QMoveEvent *)
{
    setText(QString("X:%1,Y:%2").arg(pos().x()).arg(pos().y()));
}

void Widget::closeEvent(QCloseEvent *event){
    event->ignore();
}
Widget::~Widget()
{

}
