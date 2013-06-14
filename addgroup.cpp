#include "addgroup.h"
#include "ui_addgroup.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QDebug>

addGroup::addGroup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addGroup)
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
    ui->pushButton->setStyleSheet(ordinaryButtonStyle);
    ui->lineEdit->setStyleSheet(ordinaryLineEditStyle);
    ui->label->setText("Создание группы");
    ui->label->setStyleSheet(
                "QLabel {"
                "color: white;"
                "text-align: center;"
                "}");
    ui->frame->setStyleSheet(
                "QFrame {"
                 "background-color: black; "
                 "}");
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(createGroup()));
    connect(ui->lineEdit, SIGNAL(editingFinished()), this, SLOT(loadUsr()));
}

void addGroup::createGroup()
{
    QSqlQuery * query = new QSqlQuery(db);
    db.open();
    if (db.open())
    {

        query->prepare("INSERT INTO grp (id, name, id_parent) VALUES (DEFAULT,\'"+ui->lineEdit->text()+"\',1);");
        qDebug()<<"Insert into grp "<<query->exec()<<" "<<query->lastError().text();

//        query->prepare("INSERT INTO usr2grp (id_person, id_group, role) VALUES ("++",")")

    }
    db.close();
    this->deleteLater();
}

void addGroup::loadUsr()
{
    ui->comboBox->setDuplicatesEnabled(false);
    ui->comboBox->setSizeAdjustPolicy(QComboBox::AdjustToContentsOnFirstShow);
    db.open();
    if (db.open())
    {
        QSqlQuery query = db.exec("SELECT name, surname FROM usr WHERE name<>'' AND surname<>'';");
        while (query.next())
        {
            if (-1 == ui->comboBox->findText(query.record().value("name").toString()+" "+query.record().value("surname").toString()))
                ui->comboBox->addItem(query.record().value("name").toString()+" "+query.record().value("surname").toString());
        }
    }
    db.close();
}

void addGroup::getSessionEmail(QVariantMap session)
{
    this->session = session;
}

void addGroup::getDb(QSqlDatabase db)
{
    this->db = db;
}

addGroup::~addGroup()
{
    delete ui;
}
