#include "addtask.h"
#include "ui_addtask.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QDebug>

addTask::addTask(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addTask)
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
    ui->label->setText("Создание задачи");
    ui->label->setStyleSheet(
                "QLabel {"
                "color: white;"
                "text-align: center;"
                "}");
    ui->frame->setStyleSheet(
                "QFrame {"
                 "background-color: black; "
                 "}");
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(addNewTask()));
    connect(ui->lineEdit, SIGNAL(editingFinished()), this, SLOT(loadUsr()));
    connect(ui->lineEdit, SIGNAL(editingFinished()), this, SLOT(loadProject()));
}

void addTask::addNewTask()
{
    QSqlQuery * query = new QSqlQuery(db);
    db.open();
    if (db.open())
    {

        query->prepare("INSERT INTO suggestion (id, id_creator, type_s, title, content, rating, status, id_assigned, id_group, id_parent) "
                       "VALUES (DEFAULT, "+QString::number(getUserId(session))+",'"+ui->comboBox->currentText()+"','"+ui->lineEdit->text()
                       +"','"+ui->textEdit->toPlainText()+"','"+ui->comboBox_3->currentText()+"','"+ui->comboBox_2->currentText()
                       +"','"+ui->comboBox_5->currentText()+"', 1, 1);");
        qDebug()<<"Insert into suggestion "<<query->exec()<<" "<<query->lastError().text();

    }
    db.close();
    this->deleteLater();
}

int addTask::getUserId(QVariantMap session)
{
    QSqlQuery * query = new QSqlQuery(db);
    db.open();
    query->prepare("SELECT id FROM usr WHERE email='"+session.value("email").toString()+"';");
    qDebug()<<"USER ID: "<<query->exec()<<" "<<session.value("email").toString()<<" "<<query->lastError().text();
    query->next();
    return query->record().value("id").toInt();
}

void addTask::loadUsr()
{
    ui->comboBox->setDuplicatesEnabled(false);
    ui->comboBox->setSizeAdjustPolicy(QComboBox::AdjustToContentsOnFirstShow);
    db.open();
    if (db.open())
    {
        QSqlQuery query = db.exec("SELECT name, surname FROM usr WHERE name<>'' AND surname<>'';");
        while (query.next())
        {
            if (-1 == ui->comboBox_5->findText(query.record().value("name").toString()+" "+query.record().value("surname").toString()))
                ui->comboBox_5->addItem(query.record().value("name").toString()+" "+query.record().value("surname").toString());
        }
    }
    db.close();
    loadProject();
}

void addTask::loadProject()
{
    db.open();
    if (db.open())
    {
        QSqlQuery query = db.exec("SELECT id, name FROM project;");
        while (query.next())
        {
            qDebug()<<ui->comboBox_4->findText(query.record().value("name").toString());
            if (-1 == ui->comboBox_4->findText(query.record().value("name").toString()))
                ui->comboBox_4->addItem(query.record().value("name").toString(),query.record().value("id").toString());
        }
    }
    db.close();
}

void addTask::getSessionEmail(QVariantMap session)
{
    this->session = session;
}

void addTask::getDb(QSqlDatabase db)
{
    this->db = db;
}

addTask::~addTask()
{
    delete ui;
}
