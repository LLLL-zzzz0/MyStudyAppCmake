#ifndef USERMODEL_H
#define USERMODEL_H

#include <QObject>
#include <QString>
#include <memory.h>
#include "databaseManager.h"

class userModel: public QObject
{
    Q_OBJECT

public:
    enum AuthenticationResult
    {
        SUCCESS,
        EMPTYINPUT,
        WRONGPASSWORD,
        USERNOTFOUND,
        DATABASEERROR
    };
    explicit userModel(QObject* parent = nullptr);
    ~userModel(){}
    //登录验证
    void loginVerification(const QString& strUserName, const QString& strUserPassword);

    //获取当前用户名
    QString getCurUser() const {return m_strUserName;}

    //检查当前用户名是否存在
    bool checkIfUsernameExist(const QString& strUserName);

    //用户注册
    void userRegistration(const QString& strUserName, const QString& strUserPassword, const QString &strUserPasswordReEnter);

    //用户修改密码
    void userChangePassword(const QString &strOriginPassword, const QString &strNewPassword, const QString &strNewPasswordReEnter);

    //个人中心choosebox更新后更新提示信息
    void StudyCenterTipUpdate(const int &iIndex);

signals:
    void loginVerificationResult(AuthenticationResult result, const QString& strMessage);
    void userRegistrationResult(bool bSuccess, const QString& strMessage);
    void userChangePasswordResult(bool bSuccess, const QString& strMessage);
    void StudyCenterTipUpdateResult(const QString& strMessage);

private:
    QString m_strUserName;
};

#endif // USERMODEL_H
