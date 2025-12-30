#include <QFile>
#include <QApplication>
#include <QTextStream>
#include "databaseManager.h"
#include "applicationController.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QFile file(":/qss/style-1.qss");
    file.open(QFile::ReadOnly);
    QTextStream filetext(&file);
    QString stylesheet = filetext.readAll();
    app.setStyleSheet(stylesheet);
    file.close();

    app.setWindowIcon(QIcon(":/logo.ico"));

    bool bIsOpen = DataBaseManager::initConnection("localhost", "WordLearningDB", "sa", "123456");
    if(!bIsOpen)
    {
        qWarning() << "Database not open!";
    }

    applicationController *appController = new applicationController();

    // 确保应用程序退出时删除控制器
    QObject::connect(&app, &QApplication::aboutToQuit, appController, &applicationController::deleteLater);

    return app.exec();
}
