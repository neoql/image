//
// Created by moons on 17-5-22.
//

#include <stdio.h>
#include "../util/bitstring.h"


int main(int argc, char *argv[])
{
    bitstring_t *str;
    bit_t bit;
    int i;

    str = create_bitstring();

    bitstring_append_byte(str, 0xFA);
    for (i = 0; i < 8; i++) {
        bit = bitstring_pop_bit(str);
        printf("%d\t", bit);
    }

    printf("\n");

    bitstring_destroy(str);

    return 0;
}
