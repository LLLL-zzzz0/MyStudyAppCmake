#include "studyWordController.h"

studywordcontroller::studywordcontroller(QSharedPointer<userModel> pUserModel, QSharedPointer<wordModel> pWordModel, studyWord* pStudyWord,QObject *parent)
    : QObject{parent},
    m_pStudyWord(pStudyWord),
    m_pUserModel(pUserModel),
    m_pWordModel(pWordModel)
{
    setConnectinos();
}

void studywordcontroller::initMyViewData(const int &iIndex)
{
    switch(iIndex)
    {
        case 1:
        {
            m_pWordModel->selectWordFromDatabase(CET_4, m_pUserModel->getCurUser());
            m_pWordModel->setCurrentWordLib(CET_4);
            break;
        }
        case 2:
        {
            m_pWordModel->selectWordFromDatabase(CET_6, m_pUserModel->getCurUser());
            m_pWordModel->setCurrentWordLib(CET_6);
            break;
        }
        case 3:
        {
            m_pWordModel->selectWordFromDatabase(KY, m_pUserModel->getCurUser());
            m_pWordModel->setCurrentWordLib(KY);
            break;
        }
        default:
        {
            break;
        }
    }
}

void studywordcontroller::processingProvideWord(bool bSuccess, const Word &wd, bool bIsNewWord, const QString &strMessage)
{
    if(!bSuccess)
    {
        QMessageBox::critical(m_pStudyWord, "出错了", strMessage, "确认");
        return;
    }

    if(bIsNewWord)
    {
        m_pStudyWord->setCollectNewWordText("取消收藏");
    }
    else
    {
        m_pStudyWord->setCollectNewWordText("收藏生词");
    }

    m_pStudyWord->setCurrentWordText(wd.strWord, wd.strMeaning, wd.strYinbiao, wd.strExampleSentence, wd.strExampleSentenceMeaning);
    qDebug() << wd.strWord;
}

void studywordcontroller::processingTransToStudyCenter()
{
    m_pStudyWord->hide();
    m_pWordModel->updateUserNewwordCache(m_pUserModel->getCurUser());
    emit switchToStudyCenter(STUDYCENTER);
}

void studywordcontroller::processingCollectNewWord(const QString &strWord, bool bIsNewWord)
{
    m_pWordModel->handleCollectNewWord(strWord, bIsNewWord);
}

void studywordcontroller::processingAddToReview(const QString &strWord, bool bIncreaseReviewTime)
{
    m_pWordModel->handleAddToReview(strWord, bIncreaseReviewTime);
}

void studywordcontroller::processingCollectNewWordResult(bool bSuccess)
{
    if(!bSuccess)
    {
        QMessageBox::critical(m_pStudyWord, "出错啦", "服务器异常，请稍后重试", "确认");
        return ;
    }

    m_pStudyWord->updateCollectNewWordText();
}

void studywordcontroller::processingAddToReviewResult(bool bSuccess)
{
    if(!bSuccess)
    {
        QMessageBox::critical(m_pStudyWord, "出错啦", "服务器异常，请稍后重试", "确认");
        return;
    }

    m_pWordModel->selectWordFromDatabase(m_pWordModel->currentWordLib(), m_pUserModel->getCurUser());
}

void studywordcontroller::setConnectinos()
{
    connect(m_pStudyWord, &studyWord::trans_to_studycenter, this ,&studywordcontroller::processingTransToStudyCenter);
    connect(m_pStudyWord, &studyWord::collectNewWord, this ,&studywordcontroller::processingCollectNewWord);
    connect(m_pStudyWord, &studyWord::addToReview, this ,&studywordcontroller::processingAddToReview);
    connect(m_pWordModel.get(), &wordModel::provideWord, this ,&studywordcontroller::processingProvideWord);
    connect(m_pWordModel.get(), &wordModel::handleCollectNewWordResult, this ,&studywordcontroller::processingCollectNewWordResult);
    connect(m_pWordModel.get(), &wordModel::handleAddToReviewResult, this ,&studywordcontroller::processingAddToReviewResult);
}




