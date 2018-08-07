#include "widget.h"
#include <QApplication>
#include "pendulumitem.h"
#include "pendulumcontrol.h"
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsView>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QGraphicsView *view=new QGraphicsView;
    QGraphicsScene *scene=new QGraphicsScene(view);
    view->setScene(scene);

    Pendulumitem *pendulum = new Pendulumitem;
    scene->addItem(pendulum);
    PendulumController controller(pendulum);
    view->setRenderHint(QPainter::Antialiasing);
    //view->setSceneRect(-150,-20,300,200);
    view->resize(300,180);
    view->show();

    return a.exec();
}
