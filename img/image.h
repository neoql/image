//
// Created by moons on 17-5-5.
//

#ifndef TEST_JPEG_IMAGE_H
#define TEST_JPEG_IMAGE_H


typedef unsigned char   uchar;
typedef unsigned short  uint16;
typedef unsigned int    uint32;
typedef short int16;


typedef struct {
    uchar r;
    uchar g;
    uchar b;
} color_t;

typedef struct {
    uint32 height;
    uint32 width;
    color_t *points;
} image_t;


extern int img_init(image_t *img, uint32 height, uint32 width);
extern int img_destroy(image_t *img);
extern int img_get_color(const image_t *img, int x, int y, color_t *color);
extern int img_set_color(image_t *img, int x, int y, color_t color);
extern int img_clone(const image_t *src, image_t *dst);
extern int rgb2gray(const image_t *src, image_t *dst);

#endif //TEST_JPEG_IMAGE_H
