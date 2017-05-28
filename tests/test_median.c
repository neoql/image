//
// Created by moons on 17-5-18.
//

#include "../fmt/bitmap.h"
#include "../filter/filter.h"


int main(int argc, char* argv[])
{
    image_t *img, *dest;

    img = load_bmp(argv[1]);

    dest = median_filter(img, 1);

    save_as_bmp(dest, argv[2]);


    img_destroy(img);
    img_destroy(dest);

    return 0;
}
