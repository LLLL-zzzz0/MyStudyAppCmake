#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVector>
#include <QQueue>
#include <QString>
#include <QMutex>
#include <QMutexLocker>
#include <qthread.h>
#include <memory>
#include "appdata.h"

//数据库管理
class DataBaseManager
{
public:
    DataBaseManager() = delete;
    DataBaseManager(const DataBaseManager&) = delete;
    DataBaseManager& operator=(const DataBaseManager&) = delete;

    static bool initConnection(const QString& strHost, const QString& strDbName, const QString& strUser, const QString& strPassword, const QString& strDriver = "QODBC");

    //获取单词
    /*
      返回值
      -1 出错
      0-10   queueWord(最大为10，查询语句定义)
    */
    static int getWordsByLibrary(WordLibrary lib, QQueue<Word> &queueWord, const QString & strUser = "");

    //获取用户生词表单词
    /*
      返回值
      -1 出错
      0-500   本次vctWord新增的(最大为500，查询语句定义)
    */
    static int getUserNewWord(QVector<Word> &vctWord, const QString & strUser);


    //获取某个词库单词数量  用户名不为空则查找用户名下当前词库学习的单词数量
    //返回值 -1 出错, 其他int 查询条件下的单词数量
    static int getWordCount(WordLibrary wdLib, const QString& strUser = "");

    //判断某个词库用户是否全部学习过了
    //返回值    -1 出错， 0 否 ，1 是
    static int ifNoWordToLearn(WordLibrary wdLib, const QString& strUser);

    // 获取用户复习表或生词表单词数量
    // 返回值 -1 出错, 其他int 查询条件下的单词数量
    static int getUserRevOrNewWordCount(const QString& strUser, SelfType type);

    //查询记录是否存在 （用户复习表或生词表）
    //返回值    -1 出错， 0 否 ，1 是
    static int ifRecordExists(const QString& strUser, const QString& strWord, SelfType type);

    //插入记录 （用户复习表或生词表）
    //返回值    -1 失败,  1  成功
    static int insertRecord(const QString& strUser, const QString& strWord, SelfType type, const int &iReviewCount = 0);

    //更新复习表记录 （复习次数）
    //返回值    -1 失败, 1 成功
    static int updateReviewRecord(const QString& strUser, const QString& strWord);

    //删除生词表记录
    //返回值    -1 失败, 1 成功
    static int deleteNewWordRecord(const QString& strUser, const QString& strWord);

    //查询用户信息
    //1.登录时判断用户名与密码是否一致 ...需要返回密码串
    //2.注册时判断当前用户名是否注册过 ...无需返回
    //3.修改密码时判断用户输入的密码是否与输入一致 ...需要返回密码串
    //4.用户信息插入表
    static int selectUserInfo(userInfoSelType selType, const QString &strUser, QString *strUserPwd = nullptr);


template <typename... Args>
static bool execQuery(QSqlQuery &sqlQuery, const QString& strQuery, Args... args);

private:

    static bool reconnect();

    static QSqlDatabase m_sDb;
    static QMutex m_sMutex;
    static bool m_sbInitialized;

    static QString m_strHost;
    static QString m_strDbName;
    static QString m_strUser;
    static QString m_strPassword;
    static QString m_strDriver;
};

//执行查询语句
template<typename... Args>
bool DataBaseManager::execQuery(QSqlQuery &sqlQuery, const QString &strQuery, Args... args)
{
    int iRetryCount = 0;
    int iMaxRetryTimes = 3;

    QMutexLocker locker(&m_sMutex);

    while(iRetryCount < iMaxRetryTimes)
    {
        // 检查连接状态
        if(!m_sbInitialized || !m_sDb.isOpen() || !m_sDb.isValid())
        {
            qWarning() << "Database connection issue, attempting to reconnect...";
            if(!reconnect())
            {
                iRetryCount++;
                if(iRetryCount < iMaxRetryTimes)
                {
                    qWarning() << QString("Reconnect failed, retrying (%1/%2)...")
                    .arg(iRetryCount).arg(iMaxRetryTimes);
                    QThread::msleep(1000);
                }
                continue;
            }
        }

        // 重新创建查询对象（使用新的连接）
        sqlQuery = QSqlQuery(m_sDb);

        // 准备查询
        if(!sqlQuery.prepare(strQuery))
        {
            qWarning() << "Failed to prepare query:" << sqlQuery.lastError().text();
            qWarning() << "Query:" << strQuery;
            return false;
        }

        // 绑定参数
        QVector<QString> params = {args...};
        for (const auto& param : params)
        {
            sqlQuery.addBindValue(param);
        }

        // 执行查询
        if(sqlQuery.exec())
        {
            return true;
        }
        else
        {
            QSqlError error = sqlQuery.lastError();

            // 检查是否是连接错误
            if(error.type() == QSqlError::ConnectionError)
            {
                qWarning() << "Connection error during query execution:" << error.text();

                m_sbInitialized = false;
                iRetryCount++;
                if(iRetryCount < iMaxRetryTimes)
                {
                    QThread::msleep(1000);
                }
                continue;
            }
            else
            {
                qWarning() << "Query execution failed:" << error.text();
                qWarning() << "Query:" << strQuery;
                return false;
            }
        }
    }

    qWarning() << "Failed to execute query";
    return false;
}

#endif // DATABASEMANAGER_H
