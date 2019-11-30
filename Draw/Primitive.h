#ifndef PRIMITIVE_H
#define PRIMITIVE_H
#include <QPaintEvent>
#include "qpainter.h"
#include <list>
#include <vector>
using namespace std;


struct XPixel;

enum XE_ALGORITHM
{
    emDDA, emBresenham,
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
public:
    int m_nId;
    int m_nR;
    int m_nG;
    int m_nB;
    XE_ALGORITHM m_eAlgorithm;

    list<XPixel> m_Pixels;
};

#endif // PRIMITIVE_H
