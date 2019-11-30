#include "Line.h"
//#include "mainwindow.h"

XLine::XLine(int nId, int nX1, int nY1, int nX2, int nY2, int nR, int nG, int nB, XE_ALGORITHM eAlgorithm)
{
    m_nId = nId;
    m_nR = nR;
    m_nG = nG;
    m_nB = nB;
    m_eAlgorithm = eAlgorithm;

    m_nX1 = nX1;
    m_nY1 = nY1;
    m_nX2 = nX2;
    m_nY2 = nY2;
}


list<XPixel> XLine::DrawSelf()
{
    switch (m_eAlgorithm) {
    case emDDA:
        return DDA();
    case emBresenham:
        return Bresenham();
    default:
        return m_Pixels;
    }
}


list<XPixel> XLine::DDA()
{
    m_Pixels.clear();
    int x1 = m_nX1;
    int x2 = m_nX2;
    int y1 = m_nY1;
    int y2 = m_nY2;
    //竖直水平直接处理
    if (x1 == x2)
    {
        if (y1 > y2)
        {
            swap(y1, y2);
        }
        for (int nYi = y1; nYi <= y2; nYi++)
        {
            //m_Pixels.push_back(XPixel(x1, nYi, m_nR, m_nG, m_nB));
            SetPixel(x1, nYi);
        }
        return m_Pixels;
    }
    if (y1 == y2)
    {
        if (x1 > x2)
        {
            swap(x1, x2);
        }
        for (int nXi = x1; nXi <= x2; nXi++)
        {
            //m_Pixels.push_back(XPixel(nXi, y1, m_nR, m_nG, m_nB));
            SetPixel(nXi, y1);
        }
        return m_Pixels;
    }
    //统一处理为从左往右画线
    if (x1 > x2)
    {
        swap(x1, x2);
        swap(y1, y2);
    }
    int dx = x2 - x1;
    int dy = y2 - y1;
    float m = (float)dy / (float)dx;

    bool bAbsM = abs(m) <= 1;
    int bound = abs(bAbsM == true ? dx : dy);
    float incX = (bAbsM == true ? 1 : 1/m);
    float incY = (bAbsM == true ? m : 1);

    if (-1 <= m && m <= 1)
    {
        incX = 1;
        incY = m;
    }
    else if (m > 1)
    {
        incX = 1 / m;
        incY = 1;
    }
    else
    {
        incX = -1 / m;
        incY = -1;
    }

    float xi = x1;
    float yi = y1;
    //m_Pixels.push_back(XPixel(x1, y1, m_nR, m_nG, m_nB));
    SetPixel(x1, y1);
    for (int i = 0; i < bound; i++)
    {
        xi = xi + incX;
        yi = yi + incY;
        //m_Pixels.push_back(XPixel((int)xi, (int)yi, m_nR, m_nG, m_nB));
        SetPixel((int)xi, (int)yi);
    }

    return m_Pixels;
}


list<XPixel> XLine::Bresenham()
{
    m_Pixels.clear();
    int x1 = m_nX1;
    int x2 = m_nX2;
    int y1 = m_nY1;
    int y2 = m_nY2;
    //两端点
    //m_Pixels.push_back(XPixel(x1, y1, m_nR, m_nG, m_nB));
    //m_Pixels.push_back(XPixel(x2, y2, m_nR, m_nG, m_nB));
    SetPixel(x1, y1);
    SetPixel(x2, y2);

    int dx = abs(x2-x1);
    int dy = abs(y2-y1);
    //XY增长量
    int incX = x2 > x1 ? 1 : -1;
    int incY = y2 > y1 ? 1 : -1;
    //判断斜率
    int loopflag = dx >= dy ? 0 : 1;
    if(loopflag)
    {
        int nTemp = dx;
        dx = dy;
        dy = nTemp;
    }
    //xk和yk作为循环变量
    int xk = x1;
    int yk = y1;
    int pk = 2 * dy - dx;
    for (int i = 1; i <= dx; ++i)
    {
        //m_Pixels.push_back(XPixel(xk, yk, m_nR, m_nG, m_nB));
        SetPixel(xk, yk);
        if (pk >= 0)
        {
            if (!loopflag)
            {
                yk += incY;
            }
            else
            {
                xk += incX;
            }
            pk -= 2 * dx;
        }
        if (!loopflag)
        {
            xk += incX;
        }
        else
        {
            yk += incY;
        }
        pk += 2 * dy;
    }
    return m_Pixels;
}
