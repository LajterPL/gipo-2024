#ifndef LAB_H
#define LAB_H

#include <QRgb>

class LAB
{
public:
    float l;
    float a;
    float b;

    static float ep;
    static float k;

    LAB(float l, float a, float b);
    static LAB fromRgb(int r, int g, int b);
    QRgb toRgb();
};

#endif // LAB_H
