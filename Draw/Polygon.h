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
public:
    int m_nN;
    vector<int> m_X;
    vector<int> m_Y;
};

#endif // POLYGON_H
