#include "studyCenter.h"
#include "ui_studyCenter.h"
#include "databaseManager.h"

studyCenter::studyCenter(QWidget *parent) :
    myWidget(parent),
    ui(new Ui::study)
{
    ui->setupUi(this);
    disableAllChildrenFocus();
    setConnections();
}

studyCenter::~studyCenter()
{
    delete ui;
}

void studyCenter::setTipText(const QString &strMessage)
{
    ui->tip->setText(strMessage);
}

void studyCenter::transToUserSpace()
{
    emit trans_to_userspace();
    ui->box_choosebox->setCurrentIndex(0);
}

void studyCenter::transToStudyWord()
{
    emit trans_to_studyword(ui->box_choosebox->currentIndex());
    ui->box_choosebox->setCurrentIndex(0);
}

void studyCenter::indexChanged()
{
    emit chooseBoxCurrentIndexChnaged(ui->box_choosebox->currentIndex());  
}

void studyCenter::transToReview()
{
    emit trans_to_review();
    ui->box_choosebox->setCurrentIndex(0);
}

void studyCenter::transToNewWord()
{
    emit trans_to_newword();
    ui->box_choosebox->setCurrentIndex(0);
}

void studyCenter::setConnections()
{
    connect(ui->box_choosebox, &QComboBox::currentIndexChanged, this, &studyCenter::indexChanged);
    connect(ui->btn_study, &QPushButton::clicked, this, &studyCenter::transToStudyWord);
    connect(ui->btn_newword, &QPushButton::clicked, this, &studyCenter::transToNewWord);
    connect(ui->btn_review, &QPushButton::clicked, this, &studyCenter::transToReview);
    connect(ui->btn_retTouserspace, &QPushButton::clicked, this, &studyCenter::transToUserSpace);
}

