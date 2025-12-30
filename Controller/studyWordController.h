#ifndef STUDYWORDCONTROLLER_H
#define STUDYWORDCONTROLLER_H

#include <QObject>
#include "studyWord.h"
#include "viewData.h"
#include "userModel.h"
#include "wordModel.h"
#include <QPointer>
#include <QSharedPointer>

class studywordcontroller : public QObject
{
    Q_OBJECT
public:
    explicit studywordcontroller(QSharedPointer<userModel> pUserModel, QSharedPointer<wordModel> pWordModel, studyWord* pStudyWord, QObject *parent = nullptr);

signals:


    //切换视图
    void switchToStudyCenter(VIEW view);
public slots:
    //初始化视图
    void initMyViewData(const int &iIndex);

    //处理wordModel提供的数据
    void processingProvideWord(bool bSuccess, const Word &wd, bool bIsNewWord, const QString &strMessage);

    //处理userview跳转到studycenter的信号
    void processingTransToStudyCenter();

    //处理点击userview收藏生词按钮的信号
    void processingCollectNewWord(const QString &strWord, bool bIsNewWord);

    //处理点击userview熟悉，不熟悉按钮的信号
    void processingAddToReview(const QString &strWord, bool bIncreaseReviewTime);

    //处理wordModel返回handleCollectNewWord的结果
    void processingCollectNewWordResult(bool bSuccess);

    //处理wordModel返回handleAddToReview的结果
    void processingAddToReviewResult(bool bSuccess);

private:

    void setConnectinos();

    QPointer<studyWord> m_pStudyWord;
    QSharedPointer<userModel> m_pUserModel;
    QSharedPointer<wordModel> m_pWordModel;
};

#endif // STUDYWORDCONTROLLER_H
