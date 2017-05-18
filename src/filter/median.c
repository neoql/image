//
// Created by moons on 17-5-18.
//

#include "filter.h"
#include <stdlib.h>


/* 冒泡排序 */
static void sort(int *array, int length)
{
    int i, j;
    int temp;

    for (i = 0; i < length - 1; i++) {
        for (j = i; j < length - 1; j++) {
            if (array[i] > array[j + 1]) {
                temp = array[i];
                array[i] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}


static color_t get_median_rgb(int x, int y, int radius, image_t *img)
{
    color_t color;
    int width, height;
    int xoffset, yoffset;
    int *r, *g, *b;
    int i, j;
    int m, length;

    width = height = radius * 2 + 1;
    xoffset = x - radius;
    yoffset = y - radius;

    if (x < radius) {               // 向前超出边界
        width -= radius;
        xoffset += radius;
    } else if (x + radius >= img->width) {
        width -= (x + radius - img->width + 1);
    }

    if (y < radius) {               // 向后超出边界
        height -= radius;
        yoffset += radius;
    } else if (y + radius >= img->height) {
        height -= (y + radius - img->height + 1);
    }

    r = malloc(sizeof(int) * width * height);
    g = malloc(sizeof(int) * width * height);
    b = malloc(sizeof(int) * width * height);

    for (i = 0; i < width; i++) {
        for (j = 0; j < height; j++) {
            color = img_get_color(img, i + xoffset, j + yoffset);
            r[j * width + i] = color.r;
            g[j * width + i] = color.g;
            b[j * width + i] = color.b;
        }
    }

    sort(r, width * height);
    sort(g, width * height);
    sort(b, width * height);

    length = width * height;

    m = length % 2 ? length / 2 + 1: length / 2;

    color.r = (uchar) r[m - 1];
    color.g = (uchar) g[m - 1];
    color.b = (uchar) b[m - 1];

    free(r);
    free(g);
    free(b);

    return color;
}


image_t * median_filter(image_t *img, uint16 radius)
{
    image_t *dest;
    int i, j;
    color_t color;

    dest = img_clone(img);

    for (i = 0; i < img->width; i++) {
        for (j = 0; j < img->height; j++) {
            color = get_median_rgb(i, j, radius, img);
            img_set_color(dest, i, j, color);
        }
    }

    return dest;
}
