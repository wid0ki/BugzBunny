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
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(auth()));
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(reg()));
}

void signin::auth()
{
    if (isSuccess(ui->lineEdit_7->text(),ui->lineEdit_8->text()))
    {
        MainWindow w;
        w.show();
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

bool signin::isSuccess(QString email, QString pass)
{
    QSqlQuery * query = new QSqlQuery(db);
    query->prepare("SELECT secret FROM usr WHERE email == \'de\';");
    query->exec();
    while (query->next())
    {
        qDebug() << query->record().value(0).toString();
    }
    return false;
}

bool signin::isSuccess(QString name, QString surname, QString birth, QString email,QString pass)
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

signin::~signin()
{
    delete ui;
}
