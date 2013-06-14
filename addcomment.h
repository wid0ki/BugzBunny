#ifndef ADDCOMMENT_H
#define ADDCOMMENT_H

#include <QDialog>
#include <QtSql/QPSQLDriver>
#include <QtSql/qsqldatabase.h>

namespace Ui {
class addComment;
}

class addComment : public QDialog
{
    Q_OBJECT
    
public:
    explicit addComment(QWidget *parent = 0);
    void getDb(QSqlDatabase);
    ~addComment();
    
private:
    Ui::addComment *ui;
    QSqlDatabase db;
    QString ordinaryButtonStyle;
    QString ordinaryLineEditStyle;
    QVariantMap session;

public slots:
    void getSessionEmail(QVariantMap);
};

#endif // ADDCOMMENT_H
