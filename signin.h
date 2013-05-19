#ifndef SIGNIN_H
#define SIGNIN_H

#include <QDialog>
#include <QtSql/QPSQLDriver>
#include <QtSql/qsqldatabase.h>

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
    void getDb(QSqlDatabase);
    ~signin();
    
private:
    Ui::signin *ui;
    QSqlDatabase db;

private slots:
    void auth();
    void reg();
};

#endif // SIGNIN_H
