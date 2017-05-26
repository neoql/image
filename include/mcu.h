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


typedef struct {
    int16 Y[4][64];
    int16 Cr[64];
    int16 Cb[64];
} big_mcu_t;

extern int reverse_quantization(int16 cc[64], uint16 quantization_tab[64]);
extern int reverse_zig_zag(int16 cc[64]);
extern int minus_correct(int16 cc[64]);
extern int idct(int16 cc[64]);
extern int mkimg_from_mcus(mcu_t *mcus, image_t *image);
int mkimg_from_big_mcus(big_mcu_t *mcus, image_t *image);

#endif //IMAGE_MCU_H
