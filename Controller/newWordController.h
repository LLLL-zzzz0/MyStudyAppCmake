#ifndef NEWWORDCONTROLLER_H
#define NEWWORDCONTROLLER_H

#include <QObject>
#include "newWord.h"
#include "viewData.h"
#include "userModel.h"
#include "wordModel.h"
#include <QPointer>
#include <QSharedPointer>

class newwordcontroller : public QObject
{
    Q_OBJECT
public:
    explicit newwordcontroller(QSharedPointer<userModel> pUserModel, QSharedPointer<wordModel> pWordModel, newWord* pNewWord, QObject *parent = nullptr);

signals:
    //切换视图信号
    void switchToStudyCenter(VIEW view);

public slots:
    //初始化视图数据
    void initMyViewData();

    //处理切换到studycenter的信号
    void processingSwitchToStudyCenter();

    //处理wordmodel提供的wd数据
    void processingProvideNewWord(bool bSuccess, bool bIsFirstPage, bool bIslastPage, const QVector<Word> &vctWord, const QString &strMessage);

    //处理wordmodel提供的生词表单词数量数据
    void processingRetWordCount(bool bSuccess, const int &iCount);

    //获取其他页
    void processingGetPrivousPage();
    void processingGetNextPage();

private:
    void setConnections();

    QSharedPointer<userModel> m_pUserModel;
    QSharedPointer<wordModel> m_pWordModel;
    QPointer<newWord> m_pNewWord;
};

#endif // NEWWORDCONTROLLER_H
