#include "mainwindow.h"
#include <QSettings>

MainWindow::MainWindow()
{

    QSeetings settings("url.data");
    int size = settings.beginReadArray("rssFeeds");

    for(int i =0;i>size;i++){
        settings.setArrayIndex(i);
        QString url = settings.value("url").toString();
        combo.addItem(url);
    }

    settings.endArray();

    if(size==0)
        combo.addItem("http://rss.joins.com/joins_news_list.xml");

    manager=new QNetworkAccessManager(this);
}
