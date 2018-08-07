#include "widget.h"
#include <QApplication>
#include <QWidget>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsView>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QGraphicsScene *scene = new QGraphicsScene;
    scene->addRect(-10,-10,120,50);
    QGraphicsItem *item= new QGraphicsTextItem("Hello World!");
    scene->addItem(item);

    QGraphicsView *view = new QGraphicsView;
    view->setScene(scene);
    view->show();

    return a.exec();
}
