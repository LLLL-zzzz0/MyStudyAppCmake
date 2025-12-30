#include "userModel.h"

userModel::userModel(QObject* parent):
    QObject(parent),
    m_strUserName("")
{

}

void userModel::loginVerification(const QString &strUserName, const QString &strUserPassword)
{
    if(strUserName.isEmpty() || strUserPassword.isEmpty())
    {
        emit loginVerificationResult(EMPTYINPUT, "用户名和密码不能为空");
        return ;
    }

    std::unique_ptr<QString> pStrPassword = std::make_unique<QString>();

    int iResult = DataBaseManager::selectUserInfo(USER_PWD, strUserName, pStrPassword.get());
    switch(iResult)
    {
        case EXECHASRESULT:
        {
            if((*(pStrPassword.get())) == strUserPassword)
            {
                m_strUserName = strUserName;
                emit loginVerificationResult(SUCCESS, "登录成功");
            }
            else
            {
                emit loginVerificationResult(WRONGPASSWORD, "密码错误");
            }
            break;
        }
        case EXECNORESULT:
        {
            emit loginVerificationResult(USERNOTFOUND, "用户名不存在");
            break;
        }
        case EXECERROR:
        default:
        {
            emit loginVerificationResult(DATABASEERROR, "数据库异常，请稍后重试");
            break;
        }
    }
}

bool userModel::checkIfUsernameExist(const QString &strUserName)
{
    int iResult = DataBaseManager::selectUserInfo(USER_EXIST, strUserName);
    return iResult == EXECHASRESULT;
}

void userModel::userRegistration(const QString &strUserName, const QString &strUserPassword, const QString &strUserPasswordReEnter)
{
    if(strUserName.length() < 6 || strUserName.length() > 18)
    {
        emit userRegistrationResult(false, "用户名长度需在6-18位之间");
        return ;
    }

    if(strUserPassword.length() < 6 || strUserPassword.length() > 18)
    {
        emit userRegistrationResult(false, "密码长度需在6-18位之间");
        return ;
    }

    if(strUserPassword != strUserPasswordReEnter)
    {
        emit userRegistrationResult(false, "两次输入的密码不一致");
        return ;
    }

    int iResult = DataBaseManager::selectUserInfo(USER_EXIST, strUserName);
    if(EXECERROR == iResult)
    {
        emit userRegistrationResult(false, "数据库异常，请稍后重试");
        return ;
    }

    if(EXECHASRESULT == iResult)
    {
        emit userRegistrationResult(false, "用户名已存在");
        return ;
    }

    QString strPasswordCopy = strUserPassword;
    int iCreateResult = DataBaseManager::selectUserInfo(INSERT_USER_INFO, strUserName, &strPasswordCopy);
    if(EXECERROR == iCreateResult)
    {
        emit userRegistrationResult(false, "创建用户失败，请稍后重试");
    }
    else
    {
        emit userRegistrationResult(true, "注册成功");
    }
}

void userModel::userChangePassword(const QString &strOriginPassword, const QString &strNewPassword, const QString &strNewPasswordReEnter)
{
    if(!strOriginPassword.length() || !strNewPassword.length() || !strNewPasswordReEnter.length())
    {
        emit userChangePasswordResult(false, "密码不能为空");
        return ;
    }

    if(strNewPassword.length() < 6 || strNewPassword.length() > 18)
    {
        emit userChangePasswordResult(false, "新密码长度不符合规则");
        return ;
    }

    if(strOriginPassword == strNewPassword)
    {
        emit userChangePasswordResult(false, "新密码不能与旧密码一致");
        return ;
    }

    if(strNewPassword != strNewPasswordReEnter)
    {
        emit userChangePasswordResult(false, "两次输入的新密码不一致");
        return ;
    }

    std::unique_ptr<QString> pStrPwd = std::make_unique<QString>();
    int iRetGetPwd = DataBaseManager::selectUserInfo(USER_PWD, m_strUserName, pStrPwd.get());
    if(EXECHASRESULT != iRetGetPwd)
    {
        emit userChangePasswordResult(false, "数据库异常，请稍后重试");
        return ;
    }

    if((*(pStrPwd.get())) != strOriginPassword)
    {
        emit userChangePasswordResult(false, "您输入的旧密码有误，请重新输入");
        return ;
    }

    QString strPasswordCopy = strNewPassword;
    int iRetUpdatePassword = DataBaseManager::selectUserInfo(UPDATE_USER_PWD, m_strUserName, &strPasswordCopy);
    if(EXECHASRESULT == iRetUpdatePassword)
    {
        emit userChangePasswordResult(true, "修改密码成功");
    }
    else
    {
        emit userChangePasswordResult(false, "更新密码失败，请稍后重试...");
    }
}

void userModel::StudyCenterTipUpdate(const int &iIndex)
{
    int iTotalWordsCount = -1;
    int iLearnedWordsCount = -1;
    switch(iIndex)
    {
        case 0:
        {
            emit  StudyCenterTipUpdateResult("");
            break;
        }
        case 1:
        {
            iTotalWordsCount = DataBaseManager::getWordCount(WordLibrary::CET_4);
            iLearnedWordsCount = DataBaseManager::getWordCount(WordLibrary::CET_4, m_strUserName);
            if((-1 != iTotalWordsCount) && (-1 != iLearnedWordsCount))
            {
                emit  StudyCenterTipUpdateResult("四级真题核心词汇,单词量:" + QString::number(iTotalWordsCount) + "已学习:" + QString::number(iLearnedWordsCount));
            }
            else
            {
                emit  StudyCenterTipUpdateResult("");
            }
            break;
        }
        case 2:
        {
            iTotalWordsCount = DataBaseManager::getWordCount(WordLibrary::CET_6);
            iLearnedWordsCount = DataBaseManager::getWordCount(WordLibrary::CET_6, m_strUserName);
            if((-1 != iTotalWordsCount) && (-1 != iLearnedWordsCount))
            {
                emit  StudyCenterTipUpdateResult("六级真题核心词汇,单词量:" + QString::number(iTotalWordsCount) + "已学习:" + QString::number(iLearnedWordsCount));
            }
            else
            {
                emit  StudyCenterTipUpdateResult("");
            }
            break;
        }
        case 3:
        {
            iTotalWordsCount = DataBaseManager::getWordCount(WordLibrary::KY);
            iLearnedWordsCount = DataBaseManager::getWordCount(WordLibrary::KY, m_strUserName);
            if((-1 != iTotalWordsCount) && (-1 != iLearnedWordsCount))
            {
                emit  StudyCenterTipUpdateResult("考研真题核心词汇,单词量:" + QString::number(iTotalWordsCount) + "已学习:" + QString::number(iLearnedWordsCount));
            }
            else
            {
                emit  StudyCenterTipUpdateResult("");
            }
            break;
        }
        default:
        {
            emit  StudyCenterTipUpdateResult("");
            break;
        }
    }
}














