#ifndef XPainter_H
#define XPainter_H

#include <QMainWindow>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QPainter>
#include <QVector>
#include <QPoint>
#include <QToolBar>
#include <QAction>
#include <QPalette>
#include <QColor>
#include <QMenu>
#include <QFileDialog>
#include <QTextEdit>
#include <QLabel>
#include <QString>
#include <qdebug.h>
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
using namespace std;
#include "Primitive.h"
#include "mainwindow.h"


enum XE_ALGORITHM;

class XPainter : public QMainWindow
{
    Q_OBJECT
public:
    explicit XPainter(QWidget *parent = 0);
protected:
    void paintEvent(QPaintEvent *);//重写窗体重绘事件
    void mousePressEvent(QMouseEvent *);//重写鼠标按下事件
    void mouseReleaseEvent(QMouseEvent *);//重写鼠标释放事件
    void mouseMoveEvent(QMouseEvent *);//重写鼠标移动事件
    void contextMenuEvent(QContextMenuEvent *);//重写菜单事件
    void keyPressEvent(QKeyEvent *e); //重写按键事件
private:
    int _lpress;//左键按下标志
    int _drag;//拖拽标志
    int _drawType;//描绘类型
    QMenu *_Rmenu;//右键菜单
    int _openflag;//打开图片
    QPixmap _pixmap;//画布图片
    QTextEdit *_tEdit;//文本输入框
public:
    QVector<QVector<QPoint> > _lines;//线条集合(一条线条可包含多个线段)
    QVector<QRect> _rects;//矩形集合
    QVector<QRect> _ellipse;//椭圆集合
    QVector<QRect>  _line;//直线集合
    QVector<QString>  _text;//文字集合
    QVector<QPoint>  _tpoint;//文字位置集合
    QVector<int>  _shape;//图形类型集合，用于撤回功能
    QPoint _begin;//鼠标按下坐标、用于最后一个图形移动
signals:

public slots:
    void Lines();//铅笔画线
    void SavePic();//保存图片
    void Rects();//画矩形
    void Ellipses();//画椭圆
    void Line();//画直线
    void OpenPic();//打开图片
    void Texts();//文字
    void AddTexts();//添加文字
public:
    QString m_SaveDirectoryName;        //图片输出目录
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


#endif // XPainter_H
