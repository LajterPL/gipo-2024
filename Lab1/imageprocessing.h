#ifndef IMAGEPROCESSING_H
#define IMAGEPROCESSING_H

#include <QImage>

void changeBrightness(const QImage* src, QImage* dst, int value);

void changeContrast(const QImage* src, QImage* dst, int value);

void changeGamma(const QImage* src, QImage* dst, int value);

void hist(const QImage* src, int* hist, int color);

#endif // IMAGEPROCESSING_H
