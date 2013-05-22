#include "signin.h"
#include "ui_signin.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QtSql/QPSQLDriver>
#include <QSqlRecord>
#include <QCryptographicHash>
#include <QDebug>

signin::signin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::signin)
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
    ui->lineEdit_3->setStyleSheet(ordinaryLineEditStyle);
    ui->lineEdit_4->setStyleSheet(ordinaryLineEditStyle);
    ui->lineEdit_5->setStyleSheet(ordinaryLineEditStyle);
    ui->lineEdit_6->setStyleSheet(ordinaryLineEditStyle);
    ui->lineEdit_7->setStyleSheet(ordinaryLineEditStyle);
    ui->lineEdit_8->setStyleSheet(ordinaryLineEditStyle);
    ui->pushButton->setStyleSheet(ordinaryButtonStyle);
    ui->pushButton_2->setStyleSheet(ordinaryButtonStyle);
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(auth()));
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(reg()));
}

void signin::auth()
{
    if (isSuccess(ui->lineEdit_7->text(),ui->lineEdit_8->text()))
    {
        this->hide();
        QSqlQuery query = db.exec("SELECT id, name, surname, birth, email FROM usr WHERE email = '"+ ui->lineEdit_7->text() +"';");
        query.next();
        w->session.insert("id",query.record().value("id"));
        w->session.insert("name",query.record().value("name"));
        w->session.insert("surname",query.record().value("surname"));
        w->session.insert("birth",query.record().value("birth"));
        w->session.insert("email",ui->lineEdit_7->text());

        emit w->sessionChanged();

        w->show();
    }
    else
        QMessageBox::warning(this,QString::fromUtf8("Ошибка"),QString::fromUtf8("Не верно введен логин или пароль"));
}

void signin::reg()
{
    if (isSuccess(ui->lineEdit_3->text(),ui->lineEdit_4->text(),ui->dateEdit->text(),ui->lineEdit_5->text(),ui->lineEdit_6->text()))
    {
        ui->lineEdit_7->setText(ui->lineEdit_5->text());
        ui->lineEdit_8->setText(ui->lineEdit_6->text());
        auth();
    }
    else
        QMessageBox::warning(this,QString::fromUtf8("Ошибка"),QString::fromUtf8("Возникли проблемы при регистрации"));
}

void signin::getDb(QSqlDatabase db)
{
    this->db = db;
}

void signin::getMainWindow(MainWindow * w)
{
    this->w = w;
}

bool signin::isSuccess(QString email, QString pass)
{
    if (db.open())
    {
        QSqlQuery query = db.exec("SELECT secret FROM usr WHERE email = '"+ email +"';");
        while (query.next())
            if (query.record().value("secret") == QString(QCryptographicHash::hash(QString(pass+email).toUtf8(), QCryptographicHash::Md5).toHex()))
                return true;
    }
    db.close();
    return false;
}

bool signin::isSuccess(QString name, QString surname, QString birth, QString email,QString pass)
{
    if (db.open())
    {
        QSqlQuery * query = new QSqlQuery(db);
        query->prepare("INSERT INTO usr (name, surname, birth, email, secret) VALUES (?,?,?,?,?);");
        query->addBindValue(name);
        query->addBindValue(surname);
        query->addBindValue(birth);
        query->addBindValue(email);
        query->addBindValue(QString(QCryptographicHash::hash(QString(pass+email).toUtf8(), QCryptographicHash::Md5).toHex()));
        return query->exec();
    }
}

signin::~signin()
{
    delete ui;
}
