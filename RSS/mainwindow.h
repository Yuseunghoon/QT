#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListView>
#include <QStandardItemModel>

class QNetworkReply;
class QComboBox;
class QNetworkAccessManager;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void openRssFeed();
    void replyFinished(QNetworkReply *);
    void ListViewDoubleClicked(const QModelIndex &index);
private:
    QComboBox *combo;
    QNetworkAccessManager *manager;
    QNetworkReply *reply;
    QListView *tv;
    QStandardItemModel *model;
};

class ListView:public QListView
{
    Q_OBJECT

protected:
    void keyPressEvent(QKeyEvent *event);
};


#endif // MAINWINDOW_H
