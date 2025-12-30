#ifndef ENROLLCONTROLLER_H
#define ENROLLCONTROLLER_H

#include <QObject>
#include "enroll.h"
#include "userModel.h"
#include <QPointer>
#include <QSharedPointer>
#include "viewData.h"

class enrollcontroller:public QObject
{
    Q_OBJECT
public:
    explicit enrollcontroller(QSharedPointer<userModel> pUserModel, enroll *pEnrollView, QObject* parent = nullptr);
    //初始化
    void init();
    //建立连接
    void setConnections();
signals:
    //注册成功，或者需要需要跳转到Loginview时，把这个信号给主控制器applicationcontroller
    void switchToLoginView(VIEW view);

public slots:

    //处理enrollView的注册信号
    void processingUserRegistration(const QString &strUserName, const QString &strPassword, const QString &strPasswordReEnter);

    //处理enrollView的跳转Loginview的信号,通知applicationcontroller
    void processingTransToLoginView();

    //处理UserModel的注册结果
    void processingUserRegistrationResult(bool bSuccess, const QString& strMessage);

private:
    QPointer<enroll> m_pEnrollView;
    QSharedPointer<userModel> m_pUserModel;
};

#endif // ENROLLCONTROLLER_H
