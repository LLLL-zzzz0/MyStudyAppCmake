#ifndef STUDYCENTERCONTROLLER_H
#define STUDYCENTERCONTROLLER_H

#include <QObject>
#include <QPointer>
#include "viewData.h"
#include "studyCenter.h"
#include <QSharedPointer>
#include "userModel.h"

class studycentercontroller : public QObject
{
    Q_OBJECT
public:
    explicit studycentercontroller(QSharedPointer<userModel> pUserModel, studyCenter* pStudyCenter, QObject *parent = nullptr);

signals:
    //视图切换
    void switchToUserSpace(VIEW view);
    void switchToReview(VIEW view);
    void switchToStudyWord(VIEW view, const int &Index);
    void switchToNewWord(VIEW view);

private slots:
    //处理choosebox事件
    void processingChooseBoxCurrentIndexChnaged(const int &Index);

    //处理视图切换
    void processingSwitchToStudyWord(const int &Index);
    void processingSwitchToReview();
    void processingSwitchToUserSpace();
    void processingSwitchToNewWord();

private:
    void processingChooseBoxCurrentIndexChnagedResult(const QString &strMessage);
    void setConnections();
    QPointer<studyCenter> m_pStudyCenter;
    QSharedPointer<userModel> m_pUserModel;
};

#endif // STUDYCENTERCONTROLLER_H
