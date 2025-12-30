#ifndef LOGINCONTROLLER_H
#define LOGINCONTROLLER_H

#include <QObject>
#include "userModel.h"
#include "login.h"
#include <QMessageBox>
#include <QPointer>
#include <QSharedPointer>
#include "viewData.h"

class loginController:public QObject
{
    Q_OBJECT
public:
    explicit loginController(QSharedPointer<userModel> pUserModel, login *pLoginView, QObject *parent = nullptr);
    ~loginController(){}

    //初始化
    void init();
    //设置连接
    void setConnections();
signals:
    //登录成功，切换到userspaceView，通知applicationcontroller
    void loginSuccess(VIEW view);
    //这个信号是给主控制器applicationcontroller的
    void switchToEnrollView(VIEW view);
public slots:
    //处理userModel的处理登录结果的信号
    void processingloginVerificationResult(userModel::AuthenticationResult result, const QString& strMessage);

    //处理loginview的登录信号
    void processingLoginRequest(const QString &strUsername, const QString &strPassword);

    //处理loginview的跳转到Enrollview的信号，通知applicationcontroller
    void processingSwitchToEnroll();

private:
    QSharedPointer<userModel> m_pUserModel;
    QPointer<login> m_pLoginView;
};

#endif // LOGINCONTROLLER_H
