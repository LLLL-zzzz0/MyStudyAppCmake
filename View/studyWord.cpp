#include "studyWord.h"
#include "ui_studyWord.h"
#include "databaseManager.h"

studyWord::studyWord(QWidget *parent) :
    myWidget(parent),
    ui(new Ui::cstudy)
{
    ui->setupUi(this);
    setConnections();
    disableAllChildrenFocus();
}

studyWord::~studyWord()
{
    delete ui;
}

void studyWord::setCollectNewWordText(const QString &strText)
{
    ui->btn_add->setText(strText);
}

void studyWord::updateCollectNewWordText()
{
    if(ui->btn_add->text() == "收藏生词")
    {
        ui->btn_add->setText("取消收藏");
    }
    else
    {
        ui->btn_add->setText("收藏生词");
    }
}

void studyWord::setCurrentWordText(const QString &strWord, const QString &strMeaning, const QString &strYinbiao, const QString &strExampleSentence, const QString &strExampleSentenceMeaning)
{
    ui->lb_word->setText(strWord);
    ui->lb_phonetic->setText(strMeaning);
    ui->lb_wordmeaning->setText(strYinbiao);
    ui->lb_examplesentence->setText(strExampleSentence);
    ui->lb_examplesentencemeaning->setText(strExampleSentenceMeaning);
}

void studyWord::transToStudyCenter()
{
    emit trans_to_studycenter();
}

void studyWord::closeEvent(QCloseEvent *event)
{
    // 发送返回信号
    emit trans_to_studycenter();
    event->accept();  // 接受关闭事件
}

void studyWord::setConnections()
{
    connect(ui->btn_add, &QPushButton::clicked, this, &studyWord::addToNewWord);
    connect(ui->btn_unknow, &QPushButton::clicked, this, &studyWord::insertToReview);
    connect(ui->btn_know, &QPushButton::clicked, this, &studyWord::insertOrUpdateToReview);
    connect(ui->btn_returnTostudycenter, &QPushButton::clicked, this, &studyWord::transToStudyCenter);
}

void studyWord::addToNewWord()
{
    if(ui->btn_add->text() == "收藏生词")
    {
        emit collectNewWord(ui->lb_word->text(), false);
    }
    else
    {
       emit collectNewWord(ui->lb_word->text(), true);
    }
}

void studyWord::insertToReview()
{
    emit addToReview(ui->lb_word->text(), false);
}

void studyWord::insertOrUpdateToReview()
{
    emit addToReview(ui->lb_word->text(), true);
}
