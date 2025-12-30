#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include <QDialog>
#include <QDebug>
#include <QRegularExpressionValidator>
#include "mywidght.h"

QT_BEGIN_NAMESPACE
namespace Ui { class JasonWord; }
QT_END_NAMESPACE

//登录界面
class login : public myWidget
{
    Q_OBJECT

public:
    login(QWidget *parent = nullptr);
    ~login();
    //设置提示信息
    void setTipMessage(const QString& strMessage);
    void uiTextClearup();
signals:
    //登录请求
    void loginRequest(const QString &strUsername, const QString &strPassword);
    //跳转注册请求
    void trans_to_enroll();
private slots:
    //信号转发
    void responselogIn();
    void transToEnroll();
private:
    //初始化
    void init();
    //设置输入验证
    void setInputRule();
    //建立连接
    void setConnections();
    Ui::JasonWord *ui;
};
#endif // LOGIN_H
