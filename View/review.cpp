#include "review.h"
#include "ui_review.h"


review::review(QWidget *parent) :
    myWidget(parent),
    ui(new Ui::t0study)
{
    ui->setupUi(this);

    disableAllChildrenFocus();
    setConnections();
}

review::~review()
{
    delete ui;
}

void review::execUiClear()
{
    ui->lb_hint->clear();
    ui->lb_exampleSentence->clear();
    ui->lb_word->clear();
    ui->lb_meaning->clear();
    ui->lb_yinbiao->clear();
    ui->lb_exampleSentenceMeaning->clear();
    ui->userInput->clear();
}

void review::setUiText(bool bShowAll, const Word &wd)
{
    if(bShowAll)
    {
        ui->lb_word->setText(wd.strWord);
        ui->lb_exampleSentence->setText(wd.strExampleSentence);
    }

    ui->lb_meaning->setText(wd.strMeaning);
    ui->lb_yinbiao->setText(wd.strYinbiao);
    ui->lb_exampleSentenceMeaning->setText(wd.strExampleSentenceMeaning);
}

void review::setConfimButtonText(bool bConfirm)
{
    if(bConfirm)
    {
        ui->btn_confirm->setText("确认");
        ui->userInput->setEnabled(true);
    }
    else
    {
        ui->btn_confirm->setText("重新填写");
    }
    ui->btn_confirm->show();
}

bool review::isButtonCurentTextConfirm()
{
    if(ui->btn_confirm->text() == "确认")
    {
        return true;
    }

    return false;
}

void review::hideUiMessage()
{
    ui->lb_hint->clear();
    ui->lb_exampleSentence->clear();
    ui->lb_word->clear();
    ui->userInput->clear();
}

void review::setUistatus(bool bCorrect)
{
    setConfimButtonText(bCorrect);
    ui->userInput->setEnabled(false);
    if(bCorrect)
    {
        ui->lb_hint->setText("输入正确");
        ui->btn_confirm->hide();
    }
    else
    {
        ui->lb_hint->setText("输入错误,再试试吧");
    }
}

void review::setConnections()
{
    connect(ui->btn_return, &QPushButton::clicked, this, &review::transToStudyCenter);
    connect(ui->btn_next, &QPushButton::clicked, this, &review::getNextWord);
    connect(ui->btn_confirm, &QPushButton::clicked, this, &review::confirmInput);
    connect(ui->userInput, &QLineEdit::returnPressed, this, &review::confirmInput);
}

void review::transToStudyCenter()
{
    emit trans_to_studycenter();
}

void review::confirmInput()
{
    emit transmitUserInput(ui->userInput->text());
}

void review::closeEvent(QCloseEvent *event)
{
    // 发送返回信号
    emit trans_to_studycenter();
    event->accept();  // 接受关闭事件
}

void review::getNextWord()
{
    emit getNextReviewWord();
}

