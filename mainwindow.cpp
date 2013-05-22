#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "signin.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
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
    ordinaryLeftMenuButtonStyle = QString(
                "QPushButton {"
                     "background-image: url(:/background/grey_left.png);"
                     "text-align: left;"
                     "color: #C0C0C0;"
                     "border: none;"
                 "}"
                 "QPushButton:hover {"
                     "background-image: url(:/background/focus_left.png);"
                     "background-repeat: repeat;"
                     "color: white;"
                 "}"
                 "QPushButton:pressed {"
                     "background-image: url(:/background/focus_left.png);"
                     "background-repeat: repeat;"
                     "color: white;"
                 "}"
                );
    ui->frame->setStyleSheet(
                "QFrame {"
                 "background-image: url(:/background/grey_left.png); "
                 "background-repeat: repeat-y;"
                 "}");
    ui->profileButton->setIconSize(QSize(30,30));
    ui->profileButton->setIcon(QIcon(QString(":/icon/home.png")));
    ui->profileButton->setStyleSheet(ordinaryLeftMenuButtonStyle);
    ui->projectButton->setIcon(QIcon(QString(":/icon/project.png")));
    ui->projectButton->setIconSize(QSize(30,30));
    ui->projectButton->setStyleSheet(ordinaryLeftMenuButtonStyle);
    ui->grpButton->setIcon(QIcon(QString(":/icon/group.png")));
    ui->grpButton->setIconSize(QSize(30,30));
    ui->grpButton->setStyleSheet(ordinaryLeftMenuButtonStyle);
    ui->taskButton->setIcon(QIcon(QString(":/icon/task.png")));
    ui->taskButton->setIconSize(QSize(30,30));
    ui->taskButton->setStyleSheet(ordinaryLeftMenuButtonStyle);
    ui->commentButton->setIcon(QIcon(QString(":/icon/comment.png")));
    ui->commentButton->setIconSize(QSize(30,30));
    ui->commentButton->setStyleSheet(ordinaryLeftMenuButtonStyle);
    ui->frame_2->setStyleSheet(
                "QFrame {"
                "border-radius: 2px;"
                "background-color: black;"
                "}");
    ui->rightButton->setStyleSheet(
                "QPushButton {"
                     "background-image: url(:/background/grey_left.png);"
                     "text-align: center;"
                     "border-radius: 5px;"
                     "color: #C0C0C0;"
                     "border: solid;"
                 "}"
                 "QPushButton:hover {"
                     "background-image: url(:/background/focus_left.png);"
                     "border-radius: 5px;"
                     "background-repeat: repeat;"
                     "color: white;"
                 "}"
                 "QPushButton:pressed {"
                     "background-image: url(:/background/focus_left.png);"
                     "border-radius: 5px;"
                     "background-repeat: repeat;"
                     "color: white;"
                 "}");

    connect(ui->profileButton, SIGNAL(clicked()), this, SLOT(drawProfile()));
    connect(ui->projectButton, SIGNAL(clicked()), this, SLOT(drawProject()));
    connect(ui->taskButton, SIGNAL(clicked()),this, SLOT(drawTask()));
    connect(ui->commentButton, SIGNAL(clicked()), this, SLOT(drawComment()));
    connect(ui->grpButton, SIGNAL(clicked()), this, SLOT(drawGroup()));
    connect(this,SIGNAL(sessionChanged()), this, SLOT(drawProfile()));
    connect(ui->savePass, SIGNAL(clicked()),this,SLOT(savePass()));
    connect(ui->saveProfile, SIGNAL(clicked()), this, SLOT(saveProfile()));
    connect(ui->rightButton, SIGNAL(clicked()), this, SLOT(exit()));
}

void MainWindow::drawProfile()
{
     hideEverything(3);
     unDownEverything(0);
     ui->title->setText(QString::fromUtf8("Профиль"));
     ui->lineEdit->setText(session.value("name").toString());
     ui->lineEdit_2->setText(session.value("surname").toString());
     ui->lineEdit_3->setText(session.value("email").toString());
     ui->lineEdit_3->setReadOnly(true);
     ui->dateEdit->setDate(session.value("birth").toDate());
     ui->title->setStyleSheet(
                 "QLabel {"
                 "color: white;"
                 "text-align: center;"
                 "}");
     ui->rightButton->setText("Выход");
     ui->saveProfile->setStyleSheet(ordinaryButtonStyle);
     ui->savePass->setStyleSheet(ordinaryButtonStyle);
     ui->lineEdit->setStyleSheet(ordinaryLineEditStyle);
     ui->lineEdit_2->setStyleSheet(ordinaryLineEditStyle);
     ui->lineEdit_3->setStyleSheet(ordinaryLineEditStyle);
     ui->lineEdit_4->setStyleSheet(ordinaryLineEditStyle);
     ui->lineEdit_5->setStyleSheet(ordinaryLineEditStyle);
}

void MainWindow::drawComment()
{
    hideEverything(4);
    unDownEverything(1);
    ui->commentButton->setDown(true);
}

void MainWindow::drawTask()
{
    unDownEverything(2);
    hideEverything(5);
    ui->taskButton->setDown(true);
}

void MainWindow::drawProject()
{
    hideEverything(6);
    unDownEverything(4);
    ui->projectButton->setDown(true);
    ui->title->setText(QString::fromUtf8("Проекты"));
    ui->rightButton->setText("Новый проект");
}

void MainWindow::drawGroup()
{
    hideEverything(7);
    unDownEverything(3);
    ui->grpButton->setDown(true);
}

void MainWindow::hideEverything(int frameNo)
{
    if (frameNo == 3) ui->frame_3->show();
    else
        ui->frame_3->hide();
    if (frameNo == 4) ui->frame_4->show();
    else
        ui->frame_4->hide();
//    if (frameNo == 5) ui->frame_5->show();
//    else
//        ui->frame_5->hide();
//    if (frameNo == 6) ui->frame_6->show();
//    else
//        ui->frame_6->hide();
//    if (frameNo == 7) ui->frame_7->show();
//    else
//        ui->frame_7->hide();
//    if (frameNo == 8) ui->frame_8->show();
//    else
//        ui->frame_8->hide();
}

void MainWindow::unDownEverything(int buttonNo)
{
    if (buttonNo == 0) ui->profileButton->setDown(true);
    else
        ui->profileButton->setDown(false);
    if (buttonNo == 1) ui->commentButton->setDown(true);
    else
        ui->commentButton->setDown(false);
    if (buttonNo == 2) ui->taskButton->setDown(true);
    else
        ui->taskButton->setDown(false);
    if (buttonNo == 3) ui->grpButton->setDown(true);
    else
        ui->grpButton->setDown(false);
    if (buttonNo == 4) ui->projectButton->setDown(true);
    else
        ui->projectButton->setDown(false);
}

void MainWindow::saveProfile()
{
    if (db.open())
    {
        QSqlQuery query = db.exec("UPDATE usr SET name='"+ui->lineEdit->text()+"', surname = '"
                                  +ui->lineEdit_2->text()+"', birth = '"+ui->dateEdit->text()+"' WHERE email = '"+session.value("email").toString()+"';");
        session["name"] = ui->lineEdit->text();
        session["surname"] = ui->lineEdit_2->text();
        session["birth"] = ui->dateEdit->text();
        ui->statusBar->showMessage("Данные профиля обновлены", 1000);
    }
    db.close();
}

void MainWindow::savePass()
{
    if (db.open())
    {
        QSqlQuery query = db.exec("SELECT secret FROM usr WHERE email = '"+session.value("email").toString()+"';");
        query.next();
        if (query.record().value("secret").toString() == QString(QCryptographicHash::hash(QString(ui->lineEdit_4->text()+session.value("email").toString()).toUtf8(), QCryptographicHash::Md5).toHex()))
        {
            query = db.exec("UPDATE usr SET secret='"+QString(QCryptographicHash::hash(QString(ui->lineEdit_5->text()+session.value("email").toString()).toUtf8(), QCryptographicHash::Md5).toHex())
                                  +"' WHERE email = '"+session.value("email").toString()+"';");
            ui->statusBar->showMessage("Пароль изменен", 1000);
        }
        else
            ui->statusBar->showMessage("Неверно введен старый пароль", 1000);
    }
    db.close();
}

void MainWindow::exit()
{
    if (ui->rightButton->text() == "Выход")
    {
        session.clear();
        this->hide();
    }
    else if (ui->rightButton->text() == "Новый проект")
    {

    }
}

void MainWindow::getDb(QSqlDatabase db)
{
    this->db = db;
}

MainWindow::~MainWindow()
{
    delete ui;
}
