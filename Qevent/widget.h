#ifndef WIDGET_H
#define WIDGET_H

#include <QLabel>

class Widget : public QLabel
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();
protected:
    void moveEvent(QMoveEvent *);
    void closeEvent(QCloseEvent *);
};

#endif // WIDGET_H
