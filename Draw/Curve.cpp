#include "Curve.h"

XCurve::XCurve(int nId, int nN, vector<int>& X, vector<int>& Y, int nR, int nG, int nB, XE_ALGORITHM eAlgorithm)
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


list<XPixel> XCurve::DrawSelf()
{
    switch (m_eAlgorithm) {
    case emBezier:
        return Bezier();
    case emBspline:
        return Bspline();
    default:
        m_Pixels.clear();
        return m_Pixels;
    }
}


list<XPixel> XCurve::Bezier()
{
    m_Pixels.clear();

    if (m_nN == 4)
    {
        for (int i = 0; i < 256; i++)
        {
            float t = i * 1.0/256.0;
            int x = pow(1-t, 3)*m_X[0] + 3*t*pow(1-t, 2)*m_X[1] + 3*t*t*(1-t)*m_X[2] + pow(t,3)*m_X[3];
            int y = pow(1-t, 3)*m_Y[0] + 3*t*pow(1-t, 2)*m_Y[1] + 3*t*t*(1-t)*m_Y[2] + pow(t,3)*m_Y[3];
            SetPixel(x, y);
        }
    }

    return m_Pixels;
}



list<XPixel> XCurve::Bspline()
{
    m_Pixels.clear();

    return m_Pixels;
}


bool XCurve::Translate(int nDx, int nDy)
{
    for(int i = 0; i < m_nN; i++)
    {
        m_X[i] += nDx;
        m_Y[i] += nDy;
    }
    return true;
}


bool XCurve::Rotate(int nX, int nY, int nR)
{
    for (int i = 0; i < m_nN; i++)
    {
        RotatePoint(m_X[i], m_Y[i], nX, nY, nR);
    }
    return true;
}


bool XCurve::Scale(int nX, int nY, float fS)
{
    for (int i = 0; i < m_nN; i++)
    {
        ScalePoint(m_X[i], m_Y[i], nX, nY, fS);
    }
}
