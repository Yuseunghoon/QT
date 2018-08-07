#include "mainwindow.h"
#include "saveurls.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent)
{

    QLibrary lib("SaveUrls");
    if(!lib.isLoaded()) lib.load();
    SaveUrls *saveUrl = (SaveUrls*)lib.resolve("SaveUrls");
    QStringList urlList = saveUrl->load();
    for(int i=0;i<urlList.count();i++)
        combo->addItem(urlList.at(i));
    if(lib.isLoaded()) lib.unload();

    if(urlList.count()==0)
        combo->addItem("http://rss.joins_news_list.xml");
}

MainWindow::~MainWindow()
{
    QLibrary lib("SaveUrls");
    if(!lib.isLoaded()) lib.load();
    SaveUrls *saveUrl=(SaveUrls*)lib.resolve("SaveUrls");
    QStringList urlList;
    for(int i=0;i<combo->count();i++)
        urlList.append(combo->itemText(i));
    saveUrl->save(urlList);
    if(lib.isLoaded()) lib.unload();
}
