//
// Created by moons on 17-5-22.
//

#include "jpeg.h"


int main(int argc, char *argv[])
{
    image_t img;

    load_jpeg(argv[1], &img);
    img_destroy(&img);

    return 0;
}
