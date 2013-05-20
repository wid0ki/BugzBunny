#include "passwordchange.h"
#include "ui_passwordchange.h"

passwordChange::passwordChange(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::passwordChange)
{
    ui->setupUi(this);
}

passwordChange::~passwordChange()
{
    delete ui;
}
