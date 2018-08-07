#include "widget.h"

#include <QPushButton>
#include <QApplication>
#include <QLabel>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QString>
#include <QDebug>

int turn=0;
int count=0;

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    label = new QLabel("who's winner", this);
    label -> resize(100, 35);
    label -> setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    for(int y = 0; y < 3; y++)
        for(int x = 0; x < 3; x++){
            button[x+y*3] = new QPushButton("",this);
            button[x+y*3]->setGeometry(60*x, 60+60*y, 60, 60);
        }

    for(int i = 0; i < 9; i++){
        connect(button[i], SIGNAL(clicked()), SLOT(action()));
    }


}

Widget::~Widget()
{

}

void Widget::action()
{
    if(count<9)
    {
        if(turn==0)
        {
            ((QPushButton*)sender())->setText("O");
            turn=1;
        }
        else if(turn==1)
        {
            ((QPushButton*)sender())->setText("X");
            turn=0;
        }
        ((QPushButton*)sender())->setEnabled(false);
        count++;
    }
    check();
}

void Widget::check()
{
    // -
    for(int y=0;y<3;y++)
    {
        if((QString::compare(button[0+y*3]->text(),button[1+y*3]->text()) == 0)&&
                (QString::compare(button[1+y*3]->text(),button[2+y*3]->text()) == 0))
        {
            if(button[0+y*3]->text().count() != 0)
            {
                label->setText(QString("%1 is win").arg(button[0+y*3]->text()));
                for(int i=0;i<9;i++)
                    button[i]->setEnabled(false);
            }
        }
    }

    qDebug()<<"- is over";

    //l x+y*3   0,3,6

    for(int x=0;x<3;x++)
    {

        if((QString::compare(button[x+0*3]->text(),button[x+1*3]->text()) == 0)&&
                (QString::compare(button[x+1*3]->text(),button[x+2*3]->text()) == 0))
        {
            if(button[x+0*3]->text().count() != 0)
            {
                label->setText(QString("%1 is win").arg(button[x+0*3]->text()));
                for(int i=0;i<9;i++)
                    button[i]->setEnabled(false);
            }
        }
    }

    qDebug()<<"l is over";

    // x  0,4,8| 2,4,6

    if((QString::compare(button[0]->text(),button[4]->text()) == 0)&&
            (QString::compare(button[4]->text(),button[8]->text()) == 0))
    {
        if(button[0]->text().count() != 0)
        {
            label->setText(QString("%1 is win").arg(button[0]->text()));
            for(int i=0;i<9;i++)
                button[i]->setEnabled(false);
        }
    }

    else if((QString::compare(button[2]->text(),button[4]->text()) == 0)&&
            (QString::compare(button[4]->text(),button[6]->text()) == 0))
    {
        if(button[2]->text().count() != 0)
        {
            label->setText(QString("%1 is win").arg(button[2]->text()));
            for(int i=0;i<9;i++)
                button[i]->setEnabled(false);
        }
    }

    qDebug()<<"cross is over";

}
