#ifndef BREAKOUT_H
#define BREAKOUT_H

#include <QWidget>


class QLabel;

class Breakout : public QWidget
{
    Q_OBJECT

private:
    static const int NO_OF_BRICKS = 30;

    QLabel *ball;
    QLabel *paddle;
    QLabel *bricks[NO_OF_BRICKS];

public:
    Breakout(QWidget *parent = 0);
    ~Breakout();
};

#endif // BREAKOUT_H
