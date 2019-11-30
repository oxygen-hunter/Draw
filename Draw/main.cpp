#include "mainwindow.h"
#include <QApplication>
#include "qdebug.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    qDebug("argc: %d, argv: ", argc);
    for (int i = 0; i < argc; i++)
    {
        qDebug("%s", argv[i]);
    }
    if (argc < 3)
    {   //TODO:鼠标直接操作

    }
    else if (argc == 3)
    {   //命令行启动
        w.Input(argv[1], argv[2]);
    }


    return a.exec();
}
