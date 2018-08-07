#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QTcpServer>
#include <QTcpSocket>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();
private slots:
    void echo();
    void readData();
private:
    QLabel *infoLabel;
    QTcpServer *tcpServer;
};

#endif // WIDGET_H
