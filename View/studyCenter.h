#ifndef STUDYCENTER_H
#define STUDYCENTER_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>
#include "mywidght.h"

namespace Ui {
class study;
}

//学习中心
class studyCenter : public myWidget
{
    Q_OBJECT

public:
    explicit studyCenter(QWidget *parent = nullptr);
    ~studyCenter();
    //设置提示信息
    void setTipText(const QString &strMessage);
signals:
    //view切换信号
    void trans_to_userspace();
    void trans_to_studyword(const int &iIndex);
    void trans_to_review();
    void trans_to_newword();
    //choosebox事件
    void chooseBoxCurrentIndexChnaged(const int &iIndex);
private slots:
    void transToStudyWord();
    void indexChanged();
    void transToReview();
    void transToNewWord();
    void transToUserSpace();

private:
    void setConnections();

    Ui::study *ui;
};

#endif // STUDYCENTER_H
