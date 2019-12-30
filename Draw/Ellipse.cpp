#include "Ellipse.h"

XEllipse::XEllipse(int nId, int nX, int nY, int nRx, int nRy, int nR, int nG, int nB, XE_ALGORITHM eAlgorithm)
{
    m_nId = nId;
    m_nR = nR;
    m_nG = nG;
    m_nB = nB;
    m_eAlgorithm = eAlgorithm;

    m_nX = nX;
    m_nY = nY;
    m_nRx = nRx;
    m_nRy = nRy;
}


list<XPixel> XEllipse::DrawSelf()
{
    switch (m_eAlgorithm) {
    case emMidPoint:
        return MidPoint();
    case emBresenham:
        return Bresenham();
    default:
        m_Pixels.clear();
        return m_Pixels;
    }
}


list<XPixel> XEllipse::MidPoint()
{
    m_Pixels.clear();
    //qDebug() << "midpoint1" << endl;

    int rx = m_nRx, ry = m_nRy;
    int xk = 0, yk = ry;
    int pk = ry*ry - rx*rx*ry + rx*rx/4;

    //四个端点
    SetPixel(rx + m_nX, 0 + m_nY);
    SetPixel(-rx + m_nX, 0 + m_nY);
    SetPixel(0 + m_nX, ry + m_nY);
    SetPixel(0 + m_nX, -ry + m_nY);

    //区域1
    while (2*ry*ry*xk < 2*rx*rx*yk)
    {
        if (pk < 0)
        {
            xk = xk+1;
            yk = yk;
            pk = pk+2*ry*ry*xk+ry*ry;
        }
        else
        {
            xk = xk+1;
            yk = yk-1;
            pk = pk+2*ry*ry*xk-2*rx*rx*yk+ry*ry;
        }
        //setpixel(xk, yk);
        //qDebug() << xk << ", " << yk <<endl;
        SetPixel(xk + m_nX, yk + m_nY);
        SetPixel(-xk + m_nX, yk + m_nY);
        SetPixel(xk + m_nX, -yk + m_nY);
        SetPixel(-xk + m_nX, -yk + m_nY);
    }
    //qDebug() << "midpoint2" << endl;
    //区域2
    while (xk < rx && yk > 0)
    {
        if (pk > 0)
        {
            xk = xk;
            yk = yk - 1;
            pk = pk - 2*rx*rx*yk+rx*rx;
        }
        else
        {
            xk = xk + 1;
            yk = yk - 1;
            pk = pk + 2*ry*ry*xk-2*rx*rx*yk+rx*rx;
        }
        //setpixel(xk, yk);
        //qDebug() << xk << ", " << yk <<endl;
        SetPixel(xk + m_nX, yk + m_nY);
        SetPixel(-xk + m_nX, yk + m_nY);
        SetPixel(xk + m_nX, -yk + m_nY);
        SetPixel(-xk + m_nX, -yk + m_nY);
    }

    //qDebug() << "midpoint3" <<endl;
    //qDebug() << "size: " << m_Pixels.size()<<endl;

    return m_Pixels;
}


list<XPixel> XEllipse::Bresenham()
{
    return MidPoint();
    //TODO:和中点圆有啥区别？暂时返回了中点圆画法
    m_Pixels.clear();

    return m_Pixels;
}


bool XEllipse::Translate(int nDx, int nDy)
{
    m_nX += nDx;
    m_nY += nDy;
    return true;
}


bool XEllipse::Rotate(int nX, int nY, int nR)
{
    return true;
}


bool XEllipse::Scale(int nX, int nY, float fS)
{
    ScalePoint(m_nX, m_nY, nX, nY, fS);
    m_nRx *= fabs(fS);
    m_nRy *= fabs(fS);
    return true;
}
