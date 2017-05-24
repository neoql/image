//
// Created by moons on 17-5-23.
//

#ifndef IMAGE_MCU_H
#define IMAGE_MCU_H

#include "image.h"

typedef struct {
    int16 Y[64];
    int16 Cr[64];
    int16 Cb[64];
} mcu_t;

#endif //IMAGE_MCU_H
