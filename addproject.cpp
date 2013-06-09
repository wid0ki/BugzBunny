#include "addproject.h"
#include "ui_addproject.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QDebug>

addproject::addproject(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addproject)
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
    ui->lineEdit->setStyleSheet(ordinaryLineEditStyle);
    ui->pushButton->setStyleSheet(ordinaryButtonStyle);
    ui->pushButton_2->setStyleSheet(ordinaryButtonStyle);
    ui->label->setText("Создание проекта");
    ui->label->setStyleSheet(
                "QLabel {"
                "color: white;"
                "text-align: center;"
                "}");
    ui->frame->setStyleSheet(
                "QFrame {"
                 "background-color: black; "
                 "}");

    connect (ui->pushButton, SIGNAL(clicked()), this, SLOT(createProject()));
    connect (ui->pushButton_2, SIGNAL(clicked()), this, SLOT(cancel()));
    connect(ui->lineEdit, SIGNAL(editingFinished()), this, SLOT(loadUsr()));
    connect(ui->lineEdit, SIGNAL(editingFinished()), this, SLOT(loadProject()));
}

void addproject::loadUsr()
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
    loadProject();
}

void addproject::loadProject()
{
    db.open();
    if (db.open())
    {
        QSqlQuery query = db.exec("SELECT id, name FROM project;");
        while (query.next())
        {
            qDebug()<<ui->comboBox_2->findText(query.record().value("name").toString());
            if (-1 == ui->comboBox_2->findText(query.record().value("name").toString()))
                ui->comboBox_2->addItem(query.record().value("name").toString(),query.record().value("id").toString());
        }
    }
    db.close();
}

void addproject::createProject()
{
    ui->textBrowser->setReadOnly(false);
    QSqlQuery * query = new QSqlQuery(db);
    db.open();
    if (db.open())
    {
        qDebug()<<ui->lineEdit->text()<<" "<<ui->textBrowser->toPlainText();
        if (ui->checkBox->isChecked())
        {
            QSqlQuery * subquery = new QSqlQuery(db);
            subquery->prepare("SELECT id FROM project WHERE name = '"+ui->comboBox_2->currentText()+"';");
            qDebug()<<subquery->exec();
            int id_parent = subquery->record().value("id").toInt();
            query->prepare("INSERT INTO project (id,name, backlog, id_parent) VALUES (DEFAULT,?,?,?);");
            query->addBindValue(ui->lineEdit->text());
            query->addBindValue(ui->textBrowser->toPlainText());
            query->addBindValue(id_parent);
        }
        else
        {
            query->prepare("INSERT INTO project (id, name, backlog, id_parent) VALUES (DEFAULT,?,?, NULL);");
            query->addBindValue(ui->lineEdit->text());
            query->addBindValue(ui->textBrowser->toPlainText());
        }
        qDebug()<<query->exec()<<" "<<query->lastError().text();

        query->prepare("INSERT INTO entity2project (id_project, type_e, id_entity) VALUES (?,'user',?);");
        query->addBindValue(getProjectId(ui->lineEdit->text()));
        query->addBindValue(getUserId(session));
        qDebug()<<query->exec()<<" "<<query->lastError().text();

    }
    db.close();
    this->deleteLater();
}

int addproject::getProjectId(QString projectName)
{
    QSqlQuery * query = new QSqlQuery(db);
    db.open();
    query->prepare("SELECT id FROM project WHERE name='"+projectName+"'';");
    qDebug()<<query->exec()<<" "<<query->lastError().text();
    return query->record().value("id").toInt();
}

int addproject::getUserId(QVariantMap session)
{
    QSqlQuery * query = new QSqlQuery(db);
    db.open();
    query->prepare("SELECT id FROM user WHERE email='"+session.value("email").toString()+"'';");
    qDebug()<<query->exec()<<" "<<query->lastError().text();
    return query->record().value("id").toInt();
}

void addproject::getSessionEmail(QVariantMap session)
{
    this->session = session;
}

void addproject::cancel()
{
    this->hide();
    this->deleteLater();
}

void addproject::getDb(QSqlDatabase db)
{
    this->db = db;
}

addproject::~addproject()
{
    delete ui;
}
