#include "widget.h"
#include "thread.h"
#include <QtGui>
#include <QtWidgets>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QLabel *label = new QLabel(this);
    Thread *thread = new Thread(this);

    QPushButton *stopButton=new QPushButton("Stop",this);
    QPushButton *resumeButton=new QPushButton("Resume",this);

    QHBoxLayout *hboxlayout = new QHBoxLayout;
    hboxlayout->addWidget(stopButton);
    hboxlayout->addWidget(resumeButton);

    QVBoxLayout *vboxlayout = new QVBoxLayout(this);
    vboxlayout->addWidget(label);
    vboxlayout->addLayout(hboxlayout);

    connect(stopButton,SIGNAL(clicked()),thread,SLOT(stopThread()));
    connect(resumeButton,SIGNAL(clicked()),thread,SLOT(resumeThread()));
    connect(thread,SIGNAL(setLabel(QString)),label,SLOT(setText(QString)));

    thread->start();
}

Widget::~Widget()
{

}
