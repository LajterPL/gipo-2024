#ifndef IMAGEPROCESSING_H
#define IMAGEPROCESSING_H

#include <QImage>

void changeHSL(const QImage *src, QImage *dst, int h, int s, int l);
void changeLAB(const QImage *src, QImage *dst, int l, int a, int b);

#endif // IMAGEPROCESSING_H
