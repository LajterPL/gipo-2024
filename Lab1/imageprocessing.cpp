#include "imageprocessing.h"

void brightness(const QImage *src, QImage* dst, int value)
{

    for (int y = 0; y < src->height(); y++) {
        QRgb* rgb_src = (QRgb*)src->scanLine(y);
        QRgb* rgb_dst = (QRgb*)dst->scanLine(y);

        for (int x = 0; x < src->width(); x++) {

            //QRgb rgb = src->pixel(x, y);
            QRgb rgb = rgb_src[x];

            //int r = ((rgb >> 16) & 0xFF);
            //int g = ((rgb >> 8) & 0xFF);
            //int b = (rgb & 0xFF);

            int r = qRed(rgb);
            int g = qGreen(rgb);
            int b = qBlue(rgb);

            r = std::clamp(r + value, 0, 255);
            g = std::clamp(g + value, 0, 255);
            b = std::clamp(b + value, 0, 255);

            //rgb = b + (g<<8) + (r<<16);
            rgb = qRgb(r, g, b);

            //dst->setPixel(x, y, rgb);
            rgb_dst[x] = rgb;
        }
    }

}

void contrast(const QImage *src, QImage *dst, int value)
{

}

void gamma(const QImage *src, QImage *dst, float value)
{
// normalizacja rgb na wartości <0, 1>
}
