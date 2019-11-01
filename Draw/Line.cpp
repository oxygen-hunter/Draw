#include "Line.h"
#include "mainwindow.h"

XLine::XLine(int nId, int nX1, int nY1, int nX2, int nY2, int nR, int nG, int nB, XE_ALGORITHM eAlgorithm)
    :/*m_nId(nId), */m_nX1(nX1), m_nY1(nY1), m_nX2(nX2), m_nY2(nY2)/*, m_nR(nR), m_nG(nG), m_nB(nB)*/
{
    m_nId = nId;
    m_nR = nR;
    m_nG = nG;
    m_nB = nB;
    m_eAlgorithm = eAlgorithm;
}


list<XPixel> XLine::DrawSelf()
{
    if (m_eAlgorithm == emDDA)
    {
        return DDA();
    }
    else if (m_eAlgorithm == emBresenham)
    {
        return Bresenham();
    }
    else
    {
        return list<XPixel>();
    }
}


list<XPixel> XLine::DDA()
{
    list<XPixel> Pixels;

    int nX1 = m_nX1;
    int nX2 = m_nX2;
    int nY1 = m_nY1;
    int nY2 = m_nY2;
    //两端点
    Pixels.push_back(XPixel(nX1, nY1, m_nR, m_nG, m_nB));
    Pixels.push_back(XPixel(nX2, nY2, m_nR, m_nG, m_nB));
    int nDx = abs(nX2-nX1);
    int nDy = abs(nY2-nY1);
    //XY增长量
    int nXIncrease = nX2 > nX1 ? 1 : -1;
    int nYIncrease = nY2 > nY1 ? 1 : -1;
    //斜率控制，统一处理为绝对值小于1
    int nLFlag = nDx >= nDy ? 0 : 1;
    if(nLFlag)
    {
        int nTemp = nDx;
        nDx = nDy;
        nDy = nTemp;
    }
    //X_k和Y_k作为循环变量
    int nXk = nX1;
    int nYk = nY1;
    int nHeight = 2 * nDy - nDx;
    for (int i = 1; i <= nDx; ++i)
    {
        Pixels.push_back(XPixel(nXk, nYk, m_nR, m_nG, m_nB));
        if (nHeight >= 0)
        {
            if (!nLFlag)
            {
                nYk += nYIncrease;
            }
            else
            {
                nXk += nXIncrease;
            }
            nHeight -= 2 * nDx;
        }
        if (!nLFlag)
        {
            nXk += nXIncrease;
        }
        else
        {
            nYk += nYIncrease;
        }
        nHeight += 2 * nDy;
    }
    return Pixels;
}


list<XPixel> XLine::Bresenham()
{
    list<XPixel> Pixels;

    return Pixels;
}
