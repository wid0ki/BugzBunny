#ifndef PROFILE_H
#define PROFILE_H

#include <QDialog>

namespace Ui {
class profile;
}

class profile : public QDialog
{
    Q_OBJECT
    
public:
    explicit profile(QWidget *parent = 0);
    ~profile();
    
private:
    Ui::profile *ui;
};

#endif // PROFILE_H
