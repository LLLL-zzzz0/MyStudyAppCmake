#ifndef MYWIDGHT_H
#define MYWIDGHT_H

#include <QWidget>
#include <QEvent>
#include <QKeyEvent>
#include <QLineEdit>

class myWidget: public QWidget
{
    Q_OBJECT

public:
    myWidget(QWidget *parent = nullptr);
    bool eventFilter(QObject *pObject, QEvent *pEvent) override;
    void disableAllChildrenFocus();
};

#endif // MYWIDGHT_H
