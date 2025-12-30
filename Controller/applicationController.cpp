#include "applicationController.h"

applicationController::applicationController(QObject *parent)
    : QObject{parent},
    m_pStackedWeight(nullptr),
    m_pUserModel(nullptr),
    m_pWordModel(nullptr),
    m_pLoginView(nullptr),
    m_pEnrollView(nullptr),
    m_pUserSpaceView(nullptr),
    m_pChangePasswordView(nullptr),
    m_pStudyCenterView(nullptr),
    m_pStudyWordView(nullptr),
    m_pReviewView(nullptr),
    m_pNewWordView(nullptr),
    m_pLoginController(nullptr),
    m_pEnrollController(nullptr),
    m_pUserSpaceController(nullptr),
    m_pChangePasswordController(nullptr),
    m_pStudyCentercontroller(nullptr),
    m_pStudyWordcontroller(nullptr),
    m_pReviewController(nullptr),
    m_pNewwordController(nullptr)
{
    init();
}

applicationController::~applicationController()
{
    if (nullptr != m_pStudyWordView)
    {
        delete m_pStudyWordView;
    }

    if (nullptr != m_pReviewView)
    {
        delete m_pReviewView;
    }

    if (nullptr != m_pNewWordView)
    {
        delete m_pNewWordView;
    }
}

void applicationController::init()
{
    initMyWeight();
    m_pUserModel.reset(new userModel);

    m_pLoginView = new login();
    m_pEnrollView = new enroll();

    m_pStackedWeight->addWidget(m_pLoginView);
    m_pStackedWeight->addWidget(m_pEnrollView);
    m_pStackedWeight->setCurrentWidget(m_pLoginView);
    m_pStackedWeight->show();

    m_pLoginController = std::make_unique<loginController>(m_pUserModel, m_pLoginView);
    m_pEnrollController = std::make_unique<enrollcontroller>(m_pUserModel, m_pEnrollView);
    connect(m_pLoginController.get(), &loginController::switchToEnrollView, this, &applicationController::viewSwitch);
    connect(m_pLoginController.get(), &loginController::loginSuccess, this, &applicationController::viewSwitch);
    connect(m_pEnrollController.get(), &enrollcontroller::switchToLoginView, this, &applicationController::viewSwitch);
}

void applicationController::initMyWeight()
{
    m_pStackedWeight.reset(new QStackedWidget());

    m_pStackedWeight->setWindowTitle("极思英语");
    m_pStackedWeight->setFixedSize(761, 471);
    m_pStackedWeight->setWindowFlags(m_pStackedWeight->windowFlags() & ~Qt::WindowMaximizeButtonHint);

    // 设置为主窗口
    m_pStackedWeight->setAttribute(Qt::WA_QuitOnClose, true); // 主窗口关闭时退出应用
}

void applicationController::initUserSpaceView()
{
    m_pUserSpaceView = new userSpace();
    m_pStackedWeight->addWidget(m_pUserSpaceView);

    m_pUserSpaceController = std::make_unique<userspacecontroller>(m_pUserSpaceView);

    connect(m_pUserSpaceController.get(), &userspacecontroller::switchToChangePassword, this, &applicationController::viewSwitch);
    connect(m_pUserSpaceController.get(), &userspacecontroller::switchToLogin, this, &applicationController::viewSwitch);
    connect(m_pUserSpaceController.get(), &userspacecontroller::switchToStudyCenter, this, &applicationController::viewSwitch);
}

void applicationController::initChangePasswordView()
{
    m_pChangePasswordView = new changePwd();
    m_pStackedWeight->addWidget(m_pChangePasswordView);

    m_pChangePasswordController = std::make_unique<changepwdcontroller>(m_pUserModel, m_pChangePasswordView);

    connect(m_pChangePasswordController.get(), &changepwdcontroller::switchToUserSpace, this, &applicationController::viewSwitch);
    connect(m_pChangePasswordController.get(), &changepwdcontroller::switchToLogin, this, &applicationController::viewSwitch);
}

void applicationController::initStudyCenterView()
{
    m_pStudyCenterView = new studyCenter();
    m_pStackedWeight->addWidget(m_pStudyCenterView);

    m_pStudyCentercontroller = std::make_unique<studycentercontroller>(m_pUserModel, m_pStudyCenterView);

    connect(m_pStudyCentercontroller.get(), &studycentercontroller::switchToUserSpace, this, &applicationController::viewSwitch);
    connect(m_pStudyCentercontroller.get(), &studycentercontroller::switchToNewWord, this, &applicationController::viewSwitch);
    connect(m_pStudyCentercontroller.get(), &studycentercontroller::switchToReview, this, &applicationController::viewSwitch);
    connect(m_pStudyCentercontroller.get(), &studycentercontroller::switchToStudyWord, this, &applicationController::createStudyWordView);
}

void applicationController::initReviewView()
{
    if(nullptr == m_pReviewView)
    {
        m_pReviewView = new review();
    }

    if(nullptr == m_pWordModel)
    {
        m_pWordModel.reset(new wordModel);
    }

    if(nullptr == m_pReviewController)
    {
        m_pReviewController = std::make_unique<reviewcontroller>(m_pUserModel, m_pWordModel, m_pReviewView);
        connect(m_pReviewController.get(), &reviewcontroller::switchToStudyCenter, this, &applicationController::viewSwitch);
        connect(m_pReviewController.get(), &reviewcontroller::initResult, this, &applicationController::processingReviewInitResult);
    }

    m_pReviewController->initMyViewData();
}

void applicationController::initNewWordView()
{
    if(nullptr == m_pNewWordView)
    {
        m_pNewWordView = new newWord();
    }

    if(nullptr == m_pWordModel)
    {
        m_pWordModel.reset(new wordModel);
    }

    if(nullptr == m_pNewwordController)
    {
        m_pNewwordController = std::make_unique<newwordcontroller>(m_pUserModel, m_pWordModel, m_pNewWordView);
        connect(m_pNewwordController.get(), &newwordcontroller::switchToStudyCenter, this, &applicationController::viewSwitch);
    }

    m_pNewwordController->initMyViewData();
}

void applicationController::viewSwitch(VIEW view)
{
    switch (view)
    {
        case LOGIN:
        {
            m_pStackedWeight->show();
            m_pStackedWeight->setCurrentWidget(m_pLoginView);
            break;
        }
        case ENROLL:
        {
            m_pStackedWeight->show();
            m_pStackedWeight->setCurrentWidget(m_pEnrollView);
            break;
        }
        case USERSPACE:
        {
            if(nullptr == m_pUserSpaceView)
            {
                initUserSpaceView();
            }
            m_pStackedWeight->show();
            m_pStackedWeight->setCurrentWidget(m_pUserSpaceView);
            break;
        }
        case CHANGEPASSWORD:
        {
            if(nullptr == m_pChangePasswordView)
            {
                initChangePasswordView();
            }
            m_pStackedWeight->show();
            m_pStackedWeight->setCurrentWidget(m_pChangePasswordView);
            break;
        }
        case STUDYCENTER:
        {
            if(nullptr == m_pStudyCenterView)
            {
                initStudyCenterView();
            }
            m_pStackedWeight->show();
            m_pStackedWeight->setCurrentWidget(m_pStudyCenterView);
            break;
        }
        case STUDYWORD:
        {
            qDebug() << "STUDYWORD:" << m_pStudyWordView;
            m_pStudyWordView->show();
            m_pStackedWeight->hide();
            break;
        }
        case USERREVIEW:
        {
            qDebug() << "USERREVIEW";
            initReviewView();
            break;
        }
        case USERNEWWORD:
        {
            qDebug() << "USERNEWWORD";
            initNewWordView();
            m_pNewWordView->show();
            m_pStackedWeight->hide();
            break;
        }
        default:
        {
            break;
        }
    }
}

void applicationController::createStudyWordView(VIEW view, const int &iIndex)
{
    if(nullptr == m_pStudyWordView)
    {
        m_pStudyWordView = new studyWord();
    }

    if(nullptr == m_pWordModel)
    {
        m_pWordModel.reset(new wordModel);
    }

    if(nullptr == m_pStudyWordcontroller)
    {
        m_pStudyWordcontroller = std::make_unique<studywordcontroller>(m_pUserModel, m_pWordModel, m_pStudyWordView);
        connect(m_pStudyWordcontroller.get(), &studywordcontroller::switchToStudyCenter, this, &applicationController::viewSwitch);
    }

    m_pStudyWordcontroller->initMyViewData(iIndex);
    viewSwitch(view);
}

void applicationController::processingReviewInitResult(bool bSuccess, const QString &strMessage)
{
    if(!bSuccess)
    {
        QMessageBox::information(m_pStudyCenterView, "出错了", strMessage, "确定");
        return;
    }

    m_pStackedWeight->hide();
    m_pReviewView->show();
}


