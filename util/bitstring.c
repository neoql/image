//
// Created by moons on 17-5-22.
//

#include "bitstring.h"
#include <stdlib.h>
#include "bitstring.h"


bitstring_t * create_bitstring()
{
    bitstring_t *str;

    str = malloc(sizeof(bitstring_t));

    str->__content = calloc(MIN_SIZE, sizeof(bit_t));
    str->__size = MIN_SIZE;

    str->__head = str->__content;
    str->__end  = str->__content;

    return str;
}


int bitstring_destroy(bitstring_t *str)
{
    free(str->__content);
    free(str);
    return 0;
}


int bitstring_append_bit(bitstring_t *str, bit_t bit)
{
    unsigned long head, end;

    if ((str->__end - str->__content) > str->__size * 0.75) {
        head = str->__head - str->__content;
        end = str->__end - str->__content;

        str->__content = realloc(str->__content, str->__size * 2);
        str->__size *= 2;

        str->__head = str->__content + head;
        str->__end = str->__content + end;
    }

    *str->__end++ = bit;

    return 0;
}


int bitstring_append_byte(bitstring_t *str, uchar byte)
{
    int i;

    for (i = 0; i < 8; i++) {
        bitstring_append_bit(str, byte >> 7);
        byte <<= 1;
    }

    return 0;
}


int bitstring_length(const bitstring_t *str)
{
    return (int) (str->__end - str->__head);
}


bit_t bitstring_pop_bit(bitstring_t *str)
{
    return *str->__head++;
}


int bitstring_pop_bits(bitstring_t *str, bit_t *dst, uint32 n)
{
    int i;

    for (i = 0; i < n; i++) {
        dst[i] = bitstring_pop_bit(str);
    }

    return 0;
}
