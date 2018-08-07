#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class QLabel;
class QPushButton;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();
private:
    QLabel* label;
    QPushButton *button[9];

public slots:
    void action();
    void check();
};

#endif // WIDGET_H
