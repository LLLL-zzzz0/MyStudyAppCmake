#include "reviewController.h"

reviewcontroller::reviewcontroller(QSharedPointer<userModel> pUserModel, QSharedPointer<wordModel> pWordModel, review *pReview, QObject *parent)
: QObject{parent},
    m_pReview(pReview),
    m_pUserModel(pUserModel),
    m_pWordModel(pWordModel)
{
    setConnections();
}

void reviewcontroller::initMyViewData()
{
    int iRet = m_pWordModel->getWordCount(REVIEW, m_pUserModel->getCurUser());
    if(-1 == iRet)
    {
        emit initResult(false, "数据异常，请稍后重试");
        return;
    }

    if(0 == iRet)
    {
        emit initResult(false, "您还没有学习任何单词呢，先去学习吧");
        return;
    }

    m_pWordModel->selectWordFromDatabase(USER_REVIEW, m_pUserModel->getCurUser());
    emit initResult(true, "success");
}

void reviewcontroller::processingProvideReviewWord(bool bSuccess, const Word &wd, const QString &strMessage)
{
    if(!bSuccess)
    {
        QMessageBox::critical(m_pReview, "出错了", strMessage, "确认");
        return;
    }

    m_pReview->execUiClear();
    m_pReview->setConfimButtonText(true);
    m_pReview->setUiText(false, wd);
}

void reviewcontroller::processingTransmitUserInput(const QString &strUserInput)
{
    if(m_pReview->isButtonCurentTextConfirm())
    {
        m_pWordModel->verifyUserInput(strUserInput);
        return ;
    }

    m_pReview->hideUiMessage();
    m_pReview->setConfimButtonText(true);
}

void reviewcontroller::processingTransToStudyCenter()
{
    emit switchToStudyCenter(STUDYCENTER);
    m_pReview->hide();
}

void reviewcontroller::processingGetNextReviewWord()
{
    m_pWordModel->getNextReviewWord();
}

void reviewcontroller::processingVerifyUserInputResult(bool bCorrect, const Word &wd)
{
    m_pReview->setUiText(true, wd);
    m_pReview->setUistatus(bCorrect);
}

void reviewcontroller::setConnections()
{
    connect(m_pWordModel.get(), &wordModel::provideReviewWord, this, &reviewcontroller::processingProvideReviewWord);
    connect(m_pWordModel.get(), &wordModel::verifyUserInputResult, this, &reviewcontroller::processingVerifyUserInputResult);
    connect(m_pReview, &review::trans_to_studycenter, this, &reviewcontroller::processingTransToStudyCenter);
    connect(m_pReview, &review::getNextReviewWord, this, &reviewcontroller::processingGetNextReviewWord);
    connect(m_pReview, &review::transmitUserInput, this, &reviewcontroller::processingTransmitUserInput);
}










