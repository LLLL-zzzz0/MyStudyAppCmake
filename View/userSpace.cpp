#include "userSpace.h"
#include "ui_userSpace.h"

userSpace::userSpace(QWidget *parent) :
    myWidget(parent),
    ui(new Ui::space)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
    disableAllChildrenFocus();
    setConnections();
}

userSpace::~userSpace()
{
    delete ui;
}

//返回登录界面
void userSpace::transToLogin()
{
    qDebug() << "userSpace::transToLogin";
    emit trans_to_login();
}

void userSpace::setConnections()
{
    connect(ui->btn_toChangepwd, &QPushButton::clicked, this, &userSpace::transToChangePassword);
    connect(ui->btn_retTologin, &QPushButton::clicked, this, &userSpace::transToLogin);
    connect(ui->btn_toStudyCenter, &QPushButton::clicked, this, &userSpace::transToStudyCenter);
}

//跳转到修改密码界面
void userSpace::transToChangePassword()
{
    emit trans_to_changepassword();
}

//跳转到学习界面
void userSpace::transToStudyCenter()
{
    emit trans_to_studycenter();
}

