#include "Line.h"
#include "mainwindow.h"

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
    if (nX1 == nX2)
    {
        if (nY1 > nY2)
        {
            swap(nY1, nY2);
        }
        for (int nYi = nY1; nYi <= nY2; nYi++)
        {
            Pixels.push_back(XPixel(nX1, nYi, m_nR, m_nG, m_nB));
        }
        return Pixels;
    }
    if (nY1 == nY2)
    {
        if (nX1 > nX2)
        {
            swap(nX1, nX2);
        }
        for (int nXi = nX1; nXi <= nX2; nXi++)
        {
            Pixels.push_back(XPixel(nXi, nY1, m_nR, m_nG, m_nB));
        }
        return Pixels;
    }
    //统一处理为从左往右画线
    if (nX1 > nX2)
    {
        swap(nX1, nX2);
        swap(nY1, nY2);
    }
    int nDx = nX2 - nX1;
    int nDy = nY2 - nY1;
    float fM = (float)nDy / (float)nDx;

    bool bAbsM = abs(fM) <= 1;
    int nBound = abs(bAbsM == true ? nDx : nDy);
    float fIncX = (bAbsM == true ? 1 : 1/fM);
    float fIncY = (bAbsM == true ? fM : 1);

    if (-1 <= fM && fM <= 1)
    {
        fIncX = 1;
        fIncY = fM;
    }
    else if (fM > 1)
    {
        fIncX = 1 / fM;
        fIncY = 1;
    }
    else
    {
        fIncX = -1 / fM;
        fIncY = -1;
    }

    float fXi = nX1;
    float fYi = nY1;
    Pixels.push_back(XPixel(nX1, nY1, m_nR, m_nG, m_nB));
    for (int i = 0; i < nBound; i++)
    {
        fXi = fXi + fIncX;
        fYi = fYi + fIncY;
        Pixels.push_back(XPixel((int)fXi, (int)fYi, m_nR, m_nG, m_nB));
    }

    return Pixels;
}


list<XPixel> XLine::Bresenham()
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
    int nIncX = nX2 > nX1 ? 1 : -1;
    int nIncY = nY2 > nY1 ? 1 : -1;
    //判断斜率
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
    int nPk = 2 * nDy - nDx;
    for (int i = 1; i <= nDx; ++i)
    {
        Pixels.push_back(XPixel(nXk, nYk, m_nR, m_nG, m_nB));
        if (nPk >= 0)
        {
            if (!nLFlag)
            {
                nYk += nIncY;
            }
            else
            {
                nXk += nIncX;
            }
            nPk -= 2 * nDx;
        }
        if (!nLFlag)
        {
            nXk += nIncX;
        }
        else
        {
            nYk += nIncY;
        }
        nPk += 2 * nDy;
    }
    return Pixels;
}
