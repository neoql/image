//
// Created by moons on 17-5-12.
//

#include "mat.h"
#include <stdlib.h>
#include <stdio.h>


mat_t * create_mat(uint32 height, uint32 width)
{
    mat_t *mat;
    int i;

    mat = malloc(sizeof(mat_t));
    mat->height = height;
    mat->width = width;

    mat->content = calloc(height, sizeof(double *));
    for (i = 0; i < height; i++) {
        mat->content[i] = calloc(width, sizeof(double));
    }

    return mat;
}


void mat_destroy(mat_t *mat)
{
    int i;

    for (i = 0; i < mat->height; i++) {
        free(mat->content[i]);
    }

    free(mat->content);
    free(mat);
}


void mat_print(mat_t *mat)
{
    int i, j;

    printf("[");

    for (i = 0; i < mat->height; i++) {
        printf("[");

        for(j = 0; j < mat->width; j++) {
            printf("%lf", mat->content[i][j]);
            if (j < mat->width - 1) {
                printf(", ");
            }
        }

        printf("]");
        if (i < mat->height - 1) {
            printf(",\n ");
        }
    }

    printf("]\n");
}


mat_t * mat_transposition(mat_t *mat)
{
    uint32 height, width;
    int i, j;
    mat_t *dest;

    height = mat->height;
    width = mat->width;
    dest = create_mat(width, height);

    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            dest->content[j][i] = mat->content[i][j];
        }
    }

    return dest;
}


mat_t * mat_multiply(mat_t *a, mat_t *b)
{
    int m, p, n;
    int i, j, k;
    mat_t *c;

    if (a->width != b->height) {
        return NULL;
    }

    m = a->height;
    n = b->width;
    p = a->width;

    c = create_mat(m, n);

    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            for (k = 0; k < p; k++) {
                c->content[i][j] += a->content[i][k] * b->content[k][j];
            }
        }
    }

    return c;
}
