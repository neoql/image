//
// Created by moons on 17-5-22.
//

#ifndef IMAGE_BITSTRING_H
#define IMAGE_BITSTRING_H


#include "../img/image.h"
typedef unsigned char bit_t;

#define MIN_SIZE 65535

typedef struct {
    bit_t *__content;
    bit_t *__head;
    bit_t *__end;
    uint32 __size;
} bitstring_t;

extern bitstring_t * create_bitstring();
extern int bitstring_destroy(bitstring_t *str);
extern int bitstring_append_bit(bitstring_t *str, bit_t bit);
extern int bitstring_append_byte(bitstring_t *str, uchar byte);
extern int bitstring_length(const bitstring_t *str);
extern bit_t bitstring_pop_bit(bitstring_t *str);
extern int bitstring_pop_bits(bitstring_t *str, bit_t *dst, uint32 n);

#endif //IMAGE_BITSTRING_H
