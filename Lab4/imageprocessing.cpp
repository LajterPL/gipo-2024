#include "imageprocessing.h"

#include <iostream>

float rotX(int x, int y, float cosA, float sinA) {
    return  (float) x * cosA - (float) y * sinA;
}

float rotY(int x, int y, float cosA, float sinA) {
    return (float) x * sinA + (float) y * cosA;
}

void moveImage(const QImage *src, QImage *dst, int dx, int dy) {

    dst->fill(0);

    if (dx == 0 && dy == 0) {
        *dst = src->copy();
    } else if (std::abs(dx) < src->width() && std::abs(dy) < src->height()) {
        for (int y = 0; y < src->height(); y++) {

            if (y + dy >= 0 && y + dy < src->height()) {
                QRgb* rgb_src = (QRgb*)src->scanLine(y);
                QRgb* rgb_dst = (QRgb*)dst->scanLine(y + dy);

                if (dx <= 0) {
                    std::copy(rgb_src - dx, rgb_src - dx + (src->width() + dx), rgb_dst);
                } else {
                    std::copy(rgb_src, rgb_src + (src->width() - dx), rgb_dst + dx);
                }
            }
        }
    }
}



void rotateImage(const QImage *src, QImage *dst, float a)
{
    a = (int) a % 360;
    a = a * (2*M_PI / 360.0f); // Zamiana na radiany

    float cosA = cos(a);
    float sinA = sin(a);

    int midX = src->width() / 2;
    int midY = src->height() / 2;

    int newWidth = 0;
    int newHeight = 0;

    int minX = 0;
    int minY = 0;

    {
        int testX[2] = {0, src->width()};
        int testY[2] = {0, src->height()};

        int maxX = 0;
        int maxY = 0;


        for (int y = 0; y < 2; y++) {
            for (int x = 0; x < 2; x++) {
                int newX = std::round(rotX(testX[x] - midX, testY[y] - midY, cosA, sinA));
                int newY = std::round(rotY(testX[x] - midX, testY[y] - midY, cosA, sinA));

                newX += midX;
                newY += midY;

                if (newX > maxX) {
                    maxX = newX;
                } else if (newX < minX) {
                    minX = newX;
                }

                if (newY > maxY) {
                    maxY = newY;
                } else if (newY < minY) {
                    minY = newY;
                }
            }
        }

        newWidth = maxX - minX;
        newHeight = maxY - minY;
    }


    //printf("Nowy rozmiar: %d x %d\n", newWidth, newHeight);

    *dst = QImage(newWidth, newHeight, QImage::Format_RGB32);
    dst->fill(0);


    for (int y = 0; y < src->height(); y++) {
        QRgb* rgb_src = (QRgb*)src->scanLine(y);
        for (int x = 0; x < src->width(); x++) {

            float newX = rotX(x - midX, y - midY, cosA, sinA);
            float newY = rotY(x - midX, y - midY, cosA, sinA);

            newX += midX;
            newY += midY;

            newX -= minX;
            newY -= minY;

            if (std::floor(newX) == newX) {
                if (std::floor(newY) == newY) {
                    dst->setPixel(newX, newY, rgb_src[x]);
                } else {
                    dst->setPixel(newX, std::ceil(newY), rgb_src[x]);
                    dst->setPixel(newX, std::floor(newY), rgb_src[x]);
                }
            } else {
                if (std::floor(newY) == newY) {
                    dst->setPixel(std::ceil(newX), newY, rgb_src[x]);
                    dst->setPixel(std::floor(newX), newY, rgb_src[x]);
                } else {
                    dst->setPixel(std::ceil(newX), std::ceil(newY), rgb_src[x]);
                    dst->setPixel(std::ceil(newX), std::floor(newY), rgb_src[x]);

                    dst->setPixel(std::floor(newX), std::ceil(newY), rgb_src[x]);
                    dst->setPixel(std::floor(newX), std::floor(newY), rgb_src[x]);
                }
            }
        }
    }
}



void scaleImage(const QImage *src, QImage *dst, float scale)
{
    *dst = QImage(src->width() * scale, src->height() * scale, QImage::Format_RGB32);
    dst->fill(0);


    for (int y = 0; y < dst->height(); y++) {

        QRgb* rgb_dst = (QRgb*) dst->scanLine(y);

        for (int x = 0; x < dst->height(); x++) {

            float sampleX = (float) x / scale;
            float sampleY = (float) y / scale;

            rgb_dst[x] = src->pixel(std::round(sampleX), std::round(sampleY));

        }
    }
}
