#ifndef ELLIPSE_H
#define ELLIPSE_H
#include "Primitive.h"

class XEllipse: public XPrimitive
{
public:
    XEllipse(int nId, int nX, int nY, int nRx, int nRy, int nR, int nG, int nB, XE_ALGORITHM eAlgorithm = emMidPoint);
    list<XPixel> DrawSelf();
    list<XPixel> MidPoint();
    list<XPixel> Bresenham();
    bool Translate(int nDx, int nDy);
    bool Rotate(int nX, int nY, int nR);
    bool Scale(int nX, int nY, float fS);
public:
    int m_nX;
    int m_nY;
    int m_nRx;
    int m_nRy;
};

#endif // ELLIPSE_H
