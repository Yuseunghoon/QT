#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class QRadioButton;
class QButtonGroup;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

private:
    QRadioButton *radioButton[4];
    QButtonGroup *buttonGroup;
};

#endif // WIDGET_H
