#include "mainwindow.h"
#include <QApplication>
#include "qdebug.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    qDebug("argc: %d, argv: ", argc);
    for (int i = 0; i < argc; i++)
    {
        qDebug("%s", argv[i]);
    }
    if (argc < 3)
    {   //TODO:鼠标直接操作，展示图形化界面
        w.show();
    }
    else if (argc == 3)
    {   //命令行启动，直接运行结果，return 0是为了防止一直挂着
        w.Input(argv[1], argv[2]);
        return 0;
    }


    return a.exec();
}
