//
// Created by moons on 17-5-14.
//

#ifndef TEST_JPEG_BITMAP_H
#define TEST_JPEG_BITMAP_H


#include "image.h"

typedef struct {
    uint16 bfType;                      // 标识"BM"
    uint32 bfSize;                      // 整个bmp文件的大小
    uint32 bfReserved;                  // 保留字，暂无用处
    uint32 bfOffBits;                   // 偏移数， 即 位图文件头+位图信息头+调色板 的大小
} FILE_HEADER;


typedef struct {
    uint32 biSize;                      // 位图信息头的大小，为40
    uint32 biWidth;                     // 位图的宽度
    uint32 biHeight;                    // 位图的高度
    uint16 biPlanes;                    // 固定值1
    uint16 biBitCount;                  // 每个像素的位数 1-黑白图 4-16色图 8-256色 24-真彩色
    uint32 biCompression;               // 压缩方式 0-不压缩
    uint32 biSizeImage;                 // 位图全部像素占用的字节数
    uint32 biXPelsPerMeter;             // 水平分辨率
    uint32 biYPelsPerMeter;             // 垂直分辨率
    uint32 biClrUsed;                   // 位图使用的颜色数，如果为0,则颜色数为2的biBitCount次方
    uint32 biClrImportant;              // 重要的颜色数，0代表所有颜色都重要
} INFO_HEADER;


typedef struct {
    FILE_HEADER file_header;            // 位图文件头
    INFO_HEADER info_header;            // 位图信息头
    uchar *image;                       // 图像数据
} bitmap_t;


extern int load_bmp(const char *path, image_t *img);
extern int save_as_bmp(const image_t *img, const char *path);

#endif //TEST_JPEG_BITMAP_H
