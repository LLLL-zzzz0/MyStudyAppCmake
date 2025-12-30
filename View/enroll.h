#ifndef ENROLL_H
#define ENROLL_H

#include <QDialog>
#include <QDebug>
#include <QMessageBox>
#include <QRegularExpressionValidator>
#include "mywidght.h"

namespace Ui {
class enroll;
}

//注册界面
class enroll : public myWidget
{
    Q_OBJECT

public:
    enroll(QWidget *parent = nullptr);
    ~enroll();
    //提示信息
    void setTipMessage(const QString &strMessage);
    //ui清理
    void uiTextClearUp();
signals:

    //发出注册请求给EnrollController
    void requestEnroll(const QString &strUserName, const QString &strPassword, const QString &strPasswordReEnter);

    void trans_to_login();
private slots:
    //信号转发
    void transToLogin();
    void responseUserEnroll();

private:
    //设置连接
    void setConnections();

    //初始化
    void init();

    //设计QEdit的输入规则
    void setInputRules();
    Ui::enroll *ui;
};

#endif // ENROLL_H
