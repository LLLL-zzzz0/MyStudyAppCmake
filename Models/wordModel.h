#ifndef WORDMODEL_H
#define WORDMODEL_H

#include <QObject>
#include <QQueue>
#include "databaseManager.h"

class wordModel : public QObject
{
    Q_OBJECT
public:
    explicit wordModel(QObject *parent = nullptr);

    //从数据库查询
    void selectWordFromDatabase(WordLibrary wordlib, const QString &strUserName);

    //获取CET_4,CET_6,KY单词
    void processWordlib(WordLibrary wordlib, QQueue<Word>& queueWord, const QString &strUserName);

    //获取生词表
    void selectNewWordFromDatabase(const QString &strUserName, const int &iPage);

    //获取分页数据
    void getPageData(QVector<Word> &vctWord, const int &iPage);

    //处理生词表数据查询
    void processNewWordDataSelect(const QString &strUserName, QVector<Word> &vctWord, const int &iPage);

    //处理studyWord收藏生词
    void handleCollectNewWord(const QString &strWord, bool bIsNewWord);

    //处理studyWord 的AddToReview
    void handleAddToReview(const QString &strWord, bool bIncreaseReviewTime);

    //验证review用户输入是否正确
    void verifyUserInput(const QString &strUserInput);

    //获取下一个复习单词
    void getNextReviewWord();

    //更新用户的生词表缓存
    void updateUserNewwordCache(const QString &strUser);

    //获取生词表单词数量
    void getWordCount(const QString& strUser = "");

    //获取单词数量
    int getWordCount(SelfType wordType, const QString& strUser);

    WordLibrary currentWordLib() const;
    void setCurrentWordLib(WordLibrary newCurrentWordLib);

signals:
    void verifyUserInputResult(bool bCorrect, const Word &wd);
    void provideWord(bool bSuccess, const Word &wd, bool bIsNewWord, const QString &strMessage);
    void provideReviewWord(bool bSuccess, const Word &wd, const QString& strMessage);
    void handleCollectNewWordResult(bool bSuccess);
    void handleAddToReviewResult(bool bSuccess);
    void provideNewWord(bool bSuccess, bool bIsFirstPage, bool bIslastPage, const QVector<Word> &ctWord, const QString &strMessage);
    void retWordCount(bool bSuccess, const int& iCount);
private:
    //StudyWord 单词缓存
    QQueue<Word> m_queueCET4Word;
    QQueue<Word> m_queueCET6Word;
    QQueue<Word> m_queueKYWord;

    //ReviewWord 单词缓存
    QQueue<Word> m_queueReviewWord;
    //NewWord 单词缓存
    QVector<Word> m_vctNewWord;

    QString m_strUserName;
    WordLibrary m_currentWordLib;
};

#endif // WORDMODEL_H
