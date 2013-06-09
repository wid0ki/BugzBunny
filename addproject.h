#ifndef ADDPROJECT_H
#define ADDPROJECT_H

#include <QDialog>
#include <QtSql/QPSQLDriver>
#include <QtSql/qsqldatabase.h>

namespace Ui {
class addproject;
}

class addproject : public QDialog
{
    Q_OBJECT
    
public:
    explicit addproject(QWidget *parent = 0);
    void getDb(QSqlDatabase);
    ~addproject();
    
private:
    Ui::addproject *ui;
    QSqlDatabase db;
    QString ordinaryButtonStyle;
    QString ordinaryLineEditStyle;
    QVariantMap session;

public slots:
    void createProject();
    void cancel();
    void loadUsr();
    void loadProject();
    void getSessionEmail(QVariantMap);
    int getUserId(QVariantMap);
    int getProjectId(QString);

};

#endif // ADDPROJECT_H
