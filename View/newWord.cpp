#include "newWord.h"
#include "ui_newWord.h"

newWord::newWord(QWidget *parent) :
    myWidget(parent),
    ui(new Ui::reword2)
{
    ui->setupUi(this);
    init();

}

newWord::~newWord()
{
    delete ui;
}

void newWord::init()
{
    for(int i = 1;i <= 10; i++)
    {
        m_pButtonArray[i - 1] = findChild<QPushButton*>("btn_word_" + QString::number(i));
        m_pLabelArray[i - 1] = findChild<QLabel*>("label_wordmeaning_" + QString::number(i));
    }

    disableAllChildrenFocus();
    setConnections();
}

void newWord::setConnections()
{
    connect(ui->btn_return, &QPushButton::clicked, this, &newWord::transToStudyCenter);
    connect(ui->btn_last, &QPushButton::clicked, this, &newWord::getPrivousPage);
    connect(ui->btn_next, &QPushButton::clicked, this, &newWord::getNextPage);
}

int newWord::iPage() const
{
    return m_iPage;
}

void newWord::setIPage(int newIPage)
{
    m_iPage = newIPage;
}

void newWord::setText(const int &index, const Word &wd)
{
    m_pButtonArray[index]->setText(wd.strWord);
    m_pLabelArray[index]->setText(wd.strMeaning);
}

void newWord::showButton(bool bFirst, bool bLast)
{
    if(bFirst)
    {
        ui->btn_last->hide();
    }
    else
    {
        ui->btn_last->show();
    }

    if(bLast)
    {
        ui->btn_next->hide();
    }
    else
    {
        ui->btn_next->show();
    }
}

void newWord::setWordCount(const int &iCount)
{
    ui->label_nouse->setText("共计" + QString::number(iCount) + "词");
}

void newWord::clearWord()
{
    for(int i = 0; i < 10; i++)
    {
        m_pButtonArray[i]->setText("");
        m_pLabelArray[i]->setText("");
    }
}

void newWord::transToStudyCenter()
{
    emit trans_to_studycenter();
}

void newWord::getPrivousPage()
{
    m_iPage--;
    clearWord();
    emit showPrivousPage();
}

void newWord::getNextPage()
{
    m_iPage++;
    clearWord();
    emit showNextPage();
}

void newWord::closeEvent(QCloseEvent *event)
{
    // 发送返回信号
    emit trans_to_studycenter();
    event->accept();  // 接受关闭事件
}



