#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlQuery>
#include <QSqlError>
#include <QtSql/QPSQLDriver>
#include <QSqlRecord>
#include <QCryptographicHash>
#include <QVariantMap>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    QString ordinaryButtonStyle;
    QString ordinaryLineEditStyle;
    QString ordinaryLeftMenuButtonStyle;
    QVariantMap session;
    void getDb(QSqlDatabase);
    QSqlDatabase db;
    QList<QVariantMap> model;
    int rowCount;
    ~MainWindow();

private:
    Ui::MainWindow *ui;

signals:
    void sessionChanged();

private slots:
    void drawProfile();
    void drawComment();
    void drawTask();
    void drawProject();
    void drawGroup();
    void hideEverything(int);
    void unDownEverything(int);
    void saveProfile();
    void savePass();
    void projectOpen();
    void myProjects();
    void allProjects();
    void allTasks();
    void myTasks();
    void allGroups();
    void myGroups();
    void allComments();
    void myComments();
    int getUserId();
    void exit();
    void manageLeftRadioButton();
    void manageRightRadioButton();
    void MVC();
};

#endif // MAINWINDOW_H
