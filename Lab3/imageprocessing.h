#ifndef IMAGEPROCESSING_H
#define IMAGEPROCESSING_H

#include <QImage>

void medianFilter(const QImage *src, QImage *dst, int r);
void customConv(const QImage *src, QImage *dst, int *filter, int r);


#endif // IMAGEPROCESSING_H
