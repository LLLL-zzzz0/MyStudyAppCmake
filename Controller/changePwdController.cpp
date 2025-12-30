#include "changePwdController.h"

changepwdcontroller::changepwdcontroller(QSharedPointer<userModel> pUserModel, changePwd* pChangePwd, QObject *parent)
    : QObject{parent},
    m_pUserModel(pUserModel),
    m_pChangePwd(pChangePwd)
{
    setConnections();
}

void changepwdcontroller::processingTransToUserSpace()
{
    emit switchToUserSpace(USERSPACE);
    m_pChangePwd->uiTextClearUp();
}

void changepwdcontroller::processingUserChangePassword(const QString &strOriginPassword, const QString &strNewPassword, const QString &strNewPasswordReEnter)
{
    m_pUserModel->userChangePassword(strOriginPassword, strNewPassword, strNewPasswordReEnter);
}

void changepwdcontroller::processingUserChangePasswordResult(bool bSuccess, const QString &strMessage)
{
    m_pChangePwd->setTipText(strMessage);
    if(!bSuccess)
    {
        return ;
    }

    QMessageBox::information(m_pChangePwd, "成功", "您的密码已成功修改，点击确认返回登录界面重新登录");
    emit switchToLogin(LOGIN);
    m_pChangePwd->uiTextClearUp();
}

void changepwdcontroller::setConnections()
{
    connect(m_pChangePwd, &changePwd::changePasswordRequest, this, &changepwdcontroller::processingUserChangePassword);
    connect(m_pChangePwd, &changePwd::trans_to_userspace, this, &changepwdcontroller::processingTransToUserSpace);
    connect(m_pUserModel.get(), &userModel::userChangePasswordResult, this, &changepwdcontroller::processingUserChangePasswordResult);
}
