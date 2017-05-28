//
// Created by moons on 17-5-14.
//

#include "image.h"
#include <stdlib.h>


image_t * create_empty_img(uint32 height, uint32 width)
{
    image_t *img;

    img = malloc(sizeof(image_t));

    img->height = height;
    img->width = width;
    img->points = calloc(height * width, sizeof(color_t));

    return img;
}


int img_destroy(image_t *img)
{
    free(img->points);
    free(img);
    return 0;
}


int img_get_color(const image_t *img, int x, int y, color_t *color)
{
    int index;

    if (x < 0 || x > img->width || y < 0 || y > img->height) {
        return -1;
    }

    index = y * img->width + x;
    *color = img->points[index];

    return 0;
}


int img_set_color(image_t *img, int x, int y, color_t color)
{
    int index;

    index = y * img->width + x;
    img->points[index] = color;

    return 0;
}


image_t * img_clone(const image_t *src)
{
    color_t color;
    int i, j;
    image_t *dst;

    dst = create_empty_img(src->height, src->width);
    for (i = 0; i < src->height; i++) {
        for (j = 0; j < src->width; j++) {
            img_get_color(src, j, i, &color);
            img_set_color(dst, j, j, color);
        }
    }

    return dst;
}


image_t * rgb2gray(const image_t *src)
{
    int i, j;
    uchar gray;
    color_t color;
    image_t *dst;

    dst = create_empty_img(src->height, src->width);
    for (i = 0; i < src->height; i++) {
        for (j = 0; j < src->width; j++) {
            img_get_color(src, j, i, &color);
            gray = (uchar) (color.r * 0.299 + color.g * 0.587 + color.b * 0.114);
            color.r = color.g = color.b = gray;
            img_set_color(dst, j, i, color);
        }
    }

    return dst;
}
