#ifndef WIDGET_H
#define WIDGET_H
#include <QWidget>
class QLabel;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

private:
    QLabel* label;
    QString numberTemp;
    QString operate;

public slots:
    void setNum();
    void operation();
    void calculate();
    void clear();
};

#endif // WIDGET_H
