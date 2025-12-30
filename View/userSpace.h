#ifndef USERSPACE_H
#define USERSPACE_H

#include <QDialog>
#include <QDebug>
#include "mywidght.h"

namespace Ui {
class space;
}

//个人中心
class userSpace : public myWidget
{
    Q_OBJECT

public:
    explicit userSpace(QWidget *parent = nullptr);
    ~userSpace();

signals:
    //view切换信号
    void trans_to_changepassword();
    void trans_to_login();
    void trans_to_studycenter();
private slots:
    void transToStudyCenter();
    void transToChangePassword();
    void transToLogin();

private:
    void setConnections();
    Ui::space *ui;
};

#endif // USERSPACE_H
