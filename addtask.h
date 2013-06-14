#ifndef ADDTASK_H
#define ADDTASK_H

#include <QDialog>
#include <QtSql/QPSQLDriver>
#include <QtSql/qsqldatabase.h>

namespace Ui {
class addTask;
}

class addTask : public QDialog
{
    Q_OBJECT
    
public:
    explicit addTask(QWidget *parent = 0);
    void getDb(QSqlDatabase);
    ~addTask();
    
private:
    Ui::addTask *ui;
    QSqlDatabase db;
    QString ordinaryButtonStyle;
    QString ordinaryLineEditStyle;
    QVariantMap session;

public slots:
    void getSessionEmail(QVariantMap);
    void addNewTask();
    void loadUsr();
    void loadProject();
    int getUserId(QVariantMap);
};

#endif // ADDTASK_H
