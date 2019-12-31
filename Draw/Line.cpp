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


bool XLine::Translate(int nDx, int nDy)
{
    m_nX1 += nDx;
    m_nX2 += nDx;
    m_nY1 += nDy;
    m_nY2 += nDy;
    return true;
}


bool XLine::Rotate(int nX, int nY, int nR)
{
    RotatePoint(m_nX1, m_nY1, nX, nY, nR);
    RotatePoint(m_nX2, m_nY2, nX, nY, nR);
    return true;
}


bool XLine::Scale(int nX, int nY, float fS)
{
    ScalePoint(m_nX1, m_nY1, nX, nY, fS);
    ScalePoint(m_nX2, m_nY2, nX, nY, fS);
    return true;
}


bool XLine::Clip(int nX1, int nY1, int nX2, int nY2, XE_ALGORITHM eAlgorithm)
{
    switch (eAlgorithm) {
    case emCohenSutherland:
        return CohenSutherland(nX1, nY1, nX2, nY2);
    case emLiangBarsky:
        return LiangBarsky(nX1, nY1, nX2, nY2);
    default:
        return false;
    }
}


bool XLine::CohenSutherland(int nX1, int nY1, int nX2, int nY2)
{
    //return Stupid(nX1, nY1, nX2, nY2);
if(m_nId == 114 && nX1 == 30)
{
    m_nId = 114;
}
    int loopi = 0;
loop:
    int c1[4], c2[4], cc1, cc2, x1, y1, x2, y2, x1c, y1c, x2c, y2c;
    x1 = m_nX1;
    y1 = m_nY1;
    x2 = m_nX2;
    y2 = m_nY2;
    x1c = nX1;
    y1c = nY1;
    x2c = nX2;
    y2c = nY2;

    if (x1 == x2 && y1 == y2)
    {
        m_nX1 = m_nX2 = -1;
        m_nY1 = m_nY2 = -1;
        return true;
    }

    //上下右左
    c1[0] = y1 > y2c ? 1 : 0;
    c1[1] = y1 < y1c ? 1 : 0;
    c1[2] = x1 > x2c ? 1 : 0;
    c1[3] = x1 < x1c ? 1 : 0;
    cc1 = (c1[0] << 24) | (c1[1] << 16) | (c1[2] << 8) | c1[3];

    c2[0] = y2 > y2c ? 1 : 0;
    c2[1] = y2 < y1c ? 1 : 0;
    c2[2] = x2 > x2c ? 1 : 0;
    c2[3] = x2 < x1c ? 1 : 0;
    cc2 = (c2[0] << 24) | (c2[1] << 16) | (c2[2] << 8) | c2[3];

    if (cc1 == 0 && cc2 == 0)
    {   //完全在窗口内，保留
        return true;
    }
    if ((cc1 & cc2) != 0)
    {   //完全在窗口外，舍弃
        m_nX1 = m_nX2 = -1;
        m_nY1 = m_nY2 = -1;
        return true;
    }
    //存在一部分在窗口内
    //特别处理水平竖直线
    if (x1 == x2)
    {
        if (y1 > y2)
            swap(y1, y2);
        if (x1 < x1c || x1 > x2c)
        {
            //完全在窗口外，舍弃
            m_nX1 = m_nX2 = -1;
            m_nY1 = m_nY2 = -1;
        }
        else
        {
            m_nY1 = max(y1, y1c);
            m_nY2 = min(y2, y2c);
        }
        return true;
    }
    if (y1 == y2)
    {
        if (x1 > x2)
            swap(x1, x2);
        if (y1 < y1c || y1 > y2c)
        {
            //完全在窗口外，舍弃
            m_nX1 = m_nX2 = -1;
            m_nY1 = m_nY2 = -1;
        }
        else
        {
            m_nX1 = max(x1, x1c);
            m_nX2 = min(x2, x2c);
        }
        return true;
    }

    //原直线斜率
    float k = ((float)(y2-y1)) / ((float)(x2-x1));
    //左右上下
    if (x1 > x2)
    {
        swap(x1, x2);
        swap(y1, y2);
    }
    if (loopi == 0)
    {
        loopi++;
        if (x1 < x1c)
        {
            m_nX1 = x1c;
            m_nY1 = k * (x1c - x1) + y1;
            goto loop;
        }
    }
    if (loopi == 1)
    {
        loopi++;
        if (x2 > x2c)
        {
            m_nX2 = x2c;
            m_nY2 = k * (x2c - x1) + y1;
            goto loop;
        }
    }
    if (y1 > y2)
    {
        swap(x1, x2);
        swap(y1, y2);
    }
    if (loopi == 2)
    {
        loopi++;
        if (y1 < y1c)
        {
            m_nX1 = 1 / k * (y1c - y1) + x1;
            m_nY1 = y1c;
            goto loop;
        }
    }
    if (loopi == 3)
    {
        loopi++;
        if (y2 > y2c)
        {
            m_nX2 = 1 / k * (y2c - y1) + x1;
            m_nY2 = y2c;
            goto loop;
        }
    }

    return true;
}


bool XLine::LiangBarsky(int nX1, int nY1, int nX2, int nY2)
{

    return true;
}


bool XLine::Stupid(int nX1, int nY1, int nX2, int nY2)
{
    //qDebug() << m_nX1 << m_nY1 << m_nX2 << m_nY2 << endl;
    //不在区域内的点删掉
    auto it = m_Pixels.begin();
    while (it != m_Pixels.end())
    {
        int x = it->m_nX, y = it->m_nY;
        if (x < nX1 || x > nX2 ||
            y < nY1 || y > nY2)
        {
            it = m_Pixels.erase(it);
        }
        else
        {
            ++it;
        }
    }

    //对于留下来的点，确定线段的新端点，即最小的x和最大的x
    int x1 = m_nX1, y1 = m_nY1, x2 = m_nX2, y2 = m_nY2;
    if (m_Pixels.size() > 0)
    {
        x1 = x2 = m_Pixels.begin()->m_nX;
        y1 = y2 = m_Pixels.begin()->m_nY;
    }
    for (auto it = m_Pixels.begin(); it != m_Pixels.end(); ++it)
    {
        int x = it->m_nX, y = it->m_nY;
        if (x < x1)
        {
            x1 = x;
            y1 = y;
        }
        if (x > x2)
        {
            x2 = x;
            y2 = y;
        }
    }

    //更新线段端点
    m_nX1 = x1;
    m_nY1 = y1;
    m_nX2 = x2;
    m_nY2 = y2;
    //qDebug() << m_nX1 << m_nY1 << m_nX2 << m_nY2 << endl;

    return true;
}
