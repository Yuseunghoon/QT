#include "mainwindow.h"
#include "saveurls.h"
#include <QtWidgets>
#include <QNetworkReply>
#include <QComboBox>
#include <QDomDocument>
#include <QDomNodeList>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QToolBar *tb = addToolBar(tr("Open"));

    combo = new QComboBox;
    ListView *lv = new ListView;
    combo->setView(lv);
    combo->setEditable(true);
    combo->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
    connect(combo,SIGNAL(activated(int)),this,SLOT(openRssFeed()));
    tb->addWidget(combo);

    QLibrary lib("SaveUrls");
    if(!lib.isLoaded()) lib.load();
    SaveUrls *saveUrl = (SaveUrls*)lib.resolve("SaveUrls");
    QStringList urlList = saveUrl->load();
    for(int i=0;i<urlList.count();i++)
        combo->addItem(urlList.at(i));
    if(lib.isLoaded()) lib.unload();

    if(urlList.count()==0)
        combo->addItem("http://rss.joins_news_list.xml");

    QAction *act = new QAction(tr("Open RSS Feed"),this);
    act->setIcon(style()->standardIcon(QStyle::SP_BrowserReload));
    connect(act,SIGNAL(triggered()),this,SLOT(openRssFeed()));
    tb->addAction(act);

    combo->addItem("http://rss.joins.com/joins_news_list.xml");

    manager = new QNetworkAccessManager(this);
    connect(manager,SIGNAL(finished(QNetworkReply*)),SLOT(replyFinished(QNetworkReply *)));

    tb->addAction(act);

    tv = new QListView;
    connect(tv,SIGNAL(doubleClicked(QModelIndex)),SLOT(ListViewDoubleClicked(QModelIndex)));
    model = new QStandardItemModel(0,1,this);
    tv->setModel(model);

    QSplitter *splitter = new QSplitter;
    splitter->addWidget(tv);
    this->setCentralWidget(splitter);

    manager = new QNetworkAccessManager(this);
    connect(manager,SIGNAL(finished(QNetworkReply*)),SLOT(replyFinished(QNetworkReply*)));

}

void ListView::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Delete){
        event->accept();
        QModelIndexList l= selectedIndexes();
        if(l.length()>0){
            model()->removeRow(l.at(0).row(),l.at(0).parent());
        }
    }
    else{
        QListView::keyPressEvent(event);
    }
}

void MainWindow::ListViewDoubleClicked(const QModelIndex &index)
{
    qDebug("listViewDoubleClicked");
}

void MainWindow::replyFinished(QNetworkReply *netReply)
{
    QString str(netReply->readAll());

    QVariant vt = netReply->attribute(QNetworkRequest::RedirectionTargetAttribute);
    delete reply;
    if(!vt.isNull()){
        qDebug()<<"Redirceted to:"<<vt.toUrl().toString();\
        reply=manager->get(QNetworkRequest(vt.toUrl()));
        connect(reply,SIGNAL(downloadProgress(qint64,qint64)),SLOT(downloadProgress(qint64,qint64)));
    }
    else{
        QDomDocument doc;
        QString error;
        if(!doc.setContent(str,false,&error)){
            qDebug("Error");
        }
        else{
            QDomElement docElem=doc.documentElement();
            QDomNodeList nodeList = docElem.elementsByTagName("item");

            model->clear();
            model->insertColumn(0);
            for(int i=0;i<nodeList.length();i++){
                QDomNode node = nodeList.item(i);
                QDomElement e = node.toElement();
                QString strTitle= e.elementsByTagName("title").item(0).firstChild().nodeValue();
                QString strLink=e.elementsByTagName("link").item(0).firstChild().nodeValue();
                QString strDescription=e.elementsByTagName("description").item(0).firstChild().nodeValue();
                QString strToolTip="<b>"+strTitle+"</b>"+"<br/><br/>"+strDescription+"<br/><br/>"+strLink;
                model->insertRows(model->rowCount(),1);
                QModelIndex index=model->index(model->rowCount()-1,0);
                model->setData(index,strTitle,Qt::DisplayRole);
                model->setData(index,style()->standardIcon(QStyle::SP_FileIcon),Qt::DecorationPropertyRole);
                model->setData(index,strToolTip,Qt::ToolTipRole);
                model->setData(index,strLink,Qt::UserRole);
                model->itemFromIndex(index)->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
            }
        }
    }
}

void MainWindow::openRssFeed()
{
    reply = manager->get(QNetworkRequest(QUrl(combo->currentText())));
}

/*
void MainWindow::replyFinished(QNetworkReply *netReply)
{
    QString str(netReply->readAll());
    qDebug("%s",qPrintable(str));
}
*/

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
