//
// Created by moons on 17-5-12.
//

#include <stdio.h>
#include "dct.h"
#include <math.h>


#define PI 3.1415926


static mat_t* create_trans_mat(uint32 n)
{
    mat_t *mat;
    int i, j;
    double a;

    mat = create_mat(n, n);
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (i == 0) {
                a = sqrt(1.0 / n);
            } else {
                a = sqrt(2.0 / n);
            }
            mat->content[i][j] =  a * cos(PI * (j + 0.5) * i / n);
        }
    }

    return mat;
}


mat_t * DCT(mat_t *src)
{
    mat_t *a, *a_zz, *dest, *tmp;
    uint32 n;


    if (src->width == src->height) {
        n = src->width;
    } else {
        return NULL;
    }

    a = create_trans_mat(n);
//    mat_print(a);
    a_zz = mat_transposition(a);

    tmp = mat_multiply(a, src);
    dest = mat_multiply(tmp, a_zz);

    mat_destroy(a_zz);
    mat_destroy(a);
    mat_destroy(tmp);

    return dest;
}


mat_t * IDCT(mat_t *src)
{
    mat_t *a, *a_zz, *dest, *tmp;
    uint32 n;


    if (src->width == src->height) {
        n = src->width;
    } else {
        return NULL;
    }

    a = create_trans_mat(n);
    a_zz = mat_transposition(a);

    tmp = mat_multiply(a_zz, src);
    dest = mat_multiply(tmp, a);

    mat_destroy(a_zz);
    mat_destroy(a);
    mat_destroy(tmp);

    return dest;
}
