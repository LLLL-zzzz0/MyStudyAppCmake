#include "changePwd.h"
#include "ui_changePwd.h"

changePwd::changePwd(QWidget *parent) :
    myWidget(parent),
    ui(new Ui::change)
{  
    init();
}

changePwd::~changePwd()
{
    delete ui;
}

void changePwd::uiTextClearUp()
{
    ui->lineEdit_originPwd->clear();
    ui->lineEdit_newPwd->clear();
    ui->lineEdit_conNewPwd->clear();
    ui->label_tip->clear();
}

void changePwd::setTipText(const QString &strMessage)
{
    ui->label_tip->setText(strMessage);
}

//返回用户个人主页
void changePwd::transToUserSpace()
{
    emit trans_to_userspace();
}

void changePwd::init()
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);

    setInputRules();
    disableAllChildrenFocus();
    setConnections();
}

void changePwd::setInputRules()
{
    QRegularExpression  qrx("[^ ]+");
    QRegularExpressionValidator    *qrev = new QRegularExpressionValidator   (qrx, this);
    ui->lineEdit_originPwd->setValidator(qrev);
    ui->lineEdit_newPwd->setValidator(qrev);
    ui->lineEdit_conNewPwd->setValidator(qrev);
}

//设置连接
void changePwd::setConnections()
{
    connect(ui->btn_confirm, &QPushButton::clicked, this, &changePwd::confirmChangePassword);
    connect(ui->btn_touserspace, &QPushButton::clicked, this, &changePwd::transToUserSpace);
}

//响应修改密码事件
void changePwd::confirmChangePassword()
{
    emit changePasswordRequest(ui->lineEdit_originPwd->text(), ui->lineEdit_newPwd->text(), ui->lineEdit_conNewPwd->text());
}



