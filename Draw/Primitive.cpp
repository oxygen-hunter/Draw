#include "Primitive.h"

XPrimitive::XPrimitive()
{

}


XPrimitive::~XPrimitive()
{

}


void XPrimitive::SetPixel(int nX, int nY)
{
    m_Pixels.push_back(XPixel(nX, nY, m_nR, m_nG, m_nB));
}


void XPrimitive::RotatePoint(int& nX, int& nY, int nX0, int nY0, int nR)
{
    float x, y, x0, y0, r;
    x = nX;
    y = nY;
    x0 = nX0;
    y0 = nY0;
    r = 3.1415926 * nR / (float)180;

    nX = (x-x0)*cos(r) - (y-y0)*sin(r) + x0;
    nY = (x-x0)*sin(r) + (y-y0)*cos(r) + y0;
}


void XPrimitive::ScalePoint(int& nX, int& nY, int nX0, int nY0, float fS)
{
    float x, y, x0, y0;
    x = nX;
    y = nY;
    x0 = nX0;
    y0 = nY0;
    nX = (x - x0) * fS + x0;
    nY = (y - y0) * fS + y0;
}
