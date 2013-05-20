#include "mainwindow.h"
#include "signin.h"
#include <QApplication>
#include <QDebug>
#include <QtSql/QPSQLDriver>
#include <QtSql/qsqldatabase.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    MainWindow w;
//    w.show();

    signin authorization;
    authorization.show();

    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL", "postgres");
    db.setHostName("localhost");
    db.setDatabaseName("postgres");
    db.setUserName("postgres");
    db.setPassword("12345");
    if (!db.open()) qDebug()<<QString::fromUtf8("Отсутствие подключения к БД");
    else authorization.getDb(db);
    
    return a.exec();
}
