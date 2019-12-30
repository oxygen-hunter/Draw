#ifndef PRIMITIVE_H
#define PRIMITIVE_H
#include <QPaintEvent>
#include "qpainter.h"
#include <qdebug.h>
#include <list>
#include <vector>
#include <math.h>
using namespace std;


struct XPixel;

enum XE_ALGORITHM
{
    emDDA, emBresenham,
    emMidPoint,
    emBezier, emBspline
    //TODO: 其他算法

};

struct XPixel
{
    int m_nX;
    int m_nY;
    int m_nR;
    int m_nG;
    int m_nB;
    XPixel(int nX, int nY, int nR, int nG, int nB)
        : m_nX(nX), m_nY(nY), m_nR(nR), m_nG(nG), m_nB(nB) {}
};

class XPrimitive
{
public:
    XPrimitive();
    ~XPrimitive();
    virtual list<XPixel> DrawSelf() = 0;
    virtual bool Translate(int nDx, int nDy) = 0;
    virtual bool Rotate(int nX, int nY, int nR) = 0;
    virtual bool Scale(int nX, int nY, float fS) = 0;
    void SetPixel(int nX, int nY);
    void RotatePoint(int& nX, int& nY, int nXm, int nYm, int nR);
    void ScalePoint(int& nX, int& nY, int nX0, int nY0, float fS);
public:
    int m_nId;
    int m_nR;
    int m_nG;
    int m_nB;
    XE_ALGORITHM m_eAlgorithm;

    list<XPixel> m_Pixels;
};

#endif // PRIMITIVE_H
