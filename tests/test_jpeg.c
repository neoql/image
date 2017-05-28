//
// Created by moons on 17-5-22.
//

#include "../fmt/jpeg.h"
#include "../fmt/bitmap.h"


int main(int argc, char *argv[])
{
    image_t *img;

    img = load_jpeg(argv[1]);
    save_as_bmp(img, argv[2]);
    img_destroy(img);

    return 0;
}
