#include "login.h"
#include "ui_login.h"
#include <QDebug>
#include <QMessageBox>

login::login(QWidget *parent)
    : myWidget(parent)
    , ui(new Ui::JasonWord)
{
    init();
}

login::~login()
{
    delete ui;
}

//登录按钮事件处理
void login::responselogIn()
{
    qDebug() << "login::responselogIn " << this;
    emit loginRequest(ui->user_name_line->text(),ui->pwd_line->text());
}

//注册按钮事件处理
void login::transToEnroll()
{
    emit trans_to_enroll();
    uiTextClearup();
}

void login::init()
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->setWindowIcon(QIcon(":/pic/logo.ico"));

    ui->user_name_line->setClearButtonEnabled(true);
    ui->pwd_line->setClearButtonEnabled(true);

    setInputRule();
    disableAllChildrenFocus();
    setConnections();
}

void login::setInputRule()
{
    QRegularExpression   rx("[A-Za-z0-9]+");
    QRegularExpressionValidator  *rev = new QRegularExpressionValidator (rx, this);
    ui->user_name_line->setValidator(rev);

    QRegularExpression   qrx("[^ ]+");
    QRegularExpressionValidator  *qrev = new QRegularExpressionValidator (qrx, this);
    ui->pwd_line->setValidator(qrev);
}

void login::setTipMessage(const QString &strMessage)
{
    ui->tip->setText(strMessage);
}

void login::uiTextClearup()
{
    ui->user_name_line->clear();
    ui->pwd_line->clear();
    ui->tip->clear();
}

void login::setConnections()
{
    connect(ui->btn_log, &QPushButton::clicked, this, &login::responselogIn);
    connect(ui->enroll, &QPushButton::clicked, this, &login::transToEnroll);
}
