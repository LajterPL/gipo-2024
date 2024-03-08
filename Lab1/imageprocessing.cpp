#include "imageprocessing.h"

void changeBrightness(const QImage *src, QImage* dst, int value)
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

void changeContrast(const QImage *src, QImage *dst, int value)
{

    for (int y = 0; y < src->height(); y++) {
        QRgb* rgb_src = (QRgb*)src->scanLine(y);
        QRgb* rgb_dst = (QRgb*)dst->scanLine(y);

        for (int x = 0; x < src->width(); x++) {

            QRgb rgb = rgb_src[x];

            int r = qRed(rgb);
            int g = qGreen(rgb);
            int b = qBlue(rgb);

            float gray = 127.0f;

            if (value > 0) {
                r = std::clamp((int)(gray/(gray - value) * (r - value)), 0, 255);
                g = std::clamp((int)(gray/(gray - value) * (g - value)), 0, 255);
                b = std::clamp((int)(gray/(gray - value) * (b - value)), 0, 255);

            } else if (value < 0) {
                r = std::clamp((int)((gray + value)/gray * r - value), 0, 255);
                g = std::clamp((int)((gray + value)/gray * g - value), 0, 255);
                b = std::clamp((int)((gray + value)/gray * b - value), 0, 255);
            }

            rgb = qRgb(r, g, b);

            rgb_dst[x] = rgb;
        }
    }
}

void changeGamma(const QImage *src, QImage *dst, int value)
{

    float fv = value / 100.0f;

    for (int y = 0; y < src->height(); y++) {
        QRgb* rgb_src = (QRgb*)src->scanLine(y);
        QRgb* rgb_dst = (QRgb*)dst->scanLine(y);

        for (int x = 0; x < src->width(); x++) {

            QRgb rgb = rgb_src[x];

            float r = qRed(rgb) / 255.0f;
            float g = qGreen(rgb) / 255.0f;
            float b = qBlue(rgb) / 255.0f;

            r = std::clamp((int) (std::pow(r, fv) * 255.0f), 0, 255);
            g = std::clamp((int) (std::pow(g, fv) * 255.0f), 0, 255);
            b = std::clamp((int) (std::pow(b, fv) * 255.0f), 0, 255);

            rgb = qRgb((int) r, (int) g, (int) b);

            rgb_dst[x] = rgb;
        }
    }
}

void hist(const QImage *src, int* hist, int color)
{
    for (int y = 0; y < src->height(); y++) {
        QRgb* rgb_src = (QRgb*)src->scanLine(y);

        for (int x = 0; x < src->width(); x++) {

            QRgb rgb = rgb_src[x];

            int r = qRed(rgb);
            int g = qGreen(rgb);
            int b = qBlue(rgb);

            switch(color) {
            case 0:
                *(hist + r) = *(hist + r) + 1;
                break;
            case 1:
                hist[g]++;
                break;
            case 2:
                hist[b]++;
                break;
            case 3:
                hist[(int) (0.21 * r + 0.72 * g + 0.07 * b)]++;
            }
        }
    }
}
