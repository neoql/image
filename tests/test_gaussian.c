//
// Created by moons on 17-5-18.
//

#include "bitmap.h"
#include "filter.h"
#include <stdio.h>


int main(int argc, char *argv[])
{
    image_t *img, *dst;

    if (argc < 3) {
        printf("Usage : <src_path> <dst_path>.\n");
    }

    img = load_bmp(argv[1]);

    dst = gaussian_filter(img, 20);
    save_as_bmp(dst, argv[2]);

    img_destroy(img);
    img_destroy(dst);

    return 0;
}
