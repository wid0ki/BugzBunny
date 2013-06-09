#include "projectviewer.h"
#include "ui_projectviewer.h"

projectViewer::projectViewer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::projectViewer)
{
    ui->setupUi(this);
    ui->label->setStyleSheet(
                "QLabel {"
                "color: white;"
                "text-align: center;"
                "}");
    ui->frame->setStyleSheet(
                "QFrame {"
                "border-radius: 2px;"
                "background-color: black;"
                "}");
}

void projectViewer::getDb(QSqlDatabase db)
{
    this->db = db;
}

projectViewer::~projectViewer()
{
    delete ui;
}
