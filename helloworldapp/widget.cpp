#include <QPushButton>
#include <QApplication>
#include <QLabel>
#include <QGridLayout>
#include <QVBoxLayout>
#include "widget.h"


Widget::Widget(QWidget *parent):QWidget(parent)
{
    const char ButtonChar[16][2] =
    {
        "7", "8", "9", "/",
        "4", "5", "6", "x",
        "1", "2", "3", "-",
        "0", "C", "=", "+"
    };

    label = new QLabel("0", this);
    label -> resize(160, 35);
    label -> setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    QPushButton *button[16];

    for(int y = 0; y < 4; y++)
        for(int x = 0; x < 4; x++){
            button[x+y*4] = new QPushButton(ButtonChar[x+y*4], this);
            button[x+y*4]->setGeometry(42*x, 35+42*y, 40, 40);
        }

    for(int i = 0; i < 16; i++){
        if(i == 14)connect(button[i], SIGNAL(clicked()), SLOT(calculate()));
        else if(i == 12)connect(button[i], SIGNAL(clicked()), SLOT(clear()));
        else if(i == 3||i == 7||i == 11||i == 15)connect(button[i], SIGNAL(clicked()), SLOT(operation()));
        else connect(button[i], SIGNAL(clicked()), SLOT(setNum()));
    }
}
void Widget::setNum()
{
    label->setText(QString::number(label->text().toFloat()*10 +
                                   ((QPushButton*)sender())->text().toFloat()));
}

void Widget::operation()
{
    numberTemp = label->text();
    operate = ((QPushButton*)sender())->text();
    label->setText("0");
}

void Widget::calculate()
{

    float result;
    switch(operate.at(0).toLatin1()){
    case '+':result = numberTemp.toFloat() + label->text().toFloat();break;
    case '-':result = numberTemp.toFloat() - label->text().toFloat();break;
    case 'x':result = numberTemp.toFloat() * label->text().toFloat();break;
    case '/':
        if(label->text().toFloat()){
            result = numberTemp.toFloat() / label->text().toFloat();break;
        } else {
            label->setText("Error : Cannot Divide by Zero");
            result = 0;
        }break;
    }

    label->setText(QString::number(result));
}

void Widget::clear(){
    numberTemp.setNum(0);
    label->setText("0");
}


Widget::~Widget()
{
    delete label;
}

