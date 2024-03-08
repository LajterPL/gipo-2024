#include "imageprocessing.h"

#include "hsl.h"
#include <iostream>

void changeHSL(const QImage *src, QImage *dst, int h, int s, int l)
{

    float fs = s / 100.0f;
    float fl = l / 100.0f;

    for (int y = 0; y < src->height(); y++) {
        QRgb* rgb_src = (QRgb*)src->scanLine(y);
        QRgb* rgb_dst = (QRgb*)dst->scanLine(y);

        for (int x = 0; x < src->width(); x++) {

            QRgb rgb = rgb_src[x];

            int r = qRed(rgb);
            int g = qGreen(rgb);
            int b = qBlue(rgb);

            HSL hsl_color = HSL::fromRgb(r, g, b);

            printf("Test");

            hsl_color.hue = hsl_color.hue + h % 360;
            hsl_color.saturation = std::clamp(hsl_color.saturation + fs, 0.0f, 1.0f);
            hsl_color.lumination = std::clamp(hsl_color.lumination + fl, 0.0f, 1.0f);

            rgb = hsl_color.toRgb();

            rgb_dst[x] = rgb;
        }
    }
}
