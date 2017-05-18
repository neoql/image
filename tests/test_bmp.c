#include "bitmap.h"
#include <stdio.h>


int main(int argc, char *argv[])
{
    image_t *img;

    if (argc < 3) {
        printf("Usage : <src_path> <dst_path>.\n");
    }

    img = load_bmp(argv[1]);
    save_as_bmp(img, argv[2]);

    img_destroy(img);

    return 0;
}
