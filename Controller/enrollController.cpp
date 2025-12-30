#include "enrollController.h"


enrollcontroller::enrollcontroller(QSharedPointer<userModel> pUserModel, enroll *pEnrollView, QObject *parent):
    QObject(parent),
    m_pEnrollView(pEnrollView),
    m_pUserModel(pUserModel)
{
    init();
}

void enrollcontroller::init()
{
    setConnections();
}

void enrollcontroller::setConnections()
{
    connect(m_pEnrollView, &enroll::requestEnroll, this, &enrollcontroller::processingUserRegistration);
    connect(m_pEnrollView, &enroll::trans_to_login, this, &enrollcontroller::processingTransToLoginView);
    connect(m_pUserModel.get(), &userModel::userRegistrationResult, this, &enrollcontroller::processingUserRegistrationResult);
}


void enrollcontroller::processingUserRegistration(const QString &strUserName, const QString &strPassword, const QString &strPasswordReEnter)
{
    m_pUserModel->userRegistration(strUserName, strPassword, strPasswordReEnter);
}

void enrollcontroller::processingTransToLoginView()
{
    qDebug() << "enrollcontroller::processingTransToLoginView";
    emit switchToLoginView(LOGIN);
    m_pEnrollView->uiTextClearUp();
}

void enrollcontroller::processingUserRegistrationResult(bool bSuccess, const QString &strMessage)
{
    if(!bSuccess)
    {
        m_pEnrollView->setTipMessage(strMessage);
    }
    else
    {
        QMessageBox::information(m_pEnrollView, "注册成功", "点击确定跳转到登录界面");
        emit switchToLoginView(LOGIN);
        m_pEnrollView->uiTextClearUp();
    }
}











