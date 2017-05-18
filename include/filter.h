//
// Created by moons on 17-5-18.
//

#ifndef IMAGE_FILTER_H
#define IMAGE_FILTER_H

#include "image.h"


extern image_t * gaussian_filter(image_t *img, double sigma);
extern image_t * median_filter(image_t *img, uint16 radius);

#endif //IMAGE_FILTER_H
