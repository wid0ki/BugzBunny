#ifndef ADDGROUP_H
#define ADDGROUP_H

#include <QDialog>
#include <QtSql/QPSQLDriver>
#include <QtSql/qsqldatabase.h>

namespace Ui {
class addGroup;
}

class addGroup : public QDialog
{
    Q_OBJECT
    
public:
    explicit addGroup(QWidget *parent = 0);
    void getDb(QSqlDatabase);
    ~addGroup();
    
private:
    Ui::addGroup *ui;
    QSqlDatabase db;
    QString ordinaryButtonStyle;
    QString ordinaryLineEditStyle;
    QVariantMap session;

public slots:
    void getSessionEmail(QVariantMap);
    void loadUsr();
    void createGroup();
};

#endif // ADDGROUP_H
