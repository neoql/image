//
// Created by moons on 17-5-23.
//

#include "mcu.h"
#include <string.h>
#include "dct.h"


#define clamp(a) (a < 0 ? 0 : a > 255 ? 255 : a)


const static int ZIG_ZAG_TAB[] = {
         0,  1,  5,  6, 14, 15, 27, 28,
         2,  4,  7, 13, 16, 26, 29, 42,
         3,  8, 12, 17, 25, 30, 41, 43,
         9, 11, 18, 24, 31, 40, 44, 53,
        10, 19, 23, 32, 39, 45, 52, 54,
        20, 22, 33, 38, 46, 51, 55, 60,
        21, 34, 37, 47, 50, 56, 59, 61,
        35, 36, 48, 49, 57, 58, 62, 63,
};


int reverse_quantization(int16 cc[64], uint16 quantization_tab[64])
{
    int i;

    for (i = 0; i < 64; i++) {
        cc[i] *= quantization_tab[i];
    }

    return 0;
}


int reverse_zig_zag(int16 cc[64])
{
    int i, index;
    int16 tmp[64];

    memcpy(tmp, cc, sizeof(int16) * 64);
    for (i = 0; i < 64; i++) {
        index = ZIG_ZAG_TAB[i];
        cc[i] = tmp[index];
    }

    return 0;
}


int minus_correct(int16 cc[64])
{
    int i, j, index;

    for (i = 0; i < 8; i++) {
        if (i % 2) {
            for (j = 0; j < 8; j++) {
                index = i * 8 + j;
                cc[index] = -cc[index];
            }
        }
    }

    return 0;
}


int idct(int16 cc[64])
{
    mat_t *mat, *dest;
    int i;

    mat = create_mat(8, 8);

    for (i = 0; i < 64; i++) {
        mat->content[i / 8][i % 8] = cc[i];
    }

    dest = IDCT(mat);

    for (i = 0; i < 64; i++) {
        cc[i] = (int16) dest->content[i / 8][i % 8];
    }

    mat_destroy(mat);
    mat_destroy(dest);

    return 0;
}


int mkimg(mcu_t mcus[], image_t *image)
{
    int i, j, k, index = 0;
    int x, y;
    mcu_t *mcu;
    color_t color;
    double r, g ,b, Y, Cr, Cb;

    for (i = 0; i < image->height / 8; i++) {
        for (j = 0; j < image->width / 8; j++) {
            mcu = mcus + index;
            index++;
            for (k = 0; k < 64; k++) {
                x = j * 8 + k % 8;
                y = i * 8 + 7 - k / 8;

                Y = mcu->Y[k];
                Cb = mcu->Cb[k];
                Cr = mcu->Cr[k];

                r = clamp(Y + 1.402 * Cr + 128);
                g = clamp(Y - 0.3441363 * Cb - 0.71413636 * Cr + 128);
                b = clamp(Y + 1.772 * Cb + 128);

                color.r = (uchar) r;
                color.g = (uchar) g;
                color.b = (uchar) b;

                img_set_color(image, x, y, color);
            }
        }
    }
    return 0;
}
