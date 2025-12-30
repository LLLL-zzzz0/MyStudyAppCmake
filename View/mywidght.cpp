#include "mywidght.h"


myWidget::myWidget(QWidget *parent):
    QWidget(parent)
{
    this->installEventFilter(this);
}

bool myWidget::eventFilter(QObject *pObject, QEvent *pEvent)
{
    if(pEvent->type() == QEvent::KeyPress)
    {
        QKeyEvent *pKeyEvent = static_cast<QKeyEvent*>(pEvent);

        if(pObject == this)
        {
            if(pKeyEvent->key() == Qt::Key_Enter || pKeyEvent->key() == Qt::Key_Return || pKeyEvent->key() == Qt::Key_Space)
            {
                return true;
            }
            else if (pKeyEvent->key() == Qt::Key_Escape)
            {
                return true;
            }
        }
    }

    return QWidget::eventFilter(pObject, pEvent);
}

void myWidget::disableAllChildrenFocus()
{
    // 获取对话框的所有子控件
    QList<QWidget*> allWidgets = this->findChildren<QWidget*>();

    // 遍历所有子控件，设置焦点策略为 NoFocus
    foreach(QWidget* widget, allWidgets)
    {
        if(qobject_cast<QLineEdit*>(widget))
        {
            widget->setFocusPolicy(Qt::StrongFocus);
        }
        else
        {
            widget->setFocusPolicy(Qt::NoFocus);
        }
    }

    // 但保留对话框本身的焦点策略，以便能接收键盘事件
    this->setFocusPolicy(Qt::StrongFocus);
    this->setFocus();
}
