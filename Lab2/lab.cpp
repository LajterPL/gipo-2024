#include "lab.h"

#include "xyz.h"

float LAB::ep = 0.008856;
float LAB::k = 903.3;

LAB::LAB(float l, float a, float b)
{
    this->l = l;
    this->a = a;
    this->b = b;
}

LAB LAB::fromRgb(int r, int g, int blue)
{
    XYZ xyz = XYZ::fromRgb(r, g, blue);

    float xyz_arr[3] = {xyz.x, xyz.y, xyz.z};

    for (int i = 0; i < 3; i++) {
        xyz_arr[i] = xyz_arr[i] / XYZ::white[i];

        if (xyz_arr[i] > LAB::ep) {
            xyz_arr[i] = std::pow(xyz_arr[i], 1.0f / 3.0f );
        } else {
            xyz_arr[i] = ((xyz_arr[i] * LAB::k) + 16.0f) / 116.0f;
        }
    }

    float l = 116.0f * xyz_arr[1] - 16.0f;
    float a = 500.0f * (xyz_arr[0] - xyz_arr[1]);
    float b = 200.0f * (xyz_arr[1] - xyz_arr[2]);

    return LAB(l, a, b);
}

QRgb LAB::toRgb()
{
    float xyz[3] = {0};
    float f_xyz[3] = {0};

    if (this->l > LAB::k * LAB::ep) {
        xyz[1] = std::pow((this->l + 16.0f) / 116.0f, 3.0f);
    } else {
        xyz[1] = this->l / LAB::k;
    }

    if (xyz[1] > LAB::ep) {
        f_xyz[1] = this->l;
    } else {
        f_xyz[1] = xyz[1] * LAB::k;
    }

    f_xyz[1] = (f_xyz[1] + 16.0f) / 116.0f;
    f_xyz[0] = (this->a / 500.0f) + f_xyz[1];
    f_xyz[2] = f_xyz[1] - (this->b / 200.0f);

    for (int i = 0; i < 3; i++) {
        if (i != 1) {
            float temp = std::pow(f_xyz[i], 3);

            if (temp > LAB::ep) {
                xyz[i] = temp;
            } else {
                xyz[i] = ((116.0f * f_xyz[i]) - 16.0f) / LAB::k;
            }
        }

        xyz[i] = xyz[i] * XYZ::white[i];
    }

    return XYZ(xyz[0], xyz[1], xyz[2]).toRgb();
}


