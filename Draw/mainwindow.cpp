#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Line.h"
#include "Polygon.h"
#include "Ellipse.h"
#include "Curve.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_pShowCanvas = ui->CanvasLabel;
    m_nCanvasWidth = 600;
    m_nCanvasHeight = 400;
    m_nR = 0;
    m_nG = 0;
    m_nB = 0;

    //图形化的初始化
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
        qDebug() << "File" << InputFileName << " not exist." << endl;
        return false;
    }
    if (!InputFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "File" << InputFileName << " can't open." << endl;
        return false;
    }
    while (!InputFile.atEnd())
    {
        QByteArray Line1 = InputFile.readLine();
        QString Command1(Line1);
        Command1.remove(QChar('\n'), Qt::CaseInsensitive);
        //qDebug() << Command1 << endl;
        //处理画多边形和曲线的两行参数，多读一行，并入同一行，空格隔开
        if (Command1.startsWith("drawPolygon") || Command1.startsWith("drawCurve"))
        {
            QByteArray Line2 = InputFile.readLine();
            QString Command2(Line2);
            Command2.remove(QChar('\n'), Qt::CaseInsensitive);
            Command1 += " " + Command2;
        }
        qDebug() << Command1 << endl;
        Execute(Command1);
    }
    InputFile.close();

    return true;
}


//解析每句指令
bool MainWindow::Execute(QString Command)
{
    QStringList Tokens = Command.split(" ");
    /*for (int i = 0; i < Tokens.size(); i++)
    {
        qDebug() << Tokens.at(i);
    }*/
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
            qDebug() << "Unverified algorithm " << strAlgorithm << endl;
            return false;
        }
        DrawLine(nId, nX1, nY1, nX2, nY2, eAlgorithm);
    }
    else if (Action == "drawPolygon")
    {
        int nId, nN;
        vector<int> X,Y;
        QString strAlgorithm;
        XE_ALGORITHM eAlgorithm;
        nId = Tokens.at(1).toInt();
        nN = Tokens.at(2).toInt();
        strAlgorithm = Tokens.at(3);
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
            qDebug() << "Unverified algorithm " << strAlgorithm << endl;
            return false;
        }
        //4,5, 6,7 ..4+2n,5+2n
        X.reserve(nN);
        Y.reserve(nN);
        for (int i = 0; i < nN; i++)
        {
            X.push_back(Tokens.at(4+2*i).toInt());
            Y.push_back(Tokens.at(5+2*i).toInt());
        }
        DrawPolygon(nId, nN, X, Y, eAlgorithm);
    }
    else if (Action == "drawEllipse")
    {
        int nId, nX, nY, nRx, nRy;
        nId = Tokens.at(1).toInt();
        nX = Tokens.at(2).toInt();
        nY = Tokens.at(3).toInt();
        nRx = Tokens.at(4).toInt();
        nRy = Tokens.at(5).toInt();
        DrawEllipse(nId, nX, nY, nRx, nRy);
    }
    else if (Action == "drawCurve")
    {
        int nId, nN;
        vector<int> X,Y;
        QString strAlgorithm;
        XE_ALGORITHM eAlgorithm;
        nId = Tokens.at(1).toInt();
        nN = Tokens.at(2).toInt();
        strAlgorithm = Tokens.at(3);
        if (strAlgorithm == "Bezier")
        {
            eAlgorithm = emBezier;
        }
        else if (strAlgorithm == "B-spline")
        {
            eAlgorithm = emBspline;
        }
        else
        {
            qDebug() << "Unverified algorithm " << strAlgorithm << endl;
            return false;
        }
        //4,5, 6,7 ..4+2n,5+2n
        X.reserve(nN);
        Y.reserve(nN);
        for (int i = 0; i < nN; i++)
        {
            X.push_back(Tokens.at(4+2*i).toInt());
            Y.push_back(Tokens.at(5+2*i).toInt());
        }
        DrawCurve(nId, nN, X, Y, eAlgorithm);
    }
    else if (Action == "translate")
    {
        int nId, nDx, nDy;
        nId = Tokens.at(1).toInt();
        nDx = Tokens.at(2).toInt();
        nDy = Tokens.at(3).toInt();
        Translate(nId, nDx, nDy);
    }
    else if (Action == "rotate")
    {
        int nId, nX, nY, nR;
        nId = Tokens.at(1).toInt();
        nX = Tokens.at(2).toInt();
        nY = Tokens.at(3).toInt();
        nR = Tokens.at(4).toInt();
        qDebug() << "rotate" << nX << "" << nY << "" << nR << endl;
        Rotate(nId, nX, nY, nR);
    }
    else if (Action == "scale")
    {
        int nId, nX, nY;
        float fS;
        nId = Tokens.at(1).toInt();
        nX = Tokens.at(2).toInt();
        nY = Tokens.at(3).toInt();
        fS = Tokens.at(4).toFloat();
        Scale(nId, nX, nY, fS);
    }
    else if (Action == "clip")
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
        if (strAlgorithm == "Cohen-Sutherland")
        {
            eAlgorithm = emCohenSutherland;
        }
        else if (strAlgorithm == "Liang-Barsky")
        {
            eAlgorithm = emLiangBarsky;
        }
        else
        {
            qDebug() << "Unverified algorithm " << strAlgorithm << endl;
            return false;
        }
        Clip(nId, nX1, nY1, nX2, nY2, eAlgorithm);
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
    //m_Pixels.clear();
    m_LogicCanvas.resize(m_nCanvasWidth);
    for (int i = 0; i < m_nCanvasWidth; i++)
    {
        m_LogicCanvas[i].resize(m_nCanvasHeight);
    }
    Draw();
    return true;
}


//保存画布
bool MainWindow::SaveCanvas(QString Name)
{
    //完整文件路径
    QString CompletePath = m_SaveDirectoryName + Name + ".bmp";
    qDebug(CompletePath.toStdString().data());
    //生成QImage
    QImage image(m_nCanvasWidth, m_nCanvasHeight, QImage::Format_RGB888);
    //清空逻辑画布
    for (int i = 0; i < m_nCanvasWidth; i++)
    {
        for (int j = 0; j < m_nCanvasHeight; j++)
        {
            m_LogicCanvas[i][j] = QColor(Qt::white).rgb();//白色
        }
    }
    //画图元集合到逻辑画布
    for (auto it = m_Primitives.begin(); it != m_Primitives.end(); ++it)
    {
        for (auto pPixel = it->second->m_Pixels.begin(); pPixel != it->second->m_Pixels.end(); ++pPixel)
        {
            if (pPixel->m_nX > 0 && pPixel->m_nX < m_nCanvasWidth && pPixel->m_nY > 0 && pPixel->m_nY < m_nCanvasHeight)
            {
                m_LogicCanvas[pPixel->m_nX][pPixel->m_nY] = (0xff << 24) | (pPixel->m_nR << 16) | (pPixel->m_nG << 8) | (pPixel->m_nB);
            }
        }
    }
    //保存逻辑画布到QImage
    for (int nX = 0; nX < m_nCanvasWidth; nX++)
    {
        for (int nY = 0; nY < m_nCanvasHeight; nY++)
        {
            image.setPixel(nX, nY, m_LogicCanvas[nX][nY]);
        }
    }
    //保存QImage为QPixmap，保存到完整路径
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
    pLine->DrawSelf();
    m_Primitives[nId] = pLine;
    //m_Pixels.splice(m_Pixels.end(), pLine->DrawSelf());
    Draw();

    return true;
}


//画多边形
bool MainWindow::DrawPolygon(int nId, int nN, vector<int>& X, vector<int>& Y, XE_ALGORITHM eAlgorithm)
{
    XPolygon* pPolygon = new XPolygon(nId, nN, X, Y, m_nR, m_nG, m_nB, eAlgorithm);
    pPolygon->DrawSelf();
    m_Primitives[nId] = pPolygon;
    //m_Pixels.splice(m_Pixels.end(), pPolygon->DrawSelf());
    Draw();

    return true;
}


//画椭圆
bool MainWindow::DrawEllipse(int nId, int nX, int nY, int nRx, int nRy)
{
    XEllipse* pEllipse = new XEllipse(nId, nX, nY, nRx, nRy, m_nR, m_nG, m_nB);
    pEllipse->DrawSelf();
    m_Primitives[nId] = pEllipse;
    Draw();

    return true;
}


//画曲线
bool MainWindow::DrawCurve(int nId, int nN, vector<int>& X, vector<int>& Y, XE_ALGORITHM eAlgorithm)
{
    XCurve* pCurve = new XCurve(nId, nN, X, Y, m_nR, m_nG, m_nB, eAlgorithm);
    pCurve->DrawSelf();
    m_Primitives[nId] = pCurve;
    Draw();

    return true;
}


//平移图元
bool MainWindow::Translate(int nId, int nDx, int nDy)
{
    XPrimitive* pPrimitive = m_Primitives[nId];
    if (pPrimitive == nullptr)
    {
        qDebug() << "Primitive" << nId << "Not found" << endl;
        return false;
    }
    pPrimitive->Translate(nDx, nDy);
    pPrimitive->DrawSelf();

    return true;
}


//旋转图元
bool MainWindow::Rotate(int nId, int nX, int nY, int nR)
{
    XPrimitive* pPrimitive = m_Primitives[nId];
    if (pPrimitive == nullptr)
    {
        qDebug() << "Primitive" << nId << "Not found" << endl;
        return false;
    }
    pPrimitive->Rotate(nX, nY, nR);
    pPrimitive->DrawSelf();

    return true;
}


//缩放图元
bool MainWindow::Scale(int nId, int nX, int nY, float fS)
{
    XPrimitive* pPrimitive = m_Primitives[nId];
    if (pPrimitive == nullptr)
    {
        qDebug() << "Primitive" << nId << "Not found" << endl;
        return false;
    }
    pPrimitive->Scale(nX, nY, fS);
    pPrimitive->DrawSelf();

    return true;
}


//裁剪图元
bool MainWindow::Clip(int nId, int nX1, int nY1, int nX2, int nY2, XE_ALGORITHM eAlgorithm)
{
    XPrimitive* pPrimitive = m_Primitives[nId];
    if (pPrimitive == nullptr)
    {
        qDebug() << "Primitive" << nId << "Not found" << endl;
        return false;
    }
    pPrimitive->Clip(nX1, nY1, nX2, nY2, eAlgorithm);
    pPrimitive->DrawSelf();

    return true;
}


//画所有图元并更新
bool MainWindow::Draw()
{
    //生成QImage
    QImage image(m_nCanvasWidth, m_nCanvasHeight, QImage::Format_RGB888);
    //清除逻辑画布
    for (int i = 0; i < m_nCanvasWidth; i++)
    {
        for (int j = 0; j < m_nCanvasHeight; j++)
        {
            m_LogicCanvas[i][j] = QColor(Qt::white).rgb();
        }
    }
    //画图元集合到逻辑画布
    for (auto it = m_Primitives.begin(); it != m_Primitives.end(); ++it)
    {
        for (auto pPixel = it->second->m_Pixels.begin(); pPixel != it->second->m_Pixels.end(); ++pPixel)
        {
            if (pPixel->m_nX > 0 && pPixel->m_nX < m_nCanvasWidth && pPixel->m_nY > 0 && pPixel->m_nY < m_nCanvasHeight)
            {
               m_LogicCanvas[pPixel->m_nX][pPixel->m_nY] = (0xff << 24) | (pPixel->m_nR << 16) | (pPixel->m_nG << 8) | (pPixel->m_nB);
            }
        }
    }
    //保存逻辑画布到QImage
    for (int nX = 0; nX < m_nCanvasWidth; nX++)
    {
        for (int nY = 0; nY < m_nCanvasHeight; nY++)
        {
            image.setPixel(nX, nY, m_LogicCanvas[nX][nY]);
        }
    }

    //将QImage贴到展现画布上
    m_pShowCanvas->setGeometry(0, 0, m_nCanvasWidth, m_nCanvasHeight);
    m_pShowCanvas->setPixmap(QPixmap::fromImage(image));

    return true;
}
