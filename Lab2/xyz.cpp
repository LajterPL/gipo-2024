#include "xyz.h"

#include <algorithm>

float XYZ::white[3] = {0.9505, 1.0000, 1.0891};

XYZ::XYZ(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

XYZ XYZ::fromRgb(int r, int g, int b)
{
    // Macierz kolorów RGB
    float rgb[3] = {(float) r / 255.0f, (float) g / 255.0f, (float) b / 255.0f};

    // Macierz dla przestrzeni sRGB
    float M[3][3] = {0.4124564,  0.3575761,  0.1804375,
                     0.2126729,  0.7151522,  0.0721750,
                     0.0193339,  0.1191920,  0.9503041};

    // Macierz kolorów XYZ
    float xyz[3] = {0};


    for (int i = 0; i < 3; i++) {
        rgb[i] = std::pow(rgb[i], 2.2);
    }

    for (int i = 0; i < 3; i++) {
        xyz[i] = M[i][0] * rgb[0] + M[i][1] * rgb[1] + M[i][2] * rgb[2];
    }

    return XYZ(xyz[0], xyz[1], xyz[2]);
}

QRgb XYZ::toRgb()
{
    // Macierz kolorów XYZ
    float xyz[3] = {this->x, this->y, this->z};

    // Macierz dla przestrzeni sRGB
    float M[3][3] = {3.2404542, -1.5371385, -0.4985314,
                     -0.9692660,  1.8760108,  0.0415560,
                     0.0556434, -0.2040259,  1.0572252};

    // Macierz kolorów RGB
    float rgb[3] = {0};


    for (int i = 0; i < 3; i++) {
        rgb[i] = M[i][0] * xyz[0] + M[i][1] * xyz[1] + M[i][2] * xyz[2];

        rgb[i] = std::pow(rgb[i], 1.0f / 2.2f);

        rgb[i] = std::clamp(std::round(rgb[i] * 255.0f), 0.0f, 255.0f);
    }

    return qRgb((int) rgb[0], (int) rgb[1], (int) rgb[2]);

}
