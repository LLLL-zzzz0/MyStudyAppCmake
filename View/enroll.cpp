#include "enroll.h"
#include "ui_enroll.h"
#include "databaseManager.h"

enroll::enroll(QWidget *parent) :
    myWidget(parent),
    ui(new Ui::enroll)
{
    init();
}

enroll::~enroll()
{
    delete ui;
}

void enroll::setTipMessage(const QString &strMessage)
{
    ui->label_checkTip->setText(strMessage);
}

void enroll::uiTextClearUp()
{
    ui->user_name_line->clear();
    ui->pwd_line->clear();
    ui->con_pwd_line->clear();
    ui->label_checkTip->clear();
}

//返回按钮事件处理
void enroll::transToLogin()
{
    emit trans_to_login();
}

//注册按钮事件处理
void enroll::responseUserEnroll()
{
    emit requestEnroll(ui->user_name_line->text(), ui->pwd_line->text(), ui->con_pwd_line->text());
}

void enroll::setConnections()
{
    connect(ui->btn_retToLogin, &QPushButton::clicked, this, &enroll::transToLogin);
    connect(ui->enroll_btn, &QPushButton::clicked, this, &enroll::responseUserEnroll);
}

void enroll::init()
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);

    setInputRules();
    disableAllChildrenFocus();
    setConnections();
}

void enroll::setInputRules()
{
    ui->user_name_line->setClearButtonEnabled(true);
    ui->pwd_line->setClearButtonEnabled(true);
    ui->con_pwd_line->setClearButtonEnabled(true);

    QRegularExpression   rx("[A-Za-z0-9]+");
    QRegularExpressionValidator  *rev = new QRegularExpressionValidator (rx, this);
    ui->user_name_line->setValidator(rev);

    QRegularExpression   qrx("[^ ]+");
    QRegularExpressionValidator  *qrev = new QRegularExpressionValidator (qrx, this);
    ui->pwd_line->setValidator(qrev);
    ui->con_pwd_line->setValidator(qrev);
}


