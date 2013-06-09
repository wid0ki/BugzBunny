#ifndef PROJECTVIEWER_H
#define PROJECTVIEWER_H

#include <QDialog>
#include <QtSql/QPSQLDriver>
#include <QtSql/qsqldatabase.h>

namespace Ui {
class projectViewer;
}

class projectViewer : public QDialog
{
    Q_OBJECT
    
public:
    explicit projectViewer(QWidget *parent = 0);
    void getDb(QSqlDatabase);
    QSqlDatabase db;
    ~projectViewer();
    
private:
    Ui::projectViewer *ui;
    QString ordinaryLineEditStyle;
    QString ordinaryButtonStyle;
};

#endif // PROJECTVIEWER_H
