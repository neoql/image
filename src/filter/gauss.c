//
// Created by moons on 17-5-18.
//

#include "filter.h"
#include <math.h>
#include <stdlib.h>


#define PI 3.1415926


static double get_weight(int x, double sigma)
{
    double weight;

    weight = (1 / (pow(2 * PI, 0.5) * sigma)) * exp(- (x * x) / (2 * sigma * sigma));

    return weight;
}


static double * get_weight_array(double sigma, int radius, int start, int end)
{
    double *wa;
    int i;
    double sum = 0;

    wa = malloc(sizeof(double) * (radius * 2 + 1));

    for (i = 0; i < radius * 2 + 1; i++) {
        wa[i] = 0;
    }

    for (i = start; i <= end; i++) {
        wa[i] = get_weight(i - radius, sigma);
        sum += wa[i];
    }

    for (i = start; i <= end; i++) {
        wa[i] /= sum;
    }

    return wa;
}


static color_t * get_color_array(const image_t *img, int x, int y, int radius, int direct)
{
    color_t *ca;
    int len;
    int i;

    len = radius * 2 + 1;
    ca = malloc(sizeof(color_t) * len);

    if (direct) {
        // H
        x -= radius;
    } else {
        // V
        y -= radius;
    }

    for (i = 0; i < len; i++) {
        if (direct) {
            // H
            img_get_color(img, x + i, y, ca + i);
        } else {
            // V
            img_get_color(img, x, y + i, ca + i);
        }
    }

    return ca;
}


static color_t get_blur_color(color_t *ca, double *wa, int radius)
{
    color_t color;
    int i;
    int len;
    double r, g, b;

    len = radius * 2 + 1;
    r = 0;
    g = 0;
    b = 0;

    for (i = 0; i < len; i++) {
        r += ca[i].r * wa[i];
        g += ca[i].g * wa[i];
        b += ca[i].b * wa[i];
    }
    color.r = (uchar)r;
    color.g = (uchar)g;
    color.b = (uchar)b;

    return color;
}


static void hfilter(image_t *dest, const image_t *src, double sigma, int radius)
{
    int x, y;
    double* wa, *wsa;
    color_t *ca;
    color_t color;
    int start, end;

    wa = get_weight_array(sigma, radius, 0, radius * 2);

    for (x = 0; x < src->width; x++) {
        if (x < radius || x >= src->width - radius) {
            start = 0;
            end = radius * 2;
            if (x < radius) {
                start = radius - x;
            }
            if (x >= src->width - radius) {
                end = radius + src->width - x - 1;
            }
            wsa = get_weight_array(sigma, radius, start, end);
        } else {
            wsa = wa;
        }

        for (y = 0; y < src->height; y++) {

            ca = get_color_array(src, x, y, radius, 1);
            color = get_blur_color(ca, wsa, radius);
            img_set_color(dest, x, y, color);
            free(ca);

        }
        if (wsa != wa) {
            free(wsa);
        }
    }
    free(wa);
}


static void vfilter(image_t *dest, const image_t *src, double sigma, int radius)
{
    int x, y;
    double* wa, *wsa;
    color_t *ca;
    color_t color;
    int start, end;

    wa = get_weight_array(sigma, radius, 0, radius * 2);

    for (y = 0; y < src->height; y++) {
        if (y < radius || y >= src->height - radius) {
            start = 0;
            end = radius * 2;
            if (y < radius) {
                start = radius - y;
            }
            if (y >= src->height - radius) {
                end = radius + src->height - y - 1;
            }
            wsa = get_weight_array(sigma, radius, start, end);
        } else {
            wsa = wa;
        }
        for (x = 0; x < src->width; x++) {

            ca = get_color_array(src, x, y, radius, 0);
            color = get_blur_color(ca, wsa, radius);
            img_set_color(dest, x, y, color);
            free(ca);

        }
        if (wsa != wa) {
            free(wsa);
        }
    }
    free(wa);
}


int gauss_filter(const image_t *src, image_t *dst, double sigma)
{
    image_t tmp;
    int radius;

    img_init(&tmp, src->height, src->width);
    img_init(dst, src->height, src->width);
    radius = (int) ceil(sigma * 3);

    hfilter(&tmp, src, sigma, radius);
    vfilter(dst, &tmp, sigma, radius);

    img_destroy(&tmp);

    return 0;
}
