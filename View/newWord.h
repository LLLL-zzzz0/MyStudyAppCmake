#ifndef NEWWORD_H
#define NEWWORD_H

#include <QDialog>
#include <QDebug>
#include <QMessageBox>
#include <QVector.h>
#include "mywidght.h"
#include "appdata.h"

namespace Ui {
class reword2;
}

//生词本
class newWord : public myWidget
{
    Q_OBJECT

public:
    explicit newWord(QWidget *parent = nullptr);
    ~newWord();

    //获取当前页
    int iPage() const;
    void setIPage(int newIPage);

    //设置单词文本
    void setText(const int &index, const Word &wd);

    //显示按钮
    void showButton(bool bFirst, bool bLast);

    //设置单词数量
    void setWordCount(const int &iCount);

    //清理单词
    void clearWord();

signals:
    //转到studycenter的信号
    void trans_to_studycenter();
    //切换页面
    void showNextPage();
    void showPrivousPage();
private slots:
    void transToStudyCenter();
    void getPrivousPage();
    void getNextPage();
protected:
    void closeEvent(QCloseEvent *event) override;

private:
    void init();
    void setConnections();

    Ui::reword2 *ui;
    int m_iPage;
    QPushButton *m_pButtonArray[10];
    QLabel      *m_pLabelArray[10];
};

#endif // NEWWORD_H
