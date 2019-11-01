#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Line.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_pCanvas = ui->CanvasLabel;
    m_nCanvasWidth = 600;
    m_nCanvasHeight = 400;
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{

}


//记录图片输出目录，打开input.txt，循环读指令
bool MainWindow::Input(QString InputFileName, QString SaveDirectoryName)
{
    m_SaveDirectoryName = SaveDirectoryName + "\\";

    QFile InputFile(InputFileName);
    if (!InputFile.exists())
    {
        qDebug() << InputFileName << " not exist." << endl;
        return false;
    }
    if (!InputFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << InputFileName << " can't open." << endl;
        return false;
    }
    while (!InputFile.atEnd())
    {
        QByteArray Line = InputFile.readLine();
        QString Command(Line);
        Command.remove(QChar('\n'), Qt::CaseInsensitive);
        //qDebug() << Command;
        Execute(Command);
    }
    InputFile.close();

    return true;

    //test
    for (int i = 50; i < 90; i++)
    {
        m_Pixels.push_back(XPixel(i, 50, 200, 200, 200));
    }

    //test for resetCanvas
    //ResetCanvas(100, 100);

    //test for saveCanvas
    SaveCanvas("test1");

    //test for setColor
    SetColor(0, 0, 205);

    //test for drawLine DDA
    DrawLine(1, 150, 150, 250, 250, emDDA);
    SaveCanvas("test2");
    ResetCanvas(1000, 1000);

    SetColor(0xee, 0x40, 0x0);
    DrawLine(2, 300, 300, 300, 400, emDDA);
    SaveCanvas("test3");

    ResetCanvas(500, 300);
    SetColor(0xad, 0xff, 0x2f);
    DrawLine(3, 150, 150, 150, 200, emDDA);
    SaveCanvas("test4");

    return true;
}


//解析每句指令
bool MainWindow::Execute(QString Command)
{
    QStringList Tokens = Command.split(" ");
    for (int i = 0; i < Tokens.size(); i++)
    {
        qDebug() << Tokens.at(i);
    }
    QString Action = Tokens.at(0);
    if (Action == "resetCanvas")
    {
        int nWidth, nHeight;
        nWidth = Tokens.at(1).toInt();
        nHeight = Tokens.at(2).toInt();
        ResetCanvas(nWidth, nHeight);
    }
    else if (Action == "saveCanvas")
    {
        QString Name;
        Name = Tokens.at(1);
        SaveCanvas(Name);
    }
    else if (Action == "setColor")
    {
        int nR, nG, nB;
        nR = Tokens.at(1).toInt();
        nG = Tokens.at(2).toInt();
        nB = Tokens.at(3).toInt();
        SetColor(nR, nG, nB);
    }
    else if (Action == "drawLine")
    {
        int nId, nX1, nY1, nX2, nY2;
        QString strAlgorithm;
        XE_ALGORITHM eAlgorithm;
        nId = Tokens.at(1).toInt();
        nX1 = Tokens.at(2).toInt();
        nY1 = Tokens.at(3).toInt();
        nX2 = Tokens.at(4).toInt();
        nY2 = Tokens.at(5).toInt();
        strAlgorithm = Tokens.at(6);
        if (strAlgorithm == "DDA")
        {
            eAlgorithm = emDDA;
        }
        else if (strAlgorithm == "Bresenham")
        {
            eAlgorithm = emBresenham;
        }
        else
        {
            qDebug() << "Unverified Algorithm " << strAlgorithm << endl;
            return false;
        }
        DrawLine(nId, nX1, nY1, nX2, nY2, eAlgorithm);
    }
    else
    {
        qDebug() << "Unverified command " << Command << endl;
        return false;
    }
    return true;
}


//重置画布，修改宽高，清除图元集合，清除像素点集合，用空白QImage覆盖label
bool MainWindow::ResetCanvas(int nWidth, int nHeight)
{
    m_nCanvasWidth = nWidth;
    m_nCanvasHeight = nHeight;
    m_Primitives.clear();
    m_Pixels.clear();
    Draw();
    return true;
}


//保存画布
bool MainWindow::SaveCanvas(QString Name)
{
    //完整文件路径
    QString CompletePath = m_SaveDirectoryName + Name + ".bmp";
    qDebug(CompletePath.toStdString().data());
    //生成白底QImage
    QImage image(m_nCanvasWidth, m_nCanvasHeight, QImage::Format_RGB888);
    image.fill(QColor(Qt::white).rgb());
    //画像素点集合中的所有点
    for (auto it = m_Pixels.begin(); it != m_Pixels.end(); ++it)
    {
        image.setPixel(it->m_nX, it->m_nY, (0xff << 24) | (it->m_nR << 16) | (it->m_nG << 8) | it->m_nB);
    }
    QPixmap pixmap = QPixmap::fromImage(image);
    pixmap.save(QString(CompletePath), "bmp");
    return true;
}


//设置当前画笔的颜色
bool MainWindow::SetColor(int nR, int nG, int nB)
{
    m_nR = nR;
    m_nG = nG;
    m_nB = nB;
    return true;
}


//画线，将图元添加到图元集合，调用XLine的画图函数添加到像素点集合
bool MainWindow::DrawLine(int nId, int nX1, int nY1, int nX2, int nY2, XE_ALGORITHM eAlgorithm)
{
    XLine* pLine = new XLine(nId, nX1, nY1, nX2, nY2, m_nR, m_nG, m_nB, eAlgorithm);
    m_Primitives[nId] = pLine;
    m_Pixels.splice(m_Pixels.end(), pLine->DrawSelf());
    Draw();
}


bool MainWindow::Draw()
{
    //生成白底QImage
    QImage image(m_nCanvasWidth, m_nCanvasHeight, QImage::Format_RGB888);
    image.fill(QColor(Qt::white).rgb());
    //画像素点集合中的所有点
    for (auto it = m_Pixels.begin(); it != m_Pixels.end(); ++it)
    {
        image.setPixel(it->m_nX, it->m_nY, (0xff << 24) | (it->m_nR << 16) | (it->m_nG << 8) | it->m_nB);
    }
    //贴到label上
    m_pCanvas->setGeometry(0, 0, m_nCanvasWidth, m_nCanvasHeight);
    m_pCanvas->setPixmap(QPixmap::fromImage(image));

    return true;
}
