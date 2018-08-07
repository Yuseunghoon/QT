#include <QCoreApplication>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

void sendRequest();

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    sendRequest();

    return a.exec();
}

void sendRequest()
{
    QEventLoop eventLoop;

    QNetworkAccessManager mgr;
    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)),&eventLoop,SLOT(quit()));

    QNetworkRequest req(QUrl(QString("http://time.jsontest.com/")));
    QNetworkReply *reply = mgr.get(req);
    eventLoop.exec();

    if(reply->error()==QNetworkReply::NoError)
    {
        QString strReply=(QString)reply->readAll();
        qDebug()<<"Time:"<<jsonObj=jsonResponse.object();

    }
}
