#include "newWordController.h"

newwordcontroller::newwordcontroller(QSharedPointer<userModel> pUserModel, QSharedPointer<wordModel> pWordModel, newWord *pNewWord, QObject *parent)
:QObject{parent},
    m_pUserModel(pUserModel),
    m_pWordModel(pWordModel),
    m_pNewWord(pNewWord)
{
    setConnections();
}

void newwordcontroller::initMyViewData()
{
    m_pNewWord->setIPage(0);
    m_pWordModel->getWordCount(m_pUserModel->getCurUser());
    m_pWordModel->selectNewWordFromDatabase(m_pUserModel->getCurUser(), m_pNewWord->iPage());
}

void newwordcontroller::processingSwitchToStudyCenter()
{
    emit switchToStudyCenter(STUDYCENTER);
    m_pNewWord->hide();
}

void newwordcontroller::processingProvideNewWord(bool bSuccess, bool bIsFirstPage, bool bIslastPage, const QVector<Word> &vctWord, const QString &strMessage)
{
    if(!bSuccess)
    {
        return ;
    }

    int index = 0;
    for(Word wd:vctWord)
    {
        m_pNewWord->setText(index, wd);
        index++;
    }

    m_pNewWord->showButton(bIsFirstPage, bIslastPage);
}

void newwordcontroller::processingRetWordCount(bool bSuccess, const int &iCount)
{
    if(!bSuccess)
    {
        qDebug() << "get word count";
        return;
    }

    m_pNewWord->setWordCount(iCount);
}

void newwordcontroller::processingGetPrivousPage()
{
    m_pWordModel->selectNewWordFromDatabase(m_pUserModel->getCurUser(), m_pNewWord->iPage());
}

void newwordcontroller::processingGetNextPage()
{
    m_pWordModel->selectNewWordFromDatabase(m_pUserModel->getCurUser(), m_pNewWord->iPage());
}

void newwordcontroller::setConnections()
{
    connect(m_pNewWord, &newWord::trans_to_studycenter, this, &newwordcontroller::processingSwitchToStudyCenter);
    connect(m_pNewWord, &newWord::showNextPage, this, &newwordcontroller::processingGetNextPage);
    connect(m_pNewWord, &newWord::showPrivousPage, this, &newwordcontroller::processingGetPrivousPage);
    connect(m_pWordModel.get(), &wordModel::provideNewWord, this, &newwordcontroller::processingProvideNewWord);
    connect(m_pWordModel.get(), &wordModel::retWordCount, this, &newwordcontroller::processingRetWordCount);
}


