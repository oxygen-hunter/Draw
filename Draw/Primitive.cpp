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
