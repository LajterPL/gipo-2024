#include "hsl.h"
#include <algorithm>
#include <cmath>

HSL::HSL(int h, float s, float l)
{
    this->hue = h % 360;
    this->saturation = std::clamp(s, 0.0f, 1.0f);
    this->lumination = std::clamp(l, 0.0f, 1.0f);
}

HSL HSL::fromRgb(int r, int g, int b)
{
    // Normalizacja RGB do przedziału 0 .. 1
    float fr = r / 255.0f;
    float fg = g / 255.0f;
    float fb = b / 255.0f;

    // Zmienne pomocnicze

    float max = std::max(fr, std::max(fg, fb));
    float min = std::min(fr, std::min(fg, fb));

    float dm = max - min;

    // Luminacja

    float l = (max + min) / 2.0f;

    // Saturacja

    float s;

    if (l == 0 || max == min) {
        s = 0;
    } else if (l > 0.5f) {
        s = dm / (2.0f - (2.0f * l));
    } else {
        s = dm / (2.0f * l);
    }

    // Barwa

    int h;

    if (max == fg) {
        h = 60 * (fb - fr) / dm + 120;
    } else if (max == fb) {
        h = 60 * (fr - fg) / dm + 240;
    } else {
        if (fg < fb) {
            h = 60 * (fg - fb) / dm + 360;
        } else {
            h = 60 * (fg - fb) / dm;
        }
    }

    return HSL(h, s, l);

}

QRgb HSL::toRgb()
{
    // Jeśli nasycenie = 0, to znaczenie ma tylko luminacja
    if (this->saturation == 0) {
        int color = std::clamp((int) std::round(this->lumination * 255.0f), 0, 255);

        return qRgb(color, color, color);
    }

    // Zmienne pomocnicze
    float q;

    if (this->lumination < 0.5f) {
        q = this->lumination * (1 + this->saturation);
    } else {
        q = this->lumination + this->saturation - this->lumination * this->saturation;
    }

    float p = 2 * this->lumination - q;

    float h = this->hue / 360.0f;

    float t[3];

    t[0] = h + 1 / 3.0f;  // Tr
    t[1] = h;             // Tg
    t[2] = h - 1 / 3.0f;  // Tb

    float c[3]; // Kolory RGB

    for (int i = 0; i < 3; i++) {

        if (t[i] < 0) {
            t[i]++;
        } else if (t[i] > 1) {
            t[i]--;
        }

        // Obliczanie koloru RGB
        if (t[i] < 1 / 6.0f) {
            c[i] = p + (q - p) * 6 * t[i];
        } else if (t[i] < 0.5f) {
            c[i] = q;
        } else if (t[i] < 2 / 3.0f) {
            c[i] = p + (q + p) * 6 * (2 / 3.0f - t[i]);
        } else {
            c[i] = p;
        }
    }

    int r = std::clamp((int) (c[0] * 255.0f), 0, 255);
    int g = std::clamp((int) (c[1] * 255.0f), 0, 255);
    int b = std::clamp((int) (c[2] * 255.0f), 0, 255);


    return qRgb(r, g, b);
}






