#include "addcomment.h"
#include "ui_addcomment.h"

addComment::addComment(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addComment)
{
    ui->setupUi(this);
    ordinaryButtonStyle = QString(
                "QPushButton {"
                     "background-color: black;"
                     "text-align: center;"
                     "border-radius: 5px;"
                     "color: white;"
                     "border: solid;"
                 "}"
                 "QPushButton:hover {"
                     "background-color: black;"
                     "border-radius: 5px;"
                     "background-repeat: repeat;"
                     "color: white;"
                 "}"
                 "QPushButton:pressed {"
                     "background-color: black;"
                     "border-radius: 5px;"
                     "background-repeat: repeat;"
                     "color: white;"
                 "}");
    ordinaryLineEditStyle = QString (
                "QLineEdit {"
                            "border-radius: 5px;"
                            "border: solid;"
                            "}");
    ui->pushButton_2->setStyleSheet(ordinaryButtonStyle);
    ui->label->setText("Создание комментария");
    ui->label->setStyleSheet(
                "QLabel {"
                "color: white;"
                "text-align: center;"
                "}");
    ui->frame->setStyleSheet(
                "QFrame {"
                 "background-color: black; "
                 "}");
}

void addComment::getSessionEmail(QVariantMap session)
{
    this->session = session;
}

void addComment::getDb(QSqlDatabase db)
{
    this->db = db;
}

addComment::~addComment()
{
    delete ui;
}
