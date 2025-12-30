#include "studyCenterController.h"

studycentercontroller::studycentercontroller(QSharedPointer<userModel> pUserModel, studyCenter* pStudyCenter, QObject *parent)
    : QObject{parent},
    m_pStudyCenter(pStudyCenter),
    m_pUserModel(pUserModel)
{
    setConnections();
}

void studycentercontroller::processingChooseBoxCurrentIndexChnaged(const int &Index)
{
    m_pUserModel->StudyCenterTipUpdate(Index);
}

void studycentercontroller::processingSwitchToStudyWord(const int &Index)
{
    if(0 == Index)
    {
        m_pStudyCenter->setTipText("请先选择词库");
        return ;
    }
    emit switchToStudyWord(STUDYWORD, Index);
}

void studycentercontroller::processingSwitchToReview()
{
    emit switchToReview(USERREVIEW);
}

void studycentercontroller::processingSwitchToUserSpace()
{
    emit switchToUserSpace(USERSPACE);
}

void studycentercontroller::processingSwitchToNewWord()
{
    emit switchToNewWord(USERNEWWORD);
}

void studycentercontroller::processingChooseBoxCurrentIndexChnagedResult(const QString &strMessage)
{
    m_pStudyCenter->setTipText(strMessage);
}

void studycentercontroller::setConnections()
{
    connect(m_pStudyCenter, &studyCenter::chooseBoxCurrentIndexChnaged, this, &studycentercontroller::processingChooseBoxCurrentIndexChnaged);
    connect(m_pStudyCenter, &studyCenter::trans_to_userspace, this, &studycentercontroller::processingSwitchToUserSpace);
    connect(m_pStudyCenter, &studyCenter::trans_to_review, this, &studycentercontroller::processingSwitchToReview);
    connect(m_pStudyCenter, &studyCenter::trans_to_newword, this, &studycentercontroller::processingSwitchToNewWord);
    connect(m_pStudyCenter, &studyCenter::trans_to_studyword, this, &studycentercontroller::processingSwitchToStudyWord);
    connect(m_pUserModel.get(), &userModel::StudyCenterTipUpdateResult, this, &studycentercontroller::processingChooseBoxCurrentIndexChnagedResult);
}

