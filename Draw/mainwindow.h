#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPaintEvent>
#include <QLabel>
#include <QString>
#include <qdebug.h>
#include <string>
#include <list>
#include <vector>
#include <map>
using namespace std;
#include "Primitive.h"

namespace Ui {
class MainWindow;
}



enum XE_ALGORITHM;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;

public:
    bool Input(QString InputFileName, QString SaveDirectoryName = "");
    bool Execute(QString Command);
    bool ResetCanvas(int nWidth, int nHeight);
    bool SaveCanvas(QString Name);
    bool SetColor(int nR, int nG, int nB);
    bool DrawLine(int nId, int nX1, int nY1, int nX2, int nY2, XE_ALGORITHM eAlgorithm);
    bool DrawPolygon(int nId, int nN, vector<int>& X, vector<int>& Y, XE_ALGORITHM eAlgorithm);
    bool DrawEllipse(int nId, int nX, int nY, int nRx, int nRy);
    bool Draw();
public:
    QString m_SaveDirectoryName;        //图片输出目录
    QImage m_Image;                     //图片
    QLabel* m_pShowCanvas;              //承载图片的画布
    vector<vector<int>> m_LogicCanvas;  //逻辑画布
    int m_nCanvasWidth;                 //画布宽度
    int m_nCanvasHeight;                //画布高度
    int m_nR;                           //当前画笔颜色RGB
    int m_nG;
    int m_nB;

    map<int, XPrimitive*> m_Primitives; //图元集合
    //list<XPixel> m_Pixels;              //像素点集合
};

#endif // MAINWINDOW_H
