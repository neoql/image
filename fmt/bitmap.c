//
// Created by moons on 17-5-14.
//

#include "bitmap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


image_t * load_bmp(const char *path)
{
    FILE *fp;
    bitmap_t *bmp;
    int x, y;
    uchar *p;
    int line_index;
    color_t color;
    image_t *img;

    fp = fopen(path, "rb");

    bmp = malloc(sizeof(bitmap_t));

    fread(&bmp->file_header.bfType, 2, 1, fp);
    fread(&bmp->file_header.bfSize, 4, 1, fp);
    fread(&bmp->file_header.bfReserved, 4, 1, fp);
    fread(&bmp->file_header.bfOffBits, 4, 1, fp);


    fread(&bmp->info_header.biSize, 4, 1, fp);
    fread(&bmp->info_header.biWidth, 4, 1, fp);
    fread(&bmp->info_header.biHeight, 4, 1, fp);
    fread(&bmp->info_header.biPlanes, 2, 1, fp);
    fread(&bmp->info_header.biBitCount, 2, 1, fp);
    fread(&bmp->info_header.biCompression, 4, 1, fp);
    fread(&bmp->info_header.biSizeImage, 4, 1, fp);
    fread(&bmp->info_header.biXPelsPerMeter, 4, 1, fp);
    fread(&bmp->info_header.biYPelsPerMeter, 4, 1, fp);
    fread(&bmp->info_header.biClrUsed, 4, 1, fp);
    fread(&bmp->info_header.biClrImportant, 4, 1, fp);

    if (bmp->info_header.biSizeImage == 0) {
        bmp->info_header.biSizeImage = bmp->file_header.bfSize - bmp->file_header.bfOffBits;
    }

    bmp->image = calloc(bmp->info_header.biSizeImage, sizeof(uchar));
    fread(bmp->image, 1, bmp->info_header.biSizeImage, fp);
    fclose(fp);

    img = create_empty_img(bmp->info_header.biHeight, bmp->info_header.biWidth);

    for (y = 0; y < img->height; y++) {
        for (x = 0; x < img->width; x++) {
            line_index = (img->width * 3 + img->width % 4) * (img->height - y - 1);
            p = bmp->image + line_index + x * 3;
            color.r = p[2];
            color.g = p[1];
            color.b = p[0];

            img_set_color(img, x, y, color);
        }
    }

    free(bmp->image);
    free(bmp);

    return img;
}


int save_as_bmp(const image_t *img, const char *path)
{
    bitmap_t *bmp;
    color_t color;
    int x, y;
    uchar *p;
    FILE *fp;

    bmp = malloc(sizeof(bitmap_t));

    memcpy(&bmp->file_header.bfType, "BM", 2);
    bmp->file_header.bfReserved = 0;
    bmp->file_header.bfOffBits = 54;

    bmp->info_header.biSize = 40;
    bmp->info_header.biWidth = img->width;
    bmp->info_header.biHeight = img->height;
    bmp->info_header.biPlanes = 1;
    bmp->info_header.biBitCount = 24;
    bmp->info_header.biCompression = 0;
    bmp->info_header.biXPelsPerMeter = 0;
    bmp->info_header.biYPelsPerMeter = 0;
    bmp->info_header.biClrUsed = 0;
    bmp->info_header.biClrImportant = 0;

    bmp->info_header.biSizeImage = (img->width * 3 + img->width % 4) * img->height;
    bmp->file_header.bfSize = 54 + bmp->info_header.biSizeImage;

    bmp->image = calloc(bmp->info_header.biSizeImage, sizeof(uchar));

    p = bmp->image;
    for (y = img->height - 1; y >= 0; y--) {
        for (x = 0; x < img->width; x++) {
            if (img_get_color(img, x, y, &color)) {
                bzero(&color, sizeof(color_t));
            }
            p[2] = color.r;
            p[1] = color.g;
            p[0] = color.b;
            p += 3;
        }
        p += img->width % 4;
    }

    fp = fopen(path, "wb");

    fwrite(&bmp->file_header.bfType, 2, 1, fp);
    fwrite(&bmp->file_header.bfSize, 4, 1, fp);
    fwrite(&bmp->file_header.bfReserved, 4, 1, fp);
    fwrite(&bmp->file_header.bfOffBits, 4, 1, fp);


    fwrite(&bmp->info_header.biSize, 4, 1, fp);
    fwrite(&bmp->info_header.biWidth, 4, 1, fp);
    fwrite(&bmp->info_header.biHeight, 4, 1, fp);
    fwrite(&bmp->info_header.biPlanes, 2, 1, fp);
    fwrite(&bmp->info_header.biBitCount, 2, 1, fp);
    fwrite(&bmp->info_header.biCompression, 4, 1, fp);
    fwrite(&bmp->info_header.biSizeImage, 4, 1, fp);
    fwrite(&bmp->info_header.biXPelsPerMeter, 4, 1, fp);
    fwrite(&bmp->info_header.biYPelsPerMeter, 4, 1, fp);
    fwrite(&bmp->info_header.biClrUsed, 4, 1, fp);
    fwrite(&bmp->info_header.biClrImportant, 4, 1, fp);

    fwrite(bmp->image, 1, bmp->info_header.biSizeImage, fp);

    fclose(fp);
    free(bmp->image);
    free(bmp);

    return 0;
}
