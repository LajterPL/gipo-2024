#ifndef HSL_H
#define HSL_H

#include <QRgb>

class HSL
{
public:
    int hue;
    int saturation;
    int lumination;

    HSL(int h, float s, float l);
    static HSL fromRgb(int r, int g, int b);
    QRgb toRgb();
};

#endif // HSL_H
