#ifndef IMAGEPROCESSING_H
#define IMAGEPROCESSING_H

#include <QImage>

void changeHSL(const QImage *src, QImage *dst, int h, int s, int l);

#endif // IMAGEPROCESSING_H
