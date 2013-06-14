#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "signin.h"
#include "addproject.h"
#include "addcomment.h"
#include "addgroup.h"
#include "addtask.h"
#include <QDebug>
#include <QTableWidget>
#include <QMessageBox>

int MainWindow::getUserId()
{
    QSqlQuery * query = new QSqlQuery(db);
    db.open();
    query->prepare("SELECT id FROM usr WHERE email='"+ui->lineEdit_3->text()+"';");
    query->exec();
    query->next();
    qDebug()<<"user id: "<<query->record().value("id").toInt()<<" "<<ui->lineEdit_3->text();
    return query->record().value("id").toInt();
}

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

    drawProfile();

    connect(ui->profileButton, SIGNAL(clicked()), this, SLOT(drawProfile()));
    connect(ui->projectButton, SIGNAL(clicked()), this, SLOT(drawProject()));
    connect(ui->taskButton, SIGNAL(clicked()),this, SLOT(drawTask()));
    connect(ui->commentButton, SIGNAL(clicked()), this, SLOT(drawComment()));
    connect(ui->grpButton, SIGNAL(clicked()), this, SLOT(drawGroup()));
    connect(this,SIGNAL(sessionChanged()), this, SLOT(drawProfile()));
    connect(ui->savePass, SIGNAL(clicked()),this,SLOT(savePass()));
    connect(ui->saveProfile, SIGNAL(clicked()), this, SLOT(saveProfile()));
    connect(ui->rightButton, SIGNAL(clicked()), this, SLOT(exit()));
    connect(ui->myProjects, SIGNAL(toggled(bool)), this, SLOT(manageLeftRadioButton()));
    connect(ui->allProjects, SIGNAL(toggled(bool)), this, SLOT(manageRightRadioButton()));
}

void MainWindow::MVC()
{

}

void MainWindow::manageLeftRadioButton()
{
    if (ui->myProjects->text() == "Мои проекты") myProjects();
    else if (ui->myProjects->text() == "Мои группы") myGroups();
    else if (ui->myProjects->text() == "Мои комментарии") myComments();
    else if (ui->myProjects->text() == "Мои задачи") myTasks();
}

void MainWindow::manageRightRadioButton()
{
    if (ui->allProjects->text() == "Все проекты") allProjects();
    else if (ui->allProjects->text() == "Все группы") allGroups();
    else if (ui->allProjects->text() == "Все комментарии") allComments();
    else if (ui->allProjects->text() == "Все задачи") allTasks();
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

void MainWindow::allComments()
{

}

void MainWindow::myComments()
{

}

void MainWindow::drawComment()
{
    hideEverything(4);
    unDownEverything(1);
    ui->myProjects->setText("Мои комментарии");
    ui->allProjects->setText("Все комментарии");
    ui->rightButton->setText("Новый комментарий");
    ui->commentButton->setDown(true);
    QMessageBox::warning(this,QString::fromUtf8("Ошибка"),QString::fromUtf8("Раздел в разработке, давай посмотрим что-нибудь еще"));
}

void MainWindow::allTasks()
{
    if (db.open())
    {
        QVariantMap el;
        QSqlQuery query = db.exec("SELECT * FROM suggestion;");
        while (query.next())
        {
            el.clear();
            el.insert("title", query.record().value("title").toString());
            el.insert("content", query.record().value("content").toString());
            el.insert("rating", query.record().value("rating").toString());
            el.insert("status", query.record().value("status").toString());
            el.insert("type_s", query.record().value("type_s").toString());
            model.append(el);
            rowCount++;
        }
        ui->statusBar->showMessage("Просмотр всех задач в трекере", 1000);
        qDebug()<<"row"<<rowCount;
    }
    db.close();
}

void MainWindow::myTasks()
{
    int rowCount = 0;
    if (db.open())
    {
        QVariantMap el;
        QSqlQuery query(db);
        query.prepare("SELECT * FROM suggestion WHERE id_creator = %s;");
        query.addBindValue(getUserId());
        query.exec();
        while (query.next())
        {
            el.clear();
            el.insert("title", query.record().value("title").toString());
            el.insert("content", query.record().value("content").toString());
            el.insert("rating", query.record().value("rating").toString());
            el.insert("status", query.record().value("status").toString());
            el.insert("type_s", query.record().value("type_s").toString());
            model.append(el);
            rowCount++;
        }
        ui->statusBar->showMessage("Просмотр моих задач в трекере", 1000);
    }
    db.close();
}

void MainWindow::drawTask()
{
    unDownEverything(2);
    hideEverything(4);
    ui->title->setText("Мои задачи");
    ui->myProjects->setText("Мои задачи");
    ui->allProjects->setText("Все задачи");
    ui->rightButton->setText("Новая задача");
    ui->taskButton->setDown(true);
    ui->projectView->show();

    rowCount = 0;
    QSqlQuery query;
    QVariantMap data;
    model.clear();

    if (ui->myProjects->isChecked())
        {
            myTasks();
        }
    else
        {
            allTasks();
        }
    qDebug()<<"row: "<<rowCount;
    ui->projectView->setRowCount(rowCount*3);
    ui->projectView->setColumnWidth(0, 40);
    ui->projectView->setColumnWidth(1, 550);

    for (int i = 0; i < rowCount*3; i+=3)
    {
        QTableWidgetItem * item = new QTableWidgetItem;
        item->setText(model.at(i).value("title").toString());
        item->setTextColor(Qt::black);
        ui->projectView->setItem(i,1,item);
        item->setText(model.at(i).value("content").toString());
        ui->projectView->setItem(i+1,1,item);
        item->setText(model.at(i).value("status").toString());
        ui->projectView->setItem(i+2,1,item);
    }
}

void MainWindow::projectOpen()
{

}

void MainWindow::myProjects()
{
    int rowCount = 0;
    if (db.open())
    {
        QVariantMap el;
        QSqlQuery query(db);
        query.prepare("SELECT project.name, project.backlog FROM project, entity2project, grp"
                      "WHERE entity2project.id_entity = %s AND entity2project.type_e = 'user'"
                      "AND entity2project.id_project = project.id;");
        query.addBindValue(getUserId());
        query.exec();
        while (query.next())
        {
            el.clear();
            el.insert("name", query.record().value("name").toString());
            el.insert("backlog", query.record().value("backlog").toString());
            model.append(el);
            rowCount++;
        }
        ui->statusBar->showMessage("Просмотр назначенных мне проектов в трекере", 1000);
    }
    db.close();
}

void MainWindow::allProjects()
{
    if (db.open())
    {
        QVariantMap el;
        QSqlQuery query = db.exec("SELECT * FROM project;");
        while (query.next())
        {
            el.clear();
            el.insert("name", query.record().value("name").toString());
            el.insert("backlog", query.record().value("backlog").toString());
            model.append(el);
            rowCount++;
        }
        ui->statusBar->showMessage("Просмотр всех проектов в трекере", 1000);
        qDebug()<<"row"<<rowCount;
    }
    db.close();
}

void MainWindow::drawProject()
{
    hideEverything(4);
    unDownEverything(4);
    ui->allProjects->setText("Все проекты");
    ui->myProjects->setText("Мои проекты");
    ui->projectButton->setDown(true);
    ui->title->setText(QString::fromUtf8("Проекты"));
    ui->rightButton->setText("Новый проект");
    ui->projectView->show();
    ui->projectView->showGrid();
    ui->projectView->setColumnCount(2);
    ui->projectView->verticalHeader()->hide();
    ui->projectView->horizontalHeader()->hide();

    rowCount = 0;
    QSqlQuery query;
    QVariantMap data;
    model.clear();

    if (ui->myProjects->isChecked())
        {
            myProjects();
        }
    else
        {
            allProjects();
        }
    qDebug()<<"row: "<<rowCount;
    ui->projectView->setRowCount(rowCount);
    ui->projectView->setColumnWidth(0, 40);
    ui->projectView->setColumnWidth(1, 550);

    for (int i = 0; i < rowCount; i++)
    {
        QTableWidgetItem * item = new QTableWidgetItem;
        qDebug()<<"Model"<<model.at(i).value("name").toString();
        item->setText("Проект: "+model.at(i).value("name").toString()+"  Backlog: "+model.at(i).value("backlog").toString());
        item->setTextColor(Qt::black);
        ui->projectView->setItem(i,1,item);
    }
}

void MainWindow::allGroups()
{
    rowCount=0;
    if (db.open())
    {
        QVariantMap el;
        QSqlQuery query = db.exec("SELECT * FROM grp;");
        while (query.next())
        {
            el.clear();
            qDebug()<<query.record().value("name").toString();
            el.insert("name", query.record().value("name").toString());
            model.append(el);
            rowCount++;
        }
        ui->statusBar->showMessage("Просмотр всех групп в трекере", 1000);
        qDebug()<<"row"<<rowCount;
    }
    db.close();
}

void MainWindow::myGroups()
{
    rowCount=0;
    if (db.open())
    {
        QVariantMap el;
        QSqlQuery query = db.exec("SELECT * FROM grp, usr2grp WHERE grp.id=usr2grp.id_group AND usr2grp.id_person="+QString::number(getUserId())+";");
        while (query.next())
        {
            el.clear();
            qDebug()<<query.record().value("name").toString();
            el.insert("name", query.record().value("name").toString());
            model.append(el);
            rowCount++;
        }
        ui->statusBar->showMessage("Просмотр моих групп в трекере", 1000);
        qDebug()<<"row"<<rowCount;
    }
    db.close();
}

void MainWindow::drawGroup()
{
    hideEverything(4);
    unDownEverything(3);
    ui->title->setText("Мои группы");
    ui->projectView->showGrid();
    ui->allProjects->setText("Все группы");
    ui->myProjects->setText("Мои группы");
    ui->rightButton->setText("Новая группа");
    ui->grpButton->setDown(true);
    ui->projectView->show();
    ui->allProjects->setChecked(true);
    rowCount = 0;
    QSqlQuery query;
    QVariantMap data;
    model.clear();

    if (ui->myProjects->isChecked())
        {
            myGroups();
        }
    else
        {
            allGroups();
        }
    qDebug()<<"row: "<<rowCount;
    ui->projectView->setRowCount(rowCount);
    ui->projectView->setColumnWidth(0, 40);
    ui->projectView->setColumnWidth(1, 550);


    for (int i = 0; i < rowCount; i++)
    {
        QTableWidgetItem * item = new QTableWidgetItem;
        qDebug()<<"From model: "<<model.at(i).value("name").toString();
        item->setText(model.at(i).value("name").toString());
        item->setTextColor(Qt::black);
        ui->projectView->setItem(i,1,item);
    }
}

void MainWindow::hideEverything(int frameNo)
{
    if (frameNo == 3) ui->frame_3->show();
    else
        ui->frame_3->hide();
    if (frameNo == 4) ui->frame_4->show();
    else
        ui->frame_4->hide();
    if (ui->title->text() != "Мои группы")
            ui->projectView_2->hide();
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
        addproject * addProjectWindow = new addproject;
        addProjectWindow->getSessionEmail(session);
        addProjectWindow->getDb(db);
        addProjectWindow->show();
    }
    else if (ui->rightButton->text() == "Новая группа")
    {
        addGroup * addGroupWindow = new addGroup;
        addGroupWindow->getSessionEmail(session);
        addGroupWindow->getDb(db);
        addGroupWindow->show();
    }
    else if (ui->rightButton->text() == "Новая задача")
    {
        addTask * addTaskWindow = new addTask;
        addTaskWindow->getSessionEmail(session);
        addTaskWindow->getDb(db);
        addTaskWindow->show();
    }
    else if (ui->rightButton->text() == "Новый комментарий")
    {
        addComment * addCommentWindow = new addComment;
        addCommentWindow->getSessionEmail(session);
        addCommentWindow->getDb(db);
        addCommentWindow->show();
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
