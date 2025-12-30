#ifndef APPDATA_H
#define APPDATA_H

#include <QString>

#define sqlQuery_getUserinfo                    "select user_name,pwd from dbo.user_info where (user_name=?)"
#define sqlQuery_UpdateUserPwd                  "update dbo.user_info set pwd = ? where(user_name=?);"
#define sqlQuery_InsertUserinfo                 "insert into dbo.user_info (user_name,pwd) values(?,?)"
#define sqlQuery_getWordsCount_CET_4            "select count(*) from dbo.words where (cet_4=1)"
#define sqlQuery_getWordsCount_CET_6            "select count(*) from dbo.words where (cet_6=1)"
#define sqlQuery_getWordsCount_KY               "select count(*) from dbo.words where (ky=1)"
#define sqlQuery_getUserLearnedCount_CET_4      "select count(*) from dbo.review where (user_name = ?) and wd in ( select wd from dbo.CET_4 )"
#define sqlQuery_getUserLearnedCount_CET_6      "select count(*) from dbo.review where (user_name = ?) and wd in ( select wd from dbo.CET_6 )"
#define sqlQuery_getUserLearnedCount_KY         "select count(*) from dbo.review where (user_name = ?) and wd in ( select wd from dbo.ky )"
#define sqlQuery_getUserReviewWordCount         "select count(*) from dbo.review where (user_name = ?)"
#define sqlQuery_getUserNewWordCount            "select count(*) from dbo.idtf_wd where (user_name = ?)"
#define sqlQuery_getWordFromCET_4               "select top 10 * from dbo.cet_4 order by newid()"
#define sqlQuery_getWordFromCET_6               "select top 10 * from dbo.cet_6 order by newid()"
#define sqlQuery_getWordFromKY                  "select top 10 * from dbo.ky order by newid()"
#define sqlQuery_ifRecordExist_NewWord          "select 1 from dbo.idtf_wd where user_name = ? and wd = ?"
#define sqlQuery_ifRecordExist_Review           "select 1 from dbo.review where user_name = ? and wd = ?"
#define sqlQuery_insertToReview                 "insert into dbo.review (user_name,wd,rv_tms) values(?,?,?);"
#define sqlQuery_insertToNewWord                "insert into dbo.idtf_wd (user_name,wd) values(?,?);"
#define sqlQuery_selectReviewTimes              "select rv_tms from dbo.review where user_name = ? and wd = ?"
#define sqlQuery_upadteReviewTimes              "update dbo.review set rv_tms = ? where (user_name = ?) and (wd = ?)"
#define sqlQuery_deleteNewWordRecord            "delete from dbo.idtf_wd where(user_name = ? and wd = ?);"
#define sqlQuery_getUserReviewWords             "SELECT wd,meaning,yb,eps,eps_meaning from words where wd in (SELECT TOP 10 WD FROM DBO.review WHERE user_name=? ORDER BY rv_tms)"
#define sqlQuery_getUserNewWords                "select wd,meaning,yb,eps,eps_meaning from words where wd in (SELECT wd from dbo.idtf_wd where user_name = ?)"


#define EXECERROR        -1
#define EXECHASRESULT     1
#define EXECNORESULT      0

enum WordLibrary
{
    CET_4,
    CET_6,
    KY,
    USER_REVIEW,
    USER_NEWWORD
};

enum SelfType
{
    //用户使用过程中新增表记录
    REVIEW, //复习表
    NEWWORD  //生词表
};

struct Word
{
    QString strWord;
    QString strMeaning;
    QString strYinbiao;
    QString strExampleSentence;
    QString strExampleSentenceMeaning;

    Word():strWord(""),strMeaning(""),strYinbiao(""),strExampleSentence(""),strExampleSentenceMeaning(""){}
};

enum userInfoSelType
{
    USER_EXIST, //查询用户名是否已存在
    USER_PWD,  //查询用户密码
    UPDATE_USER_PWD, //更新用户密码
    INSERT_USER_INFO //插入用户信息
};


#endif // APPDATA_H
