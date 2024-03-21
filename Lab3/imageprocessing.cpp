#include "imageprocessing.h"


void medianFilter(const QImage *src, QImage *dst, int r)
{

    QRgb** filterLines = new QRgb*[2*r + 1];

    for (int i = 0; i < r + 1; i++) {
        filterLines[r + i] = (QRgb*)src->scanLine(i);
    }

    for (int i = 0; i < r; i++) {
        filterLines[i] = filterLines[r]; // Padding
    }

    for (int y = 0; y < src->height(); y++) {

        int colorArr[3][256] = {0};

        QRgb* rgb_dst = (QRgb*)dst->scanLine(y);

        for (int x = 0; x < src->width(); x++) {

            for (int i = 0; i < 2*r + 1; i++) {
                for (int j = 0; j < 2*r + 1; j++) {

                    int x_index = 0;

                    if ((x - r) + j >= src->width()) {
                        x_index = src->width() - 1;
                    } else if ((x - r) + j > 0) {
                        x_index = (x - r) + j;
                    }

                    QRgb rgb = filterLines[i][x_index];

                    colorArr[0][qRed(rgb)]++;
                    colorArr[1][qGreen(rgb)]++;
                    colorArr[2][qBlue(rgb)]++;

                }
            }

            int colors[3] = {0};

            int middle = (std::pow(2*r + 1, 2) / 2) + 1;

            for (int i = 0; i < 3; i++) {
                int counter = middle;

                for (int value = 0; value < 256 && counter != 0; value++) {

                    for (int j = 0; j < colorArr[i][value] && counter != 0; j++) {
                        counter--;

                        if (counter == 0) {
                            colors[i] = value;
                        }
                    }
                }
            }

            for (int i = 0; i < 2*r + 1; i++) {

                int x_index = 0;

                if (x - r >= src->width()) {
                    x_index = src->width() - 1;
                } else if (x - r > 0) {
                    x_index = x - r;
                }

                QRgb rgb = filterLines[i][x_index];

                colorArr[0][qRed(rgb)]--;
                colorArr[1][qGreen(rgb)]--;
                colorArr[2][qBlue(rgb)]--;

            }


            rgb_dst[x] = qRgb(colors[0], colors[1], colors[2]);
        }


        for (int i = 1; i < 2*r + 1; i++) {
            filterLines[i - 1] = filterLines[i];
        }

        // Padding - wartości na brzegu
        if (y + r < src->height()) {
            filterLines[2*r] = (QRgb*)src->scanLine(y + r);
        } else {
            filterLines[2*r] = (QRgb*)src->scanLine(src->height() - 1);
        }

    }
}

void customConv(const QImage *src, QImage *dst, int **filter, int r)
{
    // Obliczanie sumy wartości filtra
    int filterSum = 0;

    for (int i = 0; i < 2*r + 1; i++) {
        for (int j = 0; j < 2*r + 1; j++) {
            filterSum += filter[i][j];
        }
    }

    QRgb** filterLines = new QRgb*[2*r + 1];

    for (int i = 0; i < r + 1; i++) {
        filterLines[r + i] = (QRgb*)src->scanLine(i);
    }

    for (int i = 0; i < r; i++) {
        filterLines[i] = filterLines[r];
    }

    // Splot

    for (int y = 0; y < src->height(); y++) {

        QRgb* rgb_dst = (QRgb*)dst->scanLine(y);

        for (int x = 0; x < src->width(); x++) {

            int sumRed = 0;
            int sumGreen = 0;
            int sumBlue = 0;

            for (int i = 0; i < 2*r + 1; i++) {
                for (int j = 0; j < 2*r + 1; j++) {

                    int x_index = 0;

                    if ((x - r) + j >= src->width()) {
                        x_index = src->width() - 1;
                    } else if ((x - r) + j > 0) {
                        x_index = (x - r) + j;
                    }

                    sumRed += filter[i][j] * qRed(filterLines[i][x_index]);
                    sumGreen += filter[i][j] * qGreen(filterLines[i][x_index]);
                    sumBlue += filter[i][j] * qBlue(filterLines[i][x_index]);

                }
            }

            if (filterSum != 0) {
                sumRed = sumRed / filterSum;
                sumGreen = sumGreen / filterSum;
                sumBlue = sumBlue / filterSum;
            }

            rgb_dst[x] = qRgb(sumRed, sumGreen, sumBlue);
        }


        for (int i = 1; i < 2*r + 1; i++) {
            filterLines[i - 1] = filterLines[i];
        }

        // Padding - wartości na brzegu
        if (y + r < src->height()) {
            filterLines[2*r] = (QRgb*)src->scanLine(y + r);
        } else {
            filterLines[2*r] = (QRgb*)src->scanLine(src->height() - 1);
        }

    }
}
