//
// Created by moons on 17-5-18.
//

#ifndef IMAGE_FILTER_H
#define IMAGE_FILTER_H

#include "../img/image.h"

extern int gauss_filter(const image_t *src, image_t *dst, double sigma);
extern int median_filter(const image_t *src, image_t *dst, int radius);

#endif //IMAGE_FILTER_H
