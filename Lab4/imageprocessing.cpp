#include "imageprocessing.h"

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
