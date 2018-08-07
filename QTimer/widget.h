#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>

class QTimer;


class LabelClock:public QLabel
{
    Q_OBJECT

public:
    LabelClock(QWidget *parent = 0);
    ~LabelClock();

public slots:
    void clockTimer();

};

#endif // WIDGET_H
