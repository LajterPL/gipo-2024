#include "xyz.h"

XYZ::XYZ() {}

XYZ::XYZ(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

XYZ XYZ::fromRgb(int r, int g, int b)
{
    // Macierz kolorów RGB
    float c[3];
    // Macierz dla przestrzeni Adobe RGB
    float M[3][3] = {0.57667, 0.29734, 0.02703, 0.18556, 0.62736, 0.07069, 0.18823, 0.07529, 0.99134};
    // Macierz kolorów XYZ
    float xyz[3] = {0};

    // Normalizacja kolorów
    c[0] = r / 255.0f;
    c[1] = g / 255.0f;
    c[2] = b / 255.0f;

    for (int i = 0; i < 3; i++) {
        c[i] = std::pow(c[i], 2.2f);

        for (int j = 0; i < 3; j++) {
            xyz[i] += c[j] * M[j][i];
        }
    }

    return XYZ(xyz[0], xyz[1], xyz[2]);
}

QRgb XYZ::toRgb()
{
    // Macierz kolorów XYZ
    float xyz[3] = {this->x, this->y, this->z};
    // Macierz dla przestrzeni Adobe RGB
    float M[3][3] = {2.04159, -0.96924, 0.01344, -0.56501, 1.87597, -0.11836, -0.34473, 0.04156, 1.01517};
    // Macierz kolorów RGB
    float c[3] = {0};

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            c[i] += xyz[j] * M[j][i];
        }

        c[i] = std::clamp(c[i] * 255.0f, 0.0f, 255.0f);
    }

    return qRgb((int) c[0], (int) c[1], (int) c[2]);

}
