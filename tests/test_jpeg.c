//
// Created by moons on 17-5-22.
//

#include "jpeg.h"
#include "bitmap.h"


int main(int argc, char *argv[])
{
    image_t img;

    load_jpeg(argv[1], &img);
    save_as_bmp(&img, argv[2]);
    img_destroy(&img);

    return 0;
}
