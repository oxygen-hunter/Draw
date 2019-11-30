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


    return m_Pixels;
}

list<XPixel> XEllipse::Bresenham()
{
    m_Pixels.clear();

    return m_Pixels;
}
