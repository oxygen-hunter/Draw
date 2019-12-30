#ifndef POLYGON_H
#define POLYGON_H
#include "Primitive.h"

class XPolygon : public XPrimitive
{
public:
    XPolygon(int nId, int nN, vector<int>& X, vector<int>& Y, int nR, int nG, int nB, XE_ALGORITHM eAlgorithm);
    list<XPixel> DrawSelf();
    list<XPixel> DDA();
    list<XPixel> Bresenham();
    bool Translate(int nDx, int nDy);
    bool Rotate(int nX, int nY, int nR);
    bool Scale(int nX, int nY, float fS);
public:
    int m_nN;
    vector<int> m_X;
    vector<int> m_Y;
};

#endif // POLYGON_H
