//
// Created by moons on 17-5-18.
//

#include "bitmap.h"
#include "filter.h"


int main(int argc, char* argv[])
{
    image_t img, dest;

    load_bmp(argv[1], &img);

    median_filter(&img, &img, 1);

    save_as_bmp(&dest, argv[2]);


    img_destroy(&img);
    img_destroy(&dest);

    return 0;
}
