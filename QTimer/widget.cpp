#include "widget.h"
#include <QTimer>
#include <QTime>

LabelClock::LabelClock(QWidget *parent)
    : QLabel(parent)
{
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),SLOT(clockTimer()));
    timer->start(1000);
    resize(90,40);

}

void LabelClock::clockTimer()
{
    setText(QTime::currentTime().toString());
}

LabelClock::~LabelClock()
{

}
