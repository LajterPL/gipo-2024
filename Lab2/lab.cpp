#include "lab.h"

#include "xyz.h"

LAB::LAB(float l, float a, float b)
{
    this->l = l;
    this->a = a;
    this->b = b;
}

LAB LAB::fromRgb(int r, int g, int b)
{
    XYZ xyz = XYZ::fromRgb(r, g, b);


}
