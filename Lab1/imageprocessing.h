#ifndef IMAGEPROCESSING_H
#define IMAGEPROCESSING_H

#include <QImage>

void brightness(const QImage* src, QImage* dst, int value);

void contrast(const QImage* src, QImage* dst, int value);

void gamma(const QImage* src, QImage* dst, float value);

#endif // IMAGEPROCESSING_H
