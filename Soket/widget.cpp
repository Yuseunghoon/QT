#include "widget.h"
#include <QtGui>
#include <QtNetwork>
#include <QtWidgets>
#define BLOCK_SIZE 1024

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    infoLabel = new QLabel(this);
    QPushButton *quitButton = new QPushButton("Quit",this);
    tcpServer = new QTcpServer(this);
    if(!tcpServer->listen()){
        QMessageBox::critical(this,tr("Echo Server"),\
                              tr("Unable to start the server: %1.")\
                              .arg(tcpServer->errorString()));
        close();
        return;
    }

    infoLabel->setText(tr("The server is running on port %1.").arg(tcpServer->serverPort()));
    connect(quitButton,SIGNAL(clicked()),qApp,SLOT(quit()));
    connect(tcpServer,SIGNAL(newConnection()),SLOT(echo()));

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addStretch(1);
    buttonLayout->addWidget(quitButton);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(infoLabel);
    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);

    setWindowTitle(tr("Echo Server"));
}

void Widget::echo()
{
    QTcpSocket *clientConnection = tcpServer->nextPendingConnection();
    connect(clientConnection, SIGNAL(disconnected()),clientConnection,SLOT(deleteLater()));
    connect(clientConnection,SIGNAL(readyRead()),SLOT(readData()));
    infoLabel->setText("new connection is established..");
}

void Widget::readData()
{
    QTcpSocket *clientConnection = (QTcpSocket *)sender();
    if(clientConnection->bytesAvailable()>BLOCK_SIZE)return;
    QByteArray bytearray= clientConnection->read(BLOCK_SIZE);
    clientConnection->write(bytearray);
    infoLabel->setText(QString(bytearray));
}

Widget::~Widget()
{

}
