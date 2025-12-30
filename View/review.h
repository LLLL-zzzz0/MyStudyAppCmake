#ifndef REVIEW_H
#define REVIEW_H

#include <QDialog>
#include <QDebug>
#include "appdata.h"
#include "mywidght.h"

namespace Ui {
class t0study;
}

//复习单词界面
class review : public myWidget
{
    Q_OBJECT

public:
    explicit review(QWidget *parent = nullptr);
    ~review();
    //设置ui
    void setUiText(bool bShowAll, const Word &wd);

    //设置确认按钮文本
    void setConfimButtonText(bool bConfirm);

    //获取当前按钮文本是否为确认
    bool isButtonCurentTextConfirm();

    //隐藏界面文本
    void hideUiMessage();

    //设置ui界面状态
    void setUistatus(bool bCorrect);

    //界面清理
    void execUiClear();
signals:
    void trans_to_studycenter();

    //下一个单词
    void getNextReviewWord();

    //传递用户输入
    void transmitUserInput(const QString &strUserInput);
private slots:
    void transToStudyCenter();
    void getNextWord();
    void confirmInput();
protected:
    void closeEvent(QCloseEvent *event) override;

private:
    void upDate();

    void setConnections();
    Ui::t0study *ui;
    QString m_strUser;
    QVector<Word> m_vctWords;
    int m_iCurrentCount;
    int m_iVctSize;
};

#endif // REVIEW_H
