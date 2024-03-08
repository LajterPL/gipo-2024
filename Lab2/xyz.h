#ifndef XYZ_H
#define XYZ_H

#include <QRgb>

class XYZ
{
public:
    float x;
    float y;
    float z;

    XYZ(float x, float y, float z);
    static XYZ fromRgb(int r, int g, int b);
    QRgb toRgb();
};

#endif // XYZ_H
