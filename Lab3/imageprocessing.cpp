#include "imageprocessing.h"


void medianFilter(const QImage *src, QImage *dst, int r)
{
    QRgb** filterLines = new QRgb*[2*r + 1];

    for (int i = 0; i <= r; i++) {
        filterLines[r + i] = (QRgb*)src->scanLine(i);
        filterLines[r - i] = (QRgb*)src->scanLine(i); // Padding - odbicie lustrzane
    }

    for (int y = 0; y < src->height(); y++) {



        for (int i = 0; i < 2*r; i++) {
            filterLines[i] = filterLines[i + 1];
        }

        // Padding - odbicie lustrzane obrazka
        if (y + r <= src->height()) {
            filterLines[2*r] = (QRgb*)src->scanLine(y + r);
        } else {
            filterLines[2*r] = (QRgb*)src->scanLine(2 * src->height() - (y + r));
        }

    }
}

void customConv(const QImage *src, QImage *dst, int *filter, int r)
{

}
