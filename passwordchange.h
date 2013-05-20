#ifndef PASSWORDCHANGE_H
#define PASSWORDCHANGE_H

#include <QDialog>

namespace Ui {
class passwordChange;
}

class passwordChange : public QDialog
{
    Q_OBJECT
    
public:
    explicit passwordChange(QWidget *parent = 0);
    ~passwordChange();
    
private:
    Ui::passwordChange *ui;
};

#endif // PASSWORDCHANGE_H
