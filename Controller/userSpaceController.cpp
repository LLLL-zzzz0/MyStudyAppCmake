#include "userSpaceController.h"

userspacecontroller::userspacecontroller(userSpace* pUserSpace, QObject *parent)
    : QObject{parent},
    m_pUserSpace(pUserSpace)
{
    setConnections();
}

void userspacecontroller::processingSwitchToLogin()
{
    qDebug() << "userspacecontroller::processingSwitchToLogin";
    emit switchToLogin(LOGIN);
}

void userspacecontroller::processingSwitchToStudyCenter()
{
    emit switchToStudyCenter(STUDYCENTER);
}

void userspacecontroller::processingSwitchToChangePassword()
{
    emit switchToChangePassword(CHANGEPASSWORD);
}

void userspacecontroller::setConnections()
{
    bool b1 = connect(m_pUserSpace, &userSpace::trans_to_changepassword, this, &userspacecontroller::processingSwitchToChangePassword);
    bool b2 = connect(m_pUserSpace, &userSpace::trans_to_login, this, &userspacecontroller::processingSwitchToLogin);
    bool b3 = connect(m_pUserSpace, &userSpace::trans_to_studycenter, this, &userspacecontroller::processingSwitchToStudyCenter);
    qDebug() << "userspacecontroller::setConnections:" << b1 << " " << b2 << " " << b3;
}
