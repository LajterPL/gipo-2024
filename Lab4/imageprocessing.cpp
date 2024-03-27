#include "imageprocessing.h"

#include <iostream>

int rotX(int x, int y, float cosA, float sinA) {
    return x * cosA - y * sinA;
}

int rotY(int x, int y, float cosA, float sinA) {
    return x * sinA + y * cosA;
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

    {
        int testX[2] = {0, src->width()};
        int testY[2] = {0, src->height()};

        for (int y = 0; y < 2; y++) {
            for (int x = 0; x < 2; x++) {
                int newX = rotX(testX[x] - midX, testY[y] - midY, cosA, sinA);
                int newY = rotY(testX[x] - midX, testY[y] - midY, cosA, sinA);

                newX += midX;
                newY += midY;

                newX = std::abs(newX);
                newY = std::abs(newY);

                if (newX > newWidth) {
                    newWidth = newX;
                }

                if (newY > newHeight) {
                    newHeight = newY;
                }
            }
        }
    }


    //printf("Nowy rozmiar: %d x %d\n", newWidth, newHeight);

    *dst = QImage(newWidth + 100, newHeight + 100, QImage::Format_RGB32);
    dst->fill(0);


    for (int y = 0; y < src->height(); y++) {
        QRgb* rgb_src = (QRgb*)src->scanLine(y);
        for (int x = 0; x < src->width(); x++) {

            int newX = rotX(x - midX, y - midY, cosA, sinA);
            int newY = rotY(x - midX, y - midY, cosA, sinA);

            newX += midX;
            newY += midY;

            dst->setPixel(newX, newY, rgb_src[x]);
        }
    }
}


