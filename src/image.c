//
// Created by moons on 17-5-14.
//

#include "image.h"
#include <stdlib.h>


image_t * create_img(uint32 height, uint32 width)
{
    image_t *img;

    img = malloc(sizeof(image_t));
    img->height = height;
    img->width = width;

    img->points = calloc(height * width, sizeof(color_t));

    return img;
}


void img_destroy(image_t *img)
{
    free(img->points);
    free(img);
}


color_t img_get_color(image_t *img, int x, int y)
{
    color_t color = {0, 0, 0};
    int index;

    if (x < 0 || x > img->width || y < 0 || y > img->height) {
        return color;
    }

    index = y * img->width + x;
    color = img->points[index];

    return color;
}


void img_set_color(image_t *img, int x, int y, color_t color)
{
    int index;

    index = y * img->width + x;
    img->points[index] = color;
}


image_t * img_clone(image_t *img)
{
    image_t *dst;
    color_t color;
    int i, j;

    dst = create_img(img->height, img->width);

    for (i = 0; i < img->height; i++) {
        for (j = 0; j < img->width; j++) {
            color = img_get_color(img, j, i);
            img_set_color(img, j, j, color);
        }
    }

    return dst;
}


image_t * rgb2gray(image_t * img)
{
    image_t *dst;
    int i, j;
    uchar gray;
    color_t color;

    dst = create_img(img->height, img->width);

    for (i = 0; i < img->height; i++) {
        for (j = 0; j < img->width; j++) {
            color = img_get_color(img, j, i);
            gray = (uchar) (color.r * 0.299 + color.g * 0.587 + color.b * 0.114);
            color.r = color.g = color.b = gray;
            img_set_color(dst, j, i, color);
        }
    }

    return dst;
}
