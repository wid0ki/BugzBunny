#ifndef SIGNIN_H
#define SIGNIN_H

#include <QDialog>
#include <QtSql/QPSQLDriver>
#include <QtSql/qsqldatabase.h>
#include "mainwindow.h"

namespace Ui {
class signin;
}

class signin : public QDialog
{
    Q_OBJECT
    
public:
    explicit signin(QWidget *parent = 0);
    bool isSuccess(QString, QString);
    bool isSuccess(QString, QString, QString, QString,QString);
    QString ordinaryLineEditStyle;
    QString ordinaryButtonStyle;
    void getDb(QSqlDatabase);
    void getMainWindow(MainWindow*);
    ~signin();
    
private:
    Ui::signin *ui;
    QSqlDatabase db;
    MainWindow * w;

private slots:
    void auth();
    void reg();
};

#endif // SIGNIN_H
