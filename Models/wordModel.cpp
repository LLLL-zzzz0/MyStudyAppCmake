#include "wordModel.h"

wordModel::wordModel(QObject *parent)
    : QObject{parent}
{}

void wordModel::selectWordFromDatabase(WordLibrary wordlib, const QString &strUserName)
{
    switch (wordlib)
    {
        case CET_4:
        {
            processWordlib(wordlib, m_queueCET4Word, strUserName);
            break;
        }
        case CET_6:
        {
            processWordlib(wordlib, m_queueCET6Word, strUserName);
            break;
        }
        case KY:
        {
            processWordlib(wordlib, m_queueKYWord, strUserName);
            break;
        }
        case USER_REVIEW:
        {
            if(m_strUserName == strUserName)
            {
                if(m_queueReviewWord.empty())
                {
                    int iRet = DataBaseManager::getWordsByLibrary(wordlib, m_queueReviewWord, m_strUserName);
                    if(iRet <= 0)
                    {
                        emit provideReviewWord(false, Word(), "数据异常，请稍后重试");
                        return ;
                    }
                }

                emit provideReviewWord(true, m_queueReviewWord.front(),  "success");
            }
            else
            {
                m_strUserName = strUserName;
                m_queueReviewWord.clear();

                int iRet1 = DataBaseManager::getWordsByLibrary(wordlib, m_queueReviewWord, m_strUserName);
                if(iRet1 <= 0)
                {
                    emit provideReviewWord(false, Word(),  "数据异常，请稍后重试");
                    return ;
                }

                emit provideReviewWord(true, m_queueReviewWord.front(), "success");
            }
            break;
        }
        default:
        {
            emit provideReviewWord(false, Word(), "数据异常，请稍后重试");
            break;
        }
    }
}

void wordModel::processWordlib(WordLibrary wordlib, QQueue<Word> &queueWord, const QString &strUserName)
{
    if(m_strUserName == strUserName)
    {
        if(queueWord.empty())
        {
            int iRet = DataBaseManager::getWordsByLibrary(wordlib, queueWord);
            if(iRet <= 0)
            {
                emit provideWord(false, Word(), false, "数据异常，请稍后重试");
                return ;
            }
        }

        int iRet = DataBaseManager::ifRecordExists(m_strUserName, queueWord.front().strWord, NEWWORD);
        if(1 == iRet)
        {
            emit provideWord(true, queueWord.dequeue(), true, "success");
        }
        else
        {
            emit provideWord(true, queueWord.dequeue(), false, "success");
        }
    }
    else
    {
        m_strUserName = strUserName;
        queueWord.clear();

        int iRet1 = DataBaseManager::getWordsByLibrary(wordlib, queueWord);
        if(iRet1 <= 0)
        {
            emit provideWord(false, Word(), false, "数据异常，请稍后重试");
            return ;
        }

        int iRet2 = DataBaseManager::ifRecordExists(m_strUserName, queueWord.front().strWord, NEWWORD);
        if(1 == iRet2)
        {
            emit provideWord(true, queueWord.dequeue(), true, "success");
        }
        else
        {
            emit provideWord(true, queueWord.dequeue(), false, "success");
        }
    }
}

void wordModel::selectNewWordFromDatabase(const QString &strUserName, const int &iPage)
{
    if(m_strUserName == strUserName)
    {
        if(m_vctNewWord.empty())
        {
            processNewWordDataSelect(strUserName, m_vctNewWord, iPage);
        }
        else
        {
           getPageData(m_vctNewWord, iPage);
        }
    }
    else
    {
        m_strUserName = strUserName;
        m_vctNewWord.clear();

        processNewWordDataSelect(strUserName, m_vctNewWord, iPage);
    }
}

void wordModel::getPageData(QVector<Word> &vctWord, const int &iPage)
{
    bool isFirstPage = false;
    bool isLastPage = false;
    QVector<Word>::Iterator itFirst = vctWord.begin() + iPage*10;
    int iTotalPages = vctWord.size() / 10;
    if(vctWord.size() % 10)
    {
        iTotalPages++;
    }

    if(iPage == 0)
    {
        isFirstPage = true;
    }

    if(iPage == (iTotalPages - 1))
    {
        isLastPage = true;
    }

    //一页的情况 或者最后一页 -路径压缩
    if((isFirstPage && isLastPage) || isLastPage)
    {
        QVector<Word> vctTemp(itFirst, vctWord.end());
        emit provideNewWord(true, isFirstPage, isLastPage, vctTemp, "success");
    }
    else
    {
        QVector<Word>::Iterator itEnd = vctWord.begin() + (iPage+1)*10;
        QVector<Word> vctTemp(itFirst, itEnd);
        emit provideNewWord(true, isFirstPage, isLastPage, vctTemp, "success");
    }
}

void wordModel::processNewWordDataSelect(const QString &strUserName, QVector<Word> &vctWord, const int &iPage)
{
    int iRet = DataBaseManager::getUserNewWord(vctWord, strUserName);
    if(-1 == iRet)
    {
        QVector<Word> vctWord;
        emit provideNewWord(false, false, false, vctWord, "数据异常，请稍后重试");
    }
    else if(0 == iRet)
    {
        QVector<Word> vctWord;
        emit provideNewWord(true, true, true, vctWord, "用户未收藏单词");
    }
    else
    {
        getPageData(m_vctNewWord, iPage);
    }
}

void wordModel::handleCollectNewWord(const QString &strWord, bool bIsNewWord)
{
    int iRet = -1;
    if(bIsNewWord)
    {
        iRet = DataBaseManager::deleteNewWordRecord(m_strUserName, strWord);
        if(-1 == iRet)
        {
            emit handleCollectNewWordResult(false);
            return ;
        }

        emit handleCollectNewWordResult(true);
    }
    else
    {

        iRet = DataBaseManager::insertRecord(m_strUserName, strWord, SelfType::NEWWORD);
        if(-1 == iRet)
        {
            emit handleCollectNewWordResult(false);
            return ;
        }

        emit handleCollectNewWordResult(true);
    }
}

void wordModel::handleAddToReview(const QString &strWord, bool bIncreaseReviewTime)
{
    int iRet = DataBaseManager::ifRecordExists(m_strUserName, strWord, SelfType::REVIEW);

    if(-1 == iRet)
    {
        emit handleAddToReviewResult(false);
        return ;
    }
    else if(0 == iRet)
    {
        int iiRet = -1;

        if(bIncreaseReviewTime)
        {
            iiRet = DataBaseManager::insertRecord(m_strUserName, strWord, SelfType::REVIEW, 1);
        }
        else
        {
            iiRet = DataBaseManager::insertRecord(m_strUserName, strWord, SelfType::REVIEW, 0);
        }

        if(-1 == iiRet)
        {
            emit handleAddToReviewResult(false);
            return ;
        }

        emit handleAddToReviewResult(true);
    }
    else
    {
        if(bIncreaseReviewTime)
        {
            int iiRet = DataBaseManager::updateReviewRecord(m_strUserName, strWord);
            if(-1 == iiRet)
            {
                emit handleAddToReviewResult(false);
                return;
            }
        }

        emit handleAddToReviewResult(true);
    }
}

void wordModel::verifyUserInput(const QString &strUserInput)
{
    if(!strUserInput.length())
    {
        emit verifyUserInputResult(false, m_queueReviewWord.front());
    }

    QString strUserInputCopy = strUserInput.simplified();
    QString strWord = m_queueReviewWord.front().strWord.simplified();

    if(strUserInputCopy == strWord)
    {
        DataBaseManager::updateReviewRecord(m_strUserName, m_queueReviewWord.front().strWord);
        emit verifyUserInputResult(true, m_queueReviewWord.front());
        return ;
    }

    emit verifyUserInputResult(false, m_queueReviewWord.front());
}

void wordModel::getNextReviewWord()
{
    m_queueReviewWord.dequeue();
    selectWordFromDatabase(USER_REVIEW, m_strUserName);
}

void wordModel::updateUserNewwordCache(const QString &strUser)
{
    m_vctNewWord.clear();
    int iRet = DataBaseManager::getUserNewWord(m_vctNewWord, strUser);
    if(-1 == iRet)
    {
        qDebug() << "updateUserNewwordCache Error";
        return;
    }
}

void wordModel::getWordCount(const QString &strUser)
{
    int iRet = DataBaseManager::getUserRevOrNewWordCount(strUser, NEWWORD);
    if(-1 == iRet)
    {
        emit retWordCount(false, -1);
        return;
    }

    emit retWordCount(true, iRet);
}

int wordModel::getWordCount(SelfType wordType, const QString &strUser)
{
    return DataBaseManager::getUserRevOrNewWordCount(strUser, wordType);
}

WordLibrary wordModel::currentWordLib() const
{
    return m_currentWordLib;
}

void wordModel::setCurrentWordLib(WordLibrary newCurrentWordLib)
{
    m_currentWordLib = newCurrentWordLib;
}










