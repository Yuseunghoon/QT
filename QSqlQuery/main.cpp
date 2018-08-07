#include "widget.h"
#include <QApplication>
#include <QTableView>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQueryModel>
#include <QSqlQuery>

static bool createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    //db.setDatabaseName(":memory:");
    db.setDatabaseName("data.db");
    if(!db.open()) return false;

    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS person(id INTERGER Primary Key,"
               "firstname VARCHAR(20) NOT NULL, lastname VARCHAR(20));");
    query.exec("INSERT INTO person VALUES(101, 'Yongsu', 'Kang');");
    query.exec("INSERT INTO person(firstname, lastname) VALUES('Soomi', 'Kim')");
    query.exec("INSERT INTO person(firstname, lastname) VALUES"
               "('Hanmi','Lee'),('YoungJin','Suh'),('YoungHwa','Ryu');");
    return true;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    if(!createConnection()) return 1;

    QSqlQueryModel Querymodel;
    Querymodel.setQuery("select * from person");
    Querymodel.setHeaderData(0,Qt::Horizontal, QObject::tr("ID"));
    Querymodel.setHeaderData(1,Qt::Horizontal, QObject::tr("First name"));
    Querymodel.setHeaderData(2,Qt::Horizontal, QObject::tr("Last name"));

    QTableView *tableview = new QTableView;
    tableview->setModel(&Querymodel);
    tableview->setWindowTitle(QObject::tr("Query Model"));
    tableview->show();

    return a.exec();
}
