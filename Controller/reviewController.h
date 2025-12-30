#ifndef REVIEWCONTROLLER_H
#define REVIEWCONTROLLER_H

#include <QObject>
#include "review.h"
#include "viewData.h"
#include "userModel.h"
#include "wordModel.h"
#include <QPointer>
#include <QSharedPointer>
#include <QMessageBox>

class reviewcontroller : public QObject
{
    Q_OBJECT
public:
    explicit reviewcontroller(QSharedPointer<userModel> pUserModel, QSharedPointer<wordModel> pWordModel, review* pReview,QObject *parent = nullptr);

signals:
    //通知主控制器切换view
    void switchToStudyCenter(VIEW view);

    //初始化视图失败
    void initResult(bool bSuccess, const QString& strMessage);
public slots:
    //初始化review视图
    void initMyViewData();

    //处理数据显示
    void processingProvideReviewWord(bool bSuccess, const Word &wd, const QString& strMessage);

    //处理用户传递的输入
    void processingTransmitUserInput(const QString &strUserInput);

    //处理跳转到studycenter
    void processingTransToStudyCenter();

    //处理点击下一个单词
    void processingGetNextReviewWord();

    //处理wordmodel返回的结果
    void processingVerifyUserInputResult(bool bCorrect, const Word &wd);

private:

    void setConnections();
    QPointer<review> m_pReview;
    QSharedPointer<userModel> m_pUserModel;
    QSharedPointer<wordModel> m_pWordModel;
};

#endif // REVIEWCONTROLLER_H
