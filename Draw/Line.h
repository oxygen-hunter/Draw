#ifndef LINE_H
#define LINE_H
using namespace std;
#include "Primitive.h"

class XLine : public XPrimitive
{
public:
    XLine(int nId, int nX1, int nY1, int nX2, int nY2, int nR, int nG, int nB, XE_ALGORITHM eAlgorithm);
    list<XPixel> DrawSelf();
    list<XPixel> DDA();
    list<XPixel> Bresenham();
public:
    int m_nX1;
    int m_nY1;
    int m_nX2;
    int m_nY2;
};

#endif // LINE_H
