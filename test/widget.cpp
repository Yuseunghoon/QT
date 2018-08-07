#include "widget.h"
#include <QHBoxLayout>
#include <QPushButton>
#include <QStackedLayout>
#include <QDial>
#include <QLabel>
#include <QCalendarWidget>
#include <QTextEdit>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{

    QDial* dial = new QDial(this);
    dial->setRange(0,2);

    QLabel *label= new QLabel("Stack 1",this);
    QCalendarWidget *calendarWidget = new QCalendarWidget(this);
    QTextEdit *textEdit = new QTextEdit("Stack 3", this);

    QStackedLayout *stackedLayout = new QStackedLayout();
    stackedLayout->addWidget(label);
    stackedLayout->addWidget(calendarWidget);
    stackedLayout->addWidget(textEdit);

    connect(dial,SIGNAL(valueChanged(int)), stackedLayout, SLOT(setCurrentIndex(int)));
    QHBoxLayout *hBoxLayout = new QHBoxLayout(this);
    hBoxLayout->addWidget(dial);
    hBoxLayout->addLayout(stackedLayout);

    setLayout(hBoxLayout);

/*
    resize(140,110);
    buttonGroup = new QButtonGroup(this);
    for(int i = 0;i<4;i++)
    {
        QString str=QString("RadioButton%1").arg(i+1);
        radioButton[i]=new QRadioButton(str,this);
        radioButton[i]->move(10,10+20*i);
        buttonGroup->addButton(radioButton[i]);
    }

    QPushButton *pushButton1 = new QPushButton();
    pushButton1->setText("Button1");
    QPushButton *pushButton2 = new QPushButton("Button2");
    QPushButton *pushButton3 = new QPushButton("Button3",this);

    QVBoxLayout *vBoxLayout = new QVBoxLayout(this);
    vBoxLayout->setSpacing(6);
    vBoxLayout->addWidget(pushButton1);
    vBoxLayout->addWidget(pushButton2);
    vBoxLayout->addWidget(pushButton3);
*/
    /*
    QHBoxLayout *hBoxLayout = new QHBoxLayout;
    hBoxLayout->setMargin(0);
    hBoxLayout->addWidget(pushButton1);
    hBoxLayout->addWidget(pushButton2);
    hBoxLayout->addWidget(pushButton3);
    setLayout(hBoxLayout);
    */

}

Widget::~Widget()
{

}
