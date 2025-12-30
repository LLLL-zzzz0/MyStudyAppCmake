#include "databaseManager.h"

QSqlDatabase DataBaseManager::m_sDb;
QMutex DataBaseManager::m_sMutex;
bool DataBaseManager::m_sbInitialized = false;

QString DataBaseManager::m_strHost;
QString DataBaseManager::m_strDbName;
QString DataBaseManager::m_strUser;
QString DataBaseManager::m_strPassword;
QString DataBaseManager::m_strDriver;

 bool DataBaseManager::initConnection(const QString& strHost, const QString& strDbName, const QString& strUser, const QString& strPassword, const QString& strDriver)
{
    QMutexLocker locker(&m_sMutex);

    m_strHost = strHost;
    m_strDbName = strDbName;
    m_strUser = strUser;
    m_strPassword = strPassword;
    m_strDriver = strDriver;

    m_sDb = QSqlDatabase::addDatabase(strDriver);
    m_sDb.setHostName(strHost);
    m_sDb.setDatabaseName(strDbName);
    m_sDb.setUserName(strUser);
    m_sDb.setPassword(strPassword);
    m_sbInitialized = m_sDb.open();
    if (!m_sbInitialized)
    {
        qWarning() << "Failed to connect to database:" << m_sDb.lastError().text();
    }

    return m_sbInitialized;
}

int DataBaseManager::getWordsByLibrary(WordLibrary lib, QQueue<Word> &queueWord, const QString &strUser)
{
    QSqlQuery sqlQuery;
    QString strSql;
    int iCount = 0;
    switch (lib)
    {
        case CET_4:
        {
            strSql = sqlQuery_getWordFromCET_4;
            break;
        }
        case CET_6:
        {
            strSql = sqlQuery_getWordFromCET_6;
            break;
        }
        case KY:
        {
            strSql = sqlQuery_getWordFromKY;
            break;
        }
        case USER_REVIEW:
        {
            strSql = sqlQuery_getUserReviewWords;
            break;
        }
        default:
        {
            return -1;
            break;
        }
    }

    if(WordLibrary::USER_REVIEW == lib)
    {
        if(!execQuery(sqlQuery, strSql, strUser))
        {
            return -1;
        }
    }
    else
    {
        if(!execQuery(sqlQuery, strSql))
        {
            return -1;
        }
    }

    while(sqlQuery.next())
    {
        Word wd;
        wd.strWord = sqlQuery.value(0).toString();
        wd.strMeaning = sqlQuery.value(1).toString();
        wd.strYinbiao = sqlQuery.value(2).toString();
        wd.strExampleSentence = sqlQuery.value(3).toString();
        wd.strExampleSentenceMeaning = sqlQuery.value(4).toString();

        queueWord.enqueue(wd);
        iCount++;
    }

    return iCount;
}

int DataBaseManager::getUserNewWord(QVector<Word> &vctWord, const QString &strUser)
{
    QSqlQuery sqlQuery;
    QString strSql = sqlQuery_getUserNewWords;
    int iCount = 0;

    if(!execQuery(sqlQuery, strSql, strUser))
    {
        return -1;
    }

    while(sqlQuery.next())
    {
        Word wd;
        wd.strWord = sqlQuery.value(0).toString();
        wd.strMeaning = sqlQuery.value(1).toString();
        wd.strYinbiao = sqlQuery.value(2).toString();
        wd.strExampleSentence = sqlQuery.value(3).toString();
        wd.strExampleSentenceMeaning = sqlQuery.value(4).toString();

        vctWord.push_back(wd);
        iCount++;
    }

    return iCount;
}

int DataBaseManager::getWordCount(WordLibrary wdLib, const QString& strUser)
{
    QString strSql;
    QSqlQuery sqlQuery;
    switch (wdLib)
    {
        case CET_4:
        {
            if("" == strUser)
            {
                strSql = sqlQuery_getWordsCount_CET_4;
            }
            else
            {
                strSql = sqlQuery_getUserLearnedCount_CET_4;
            }
            break;
        }
        case CET_6:
        {
            if("" == strUser)
            {
                strSql = sqlQuery_getWordsCount_CET_6;
            }
            else
            {
                strSql = sqlQuery_getUserLearnedCount_CET_6;
            }
            break;
        }
        case KY:
        {
            if("" == strUser)
            {
                strSql = sqlQuery_getWordsCount_KY;
            }
            else
            {
                strSql = sqlQuery_getUserLearnedCount_KY;
            }
            break;
        }
        default:
        {
            return -1;
            break;
        }
    }

    if("" == strUser)
    {
        if(!execQuery(sqlQuery, strSql))
        {
            return -1;
        }
    }
    else
    {
        if(!execQuery(sqlQuery, strSql, strUser))
        {
            return -1;
        }
    }

    if(!sqlQuery.next())
    {
        return -1;
    }

    return sqlQuery.value(0).toInt();
}

int DataBaseManager::ifNoWordToLearn(WordLibrary wdLib, const QString &strUser)
{
    int iWordCount = getWordCount(wdLib);
    int iWordLearned = getWordCount(wdLib, strUser);
    if((-1 != iWordCount) && (-1 != iWordLearned))
    {
        if(iWordCount == iWordLearned)
        {
            return 1;
        }

        return 0;
    }

    return -1;
}

int DataBaseManager::getUserRevOrNewWordCount(const QString &strUser, SelfType type)
{
    QSqlQuery sqlQuery;
    QString strSql;

    switch(type)
    {
        case REVIEW:
        {
            strSql = sqlQuery_getUserReviewWordCount;
            break;
        }
        case NEWWORD:
        {
            strSql = sqlQuery_getUserNewWordCount;
            break;
        }
        default:
        {
            return -1;
            break;
        }
    }

    if(!execQuery(sqlQuery, strSql, strUser))
    {
        return -1;
    }

    if(!sqlQuery.next())
    {
        return -1;
    }

    return sqlQuery.value(0).toInt();
}

int DataBaseManager::ifRecordExists(const QString &strUser, const QString &strWord, SelfType type)
{
    QString strSql;
    switch (type)
    {
        case REVIEW:
        {
            strSql = sqlQuery_ifRecordExist_Review;
            break;
        }
        case NEWWORD:
        {
            strSql = sqlQuery_ifRecordExist_NewWord;
            break;
        }
        default:
        {
            return -1;
            break;
        }
    }

    QSqlQuery sqlQuery;
    if(!execQuery(sqlQuery, strSql, strUser, strWord))
    {
        return -1;
    }

    if(sqlQuery.next())
    {
        return 1;
    }

    return 0;
}

int DataBaseManager::insertRecord(const QString &strUser, const QString &strWord, SelfType type, const int &iReviewCount)
{
    QString strSql;
    QSqlQuery sqlQuery;
    switch (type)
    {
        case REVIEW:
        {
            strSql = sqlQuery_insertToReview;
            if(!execQuery(sqlQuery, strSql, strUser, strWord, QString::number(iReviewCount)))
            {
                return -1;
            }
            break;
        }
        case NEWWORD:
        {
            strSql = sqlQuery_insertToNewWord;
            if(!execQuery(sqlQuery, strSql, strUser, strWord))
            {
                return -1;
            }
            break;
        }
        default:
        {
            return -1;
            break;
        }
    }

    return 1;
}

int DataBaseManager::updateReviewRecord(const QString &strUser, const QString &strWord)
{
    QSqlQuery sqlQuery1;
    QSqlQuery sqlQuery2;
    int iRevTimes = 0;

    if(!execQuery(sqlQuery1, sqlQuery_selectReviewTimes, strUser, strWord))
    {
        return -1;
    }

    if(sqlQuery1.next())
    {
        iRevTimes = sqlQuery1.value(0).toInt() + 1;
    }
    else
    {
        return -1;
    }

    if(execQuery(sqlQuery2, sqlQuery_upadteReviewTimes, QString::number(iRevTimes), strUser, strWord))
    {
        return 1;
    }

    return -1;
}

int DataBaseManager::deleteNewWordRecord(const QString &strUser, const QString &strWord)
{
    QSqlQuery sqlQuery;
    if(!DataBaseManager::execQuery(sqlQuery, sqlQuery_deleteNewWordRecord, strUser, strWord))
    {
        return -1;
    }

    return 1;
}

bool DataBaseManager::reconnect()
{
    // 关闭现有连接
    if(m_sDb.isOpen())
    {
        m_sDb.close();
    }

    // 使用保存的连接信息重新连接
    m_sDb = QSqlDatabase::addDatabase(m_strDriver);
    m_sDb.setHostName(m_strHost);
    m_sDb.setDatabaseName(m_strDbName);
    m_sDb.setUserName(m_strUser);
    m_sDb.setPassword(m_strPassword);

    m_sbInitialized = m_sDb.open();
    if (m_sbInitialized)
    {
        qDebug() << "Database reconnected successfully";
    }
    else
    {
        qWarning() << "Failed to reconnect to database:" << m_sDb.lastError().text();
    }

    return m_sbInitialized;
}

int DataBaseManager::selectUserInfo(userInfoSelType selType, const QString &strUser,  QString *strUserPwd)
{
    QSqlQuery query;

    switch (selType)
    {
        case USER_EXIST:
        {
            if(!execQuery(query, sqlQuery_getUserinfo, strUser))
            {
                return EXECERROR;
            }

            if(query.next())
            {
                return EXECHASRESULT;
            }
            else
            {
                return EXECNORESULT;
            }

            break;
        }
        case USER_PWD:
        {
            if(!execQuery(query, sqlQuery_getUserinfo, strUser))
            {
                return EXECERROR;
            }

            if(query.next())
            {
                (*strUserPwd) = query.value(1).toString();
                return EXECHASRESULT;
            }
            else
            {
                return EXECNORESULT;
            }

            break;
        }
        case UPDATE_USER_PWD:
        {
            if(!execQuery(query, sqlQuery_UpdateUserPwd, *strUserPwd, strUser))
            {
                return EXECERROR;
            }

            return EXECHASRESULT;

            break;
        }
        case INSERT_USER_INFO:
        {
            if(!execQuery(query, sqlQuery_InsertUserinfo, strUser, *strUserPwd))
            {
                return EXECERROR;
            }

            return EXECHASRESULT;

            break;
        }
        default:
        {
            break;
        }
    }

    return EXECERROR;
}



