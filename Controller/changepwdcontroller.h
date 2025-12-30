#ifndef CHANGEPWDCONTROLLER_H
#define CHANGEPWDCONTROLLER_H

#include <QObject>
#include "viewData.h"
#include "changePwd.h"
#include "userModel.h"
#include <QPointer>
#include <QSharedPointer>

class changepwdcontroller : public QObject
{
    Q_OBJECT
public:
    explicit changepwdcontroller(QSharedPointer<userModel> pUserModel, changePwd* pChangePwd, QObject *parent = nullptr);

signals:
    //页面切换信号
    void switchToLogin(VIEW view);
    void switchToUserSpace(VIEW view);

public slots:
    void processingTransToUserSpace();

private slots:
    //view传递修改密码的信号
    void processingUserChangePassword(const QString &strOriginPassword, const QString &strNewPassword, const QString &strNewPasswordReEnter);
    //usermodel传递修改密码的结果
    void processingUserChangePasswordResult(bool bSuccess, const QString& strMessage);
private:
    void setConnections();

    QSharedPointer<userModel> m_pUserModel;
    QPointer<changePwd> m_pChangePwd;
};

#endif // CHANGEPWDCONTROLLER_H
