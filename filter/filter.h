//
// Created by moons on 17-5-18.
//

#ifndef IMAGE_FILTER_H
#define IMAGE_FILTER_H

#include "../img/image.h"

extern image_t * gauss_filter(const image_t *src, double sigma);
extern image_t * median_filter(const image_t *src, uint32 radius);

#endif //IMAGE_FILTER_H
