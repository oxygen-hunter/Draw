#include "Polygon.h"
#include "Line.h"

//#include "mainwindow.h"

XPolygon::XPolygon(int nId, int nN, vector<int>& X, vector<int>& Y, int nR, int nG, int nB, XE_ALGORITHM eAlgorithm)
{
    m_nId = nId;
    m_nR = nR;
    m_nG = nG;
    m_nB = nB;
    m_eAlgorithm = eAlgorithm;

    m_nN = nN;
    m_X = X;
    m_Y = Y;
    //m_X.assign(X.begin(), X.end());
    //m_Y.assign(Y.begin(), Y.end());
}


list<XPixel> XPolygon::DrawSelf()
{
    switch (m_eAlgorithm) {
    case emDDA:
        return DDA();
    case emBresenham:
        return Bresenham();
    default:
        m_Pixels.clear();
        return m_Pixels;
    }
}


list<XPixel> XPolygon::DDA()
{
    m_Pixels.clear();
    for (int i = 0; i < m_nN; i++)
    {
        XLine line(m_nId, m_X[i], m_Y[i], m_X[(i+1)%m_nN], m_Y[(i+1)%m_nN], m_nR, m_nG, m_nB, m_eAlgorithm);
        m_Pixels.splice(m_Pixels.end(), line.DrawSelf());
    }
    return m_Pixels;
}


list<XPixel> XPolygon::Bresenham()
{
    m_Pixels.clear();
    for (int i = 0; i < m_nN; i++)
    {
        XLine line(m_nId, m_X[i], m_Y[i], m_X[(i+1)%m_nN], m_Y[(i+1)%m_nN], m_nR, m_nG, m_nB, m_eAlgorithm);
        m_Pixels.splice(m_Pixels.end(), line.DrawSelf());
    }
    return m_Pixels;
}


bool XPolygon::Translate(int nDx, int nDy)
{
    for (int i = 0; i < m_nN; i++)
    {
        m_X[i] += nDx;
        m_Y[i] += nDy;
    }
    return true;
}


bool XPolygon::Rotate(int nX, int nY, int nR)
{   
    for (int i = 0; i < m_nN; i++)
    {
        RotatePoint(m_X[i], m_Y[i], nX, nY, nR);
    }
    return true;
}


bool XPolygon::Scale(int nX, int nY, float fS)
{
    for (int i = 0; i < m_nN; i++)
    {
        ScalePoint(m_X[i], m_Y[i], nX, nY, fS);
    }
    return true;
}
