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


extern image_t * create_img(uint32 height, uint32 width);
extern void img_destroy(image_t *img);
extern color_t img_get_color(image_t *img, int x, int y);
extern void img_set_color(image_t *img, int x, int y, color_t color);
extern image_t * img_clone(image_t *img);
extern image_t * rgb2gray(image_t * img);

#endif //TEST_JPEG_IMAGE_H
