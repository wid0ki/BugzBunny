#include "mainwindow.h"
#include "signin.h"
#include <QApplication>
#include <QDebug>
#include <QtSql/QPSQLDriver>
#include <QtSql/qsqldatabase.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
//    w.show();
    w.hide();

    signin authorization;
    authorization.show();

    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL", "postgres");
    db.setHostName("localhost");
    db.setDatabaseName("postgres");
    db.setUserName("postgres");
    db.setPassword("12345");
    w.getDb(db);
    authorization.getDb(db);
    authorization.getMainWindow(&w);

    
    return a.exec();
}
