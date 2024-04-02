#ifndef IMAGEPROCESSING_H
#define IMAGEPROCESSING_H

#include <QImage>

void moveImage(const QImage *src, QImage *dst, int x, int y);
void rotateImage(const QImage *src, QImage *dst, float a);
void scaleImage(const QImage *src, QImage *dst, float scale);

#endif // IMAGEPROCESSING_H
