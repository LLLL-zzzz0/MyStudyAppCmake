#include "loginController.h"


loginController::loginController(QSharedPointer<userModel> pUserModel, login *pLoginView, QObject *parent):
    QObject(parent),
    m_pUserModel(pUserModel),
    m_pLoginView(pLoginView)
{
    init();
}

void loginController::init()
{
    setConnections();
}

void loginController::setConnections()
{
    qDebug() << "loginController::setConnections::" << m_pLoginView;
    bool bconn1 = connect(m_pLoginView, &login::loginRequest, this, &loginController::processingLoginRequest);
    bool bconn2 = connect(m_pLoginView, &login::trans_to_enroll, this, &loginController::processingSwitchToEnroll);
    bool bconn3 = connect(m_pUserModel.get(), &userModel::loginVerificationResult, this, &loginController::processingloginVerificationResult);
    qDebug() << bconn1 << " " << bconn2 << " "<< bconn3 << " ";
}

void loginController::processingloginVerificationResult(userModel::AuthenticationResult result, const QString &strMessage)
{
    switch(result)
    {
        case userModel::SUCCESS:
        {
            m_pLoginView->setTipMessage(strMessage);
            emit loginSuccess(USERSPACE);
            m_pLoginView->uiTextClearup();
            break;
        }
        case userModel::EMPTYINPUT:
        case userModel::WRONGPASSWORD:
        case userModel::USERNOTFOUND:
        {
            m_pLoginView->setTipMessage(strMessage);
            break;
        }
        case userModel::DATABASEERROR:
        {
            m_pLoginView->setTipMessage(strMessage);
            QMessageBox::critical(m_pLoginView, "系统错误", "数据库连接异常，请检查网络连接或联系管理员。");
            break;
        }
    }
}

void loginController::processingLoginRequest(const QString &strUsername, const QString &strPassword)
{
    qDebug() << "loginController::processingLoginRequest";
    m_pUserModel->loginVerification(strUsername, strPassword);
}

void loginController::processingSwitchToEnroll()
{
    emit switchToEnrollView(ENROLL);
}

