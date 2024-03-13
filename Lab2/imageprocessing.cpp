#include "imageprocessing.h"

#include "hsl.h"
#include "lab.h"

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

            hsl_color.hue = hsl_color.hue + h % 360;
            hsl_color.saturation = std::clamp(hsl_color.saturation + fs, 0.0f, 1.0f);
            hsl_color.lumination = std::clamp(hsl_color.lumination + fl, 0.0f, 1.0f);

            rgb = hsl_color.toRgb();

            rgb_dst[x] = rgb;
        }
    }
}



void changeLAB(const QImage *src, QImage *dst, int l, int a, int b)
{
    for (int y = 0; y < src->height(); y++) {
        QRgb* rgb_src = (QRgb*)src->scanLine(y);
        QRgb* rgb_dst = (QRgb*)dst->scanLine(y);

        for (int x = 0; x < src->width(); x++) {

            QRgb rgb = rgb_src[x];

            int r = qRed(rgb);
            int g = qGreen(rgb);
            int b = qBlue(rgb);

            LAB lab_color = LAB::fromRgb(r, g, b);

            lab_color.l = std::clamp(lab_color.l + (float) l, -100.0f, 100.0f);
            lab_color.a = std::clamp(lab_color.a + (float) a, -128.0f, 127.0f);
            lab_color.b = std::clamp(lab_color.b + (float) b, -128.0f, 127.0f);

            rgb = lab_color.toRgb();

            rgb_dst[x] = rgb;
        }
    }
}
