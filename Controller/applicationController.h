#ifndef APPLICATIONCONTROLLER_H
#define APPLICATIONCONTROLLER_H

#include <QObject>
#include "loginController.h"
#include "enrollController.h"
#include <memory.h>
#include <QPointer>
#include <QSharedPointer>
#include <QScopedPointer>
#include <QStackedWidget>
#include <QMessageBox>
#include "viewData.h"
#include "userSpaceController.h"
#include "changePwdController.h"
#include "studyCenterController.h"
#include "studyWordController.h"
#include "reviewController.h"
#include "newWordController.h"

class applicationController : public QObject
{
    Q_OBJECT

public:

    explicit applicationController(QObject *parent = nullptr);
    ~applicationController();

    //初始化
    void init();

    //初始化视窗
    void initMyWeight();

    //初始化用户中心
    void initUserSpaceView();

    //初始化修改密码视图
    void initChangePasswordView();

    //初始化学习中心视图
    void initStudyCenterView();

    //初始化reView视图
    void initReviewView();

    //初始化NewWord视图
    void initNewWordView();

private slots:
    void viewSwitch(VIEW view);
    void createStudyWordView(VIEW view, const int &iIndex);
    void processingReviewInitResult(bool bSuccess, const QString &strMessage);

private:
    QScopedPointer<QStackedWidget> m_pStackedWeight;

    QSharedPointer<userModel> m_pUserModel;
    QSharedPointer<wordModel> m_pWordModel;

    QPointer<login> m_pLoginView;
    QPointer<enroll> m_pEnrollView;
    QPointer<userSpace> m_pUserSpaceView;
    QPointer<changePwd> m_pChangePasswordView;
    QPointer<studyCenter> m_pStudyCenterView;
    QPointer<studyWord> m_pStudyWordView;
    QPointer<review> m_pReviewView;
    QPointer<newWord> m_pNewWordView;

    std::unique_ptr<loginController> m_pLoginController;
    std::unique_ptr<enrollcontroller> m_pEnrollController;
    std::unique_ptr<userspacecontroller> m_pUserSpaceController;
    std::unique_ptr<changepwdcontroller> m_pChangePasswordController;
    std::unique_ptr<studycentercontroller> m_pStudyCentercontroller;
    std::unique_ptr<studywordcontroller> m_pStudyWordcontroller;
    std::unique_ptr<reviewcontroller> m_pReviewController;
    std::unique_ptr<newwordcontroller> m_pNewwordController;
};

#endif // APPLICATIONCONTROLLER_H
