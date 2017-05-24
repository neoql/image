//
// Created by moons on 17-5-22.
//

#ifndef IMAGE_JPEG_H
#define IMAGE_JPEG_H

#include "image.h"
#include "bitstring.h"

#define SOI     0xFFD8                  // 图像开始
#define APP0    0xFFE0                  // 应用程序保留标记0
#define DQT     0xFFDB                  // 定义量化表
#define SOF0    0xFFC0                  // 帧图像开始
#define DHT     0xFFC4                  // 定义Huffman表
#define DRI     0xFFDD                  // 定义差分编码累计复位的间隔
#define SOS     0xFFDA                  // 扫描开始
#define EOI     0xFFD9                  // 图像结束

typedef struct {
    uchar cc_id;                        // 颜色分量ID
    uchar h_sampling_factor;            // 水平采样因子
    uchar v_sampling_factor;            // 垂直采样因子
    uchar qt_id;                        // 当前分量使用的量化表的ID
    uchar dc_huffman_tab;               // 直流分量使用的哈夫曼表编号
    uchar ac_huffman_tab;               // 交流分量使用的哈夫曼表编号
} color_component_t;


typedef struct {
    uchar id;                           // 表ID
    uchar kind;                         // 表类型 0:DC直流 1:AC交流
    uchar total[16];                    // 不同位数的码字数量
    uchar *value;                       // 编码内容,每个叶子节点的权重
    uint16 first[16];                   // 各个长度的码字的第一个码字的整数值
    uint16 index[16];                   // 各个长度码字的第一个码字的索引
} huffman_table_t;


typedef struct {
    uint16 quantization_tab[4][64];     // 量化表
    uint16 height;                      // 图像高度
    uint16 width;                       // 图像宽度
    uchar  cc_total;                    // 颜色分量数 1:灰度图 3:YCrCb 4:CMYK
    color_component_t cc[4];            // 颜色分量
    huffman_table_t huffman_tab[4];     // 哈夫曼表
    bitstring_t content;                // 图像内容
} jpeg_t;

extern int load_jpeg(const char *path, image_t *img);
extern int save_as_jpeg(const image_t *img, const char *path);

#endif //IMAGE_JPEG_H
