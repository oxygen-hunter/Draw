#ifndef PRIMITIVE_H
#define PRIMITIVE_H
#include <QPaintEvent>
#include "qpainter.h"
#include <list>
using namespace std;

struct XPixel;

enum XE_ALGORITHM
{
    emDDA, emBresenham,
    //TODO: 其他算法

};

class XPrimitive
{
public:
    XPrimitive();
    virtual list<XPixel> DrawSelf() = 0;
public:
    int m_nId;
    int m_nR;
    int m_nG;
    int m_nB;
    XE_ALGORITHM m_eAlgorithm;
};

#endif // PRIMITIVE_H
