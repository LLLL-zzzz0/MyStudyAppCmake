#ifndef STUDYWORD_H
#define STUDYWORD_H

#include <QDialog>
#include <QDebug>
#include <QMessageBox>
#include "mywidght.h"

namespace Ui {
class cstudy;
}

//学习单词界面
class studyWord : public myWidget
{
    Q_OBJECT

public:
    explicit studyWord(QWidget *parent = nullptr);
    ~studyWord();
    //设置当前展示单词的数据
    void setCurrentWordText(const QString &strWord, const QString &strMeaning, const QString &strYinbiao, const QString &strExampleSentence, const QString &strExampleSentenceMeaning);

    //设置收藏生词按钮的文本
    void setCollectNewWordText(const QString &strText);

    //更新收藏生词按钮的文本
    void updateCollectNewWordText();

signals:
    void trans_to_studycenter();
    //收藏生词
    void collectNewWord(const QString &strWord, bool bIsNewWord);
    //添加到复习表
    void addToReview(const QString &strWord, bool bIncreaseReviewTime);

private slots:
    void addToNewWord();
    void insertToReview();
    void insertOrUpdateToReview();
    void transToStudyCenter();
protected:
    void closeEvent(QCloseEvent *event) override;

private:
    //连接信号和槽
    void setConnections();

    Ui::cstudy *ui;
};

#endif // STUDYWORD_H
