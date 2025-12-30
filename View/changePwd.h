#ifndef CHANGEPWD_H
#define CHANGEPWD_H

#include <QDialog>
#include <QDebug>
#include <QMessageBox>
#include <QRegularExpressionValidator>
#include "mywidght.h"


namespace Ui {
class change;
}

//修改密码界面
class changePwd : public myWidget
{
    Q_OBJECT

public:
    explicit changePwd(QWidget *parent = nullptr);
    ~changePwd();

    //ui清理
    void uiTextClearUp();
    //设置提示信息
    void setTipText(const QString &strMessage);
signals:
    //view切换的信号 view -> controller
    void trans_to_userspace();
    //修改密码的请求 view -> controller
    void changePasswordRequest(const QString &strOriginPassword, const QString &strNewPassword, const QString &strNewPasswordReEnter);
private slots:
    //槽函数
    void confirmChangePassword();
    void transToUserSpace();

private:
    void init();

    //设置输入框的输入规则
    void setInputRules();

    //连接信号槽
    void setConnections();
    Ui::change *ui;
};

#endif // CHANGEPWD_H
