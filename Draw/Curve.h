#ifndef CURVE_H
#define CURVE_H
#include "Primitive.h"

class XCurve : public XPrimitive
{
public:
    XCurve(int nId, int nN, vector<int>& X, vector<int>& Y, int nR, int nG, int nB, XE_ALGORITHM eAlgorithm);
    list<XPixel> DrawSelf();
    list<XPixel> Bezier();
    list<XPixel> Bspline();
    bool Translate(int nDx, int nDy);
    bool Rotate(int nX, int nY, int nR);
    bool Scale(int nX, int nY, float fS);
public:
    int m_nN;
    vector<int> m_X;
    vector<int> m_Y;
};

#endif // CURVE_H
