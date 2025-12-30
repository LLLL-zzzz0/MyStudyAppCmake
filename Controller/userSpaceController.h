#ifndef USERSPACECONTROLLER_H
#define USERSPACECONTROLLER_H

#include <QObject>
#include "userSpace.h"
#include <QPointer>
#include "viewData.h"

class userspacecontroller : public QObject
{
    Q_OBJECT
public:
    explicit userspacecontroller(userSpace* pUserSpace, QObject *parent = nullptr);

signals:
    //视图切换 this controller -> 总的controller
    void switchToLogin(VIEW view);
    void switchToStudyCenter(VIEW view);
    void switchToChangePassword(VIEW view);
public slots:
    //处理视图切换 view -> controller
    void processingSwitchToLogin();
    void processingSwitchToStudyCenter();
    void processingSwitchToChangePassword();

private:
    void setConnections();
    QPointer<userSpace> m_pUserSpace;
};

#endif // USERSPACECONTROLLER_H
