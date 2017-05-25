//
// Created by moons on 17-5-22.
//

#include "jpeg.h"
#include "mcu.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define H4BIT(x) ((uchar) ((x & 0xF0) >> 4))
#define L4BIT(x) ((uchar) (x & 0x0F))


uint16 read_uint16(FILE *fp)
{
    uint16 tmp;

    fread(&tmp, 2, 1, fp);
    tmp = htobe16(tmp);
    return tmp;
}


void read_app0(FILE *fp, jpeg_t *jpeg)
{
    uint16 len;

    len = read_uint16(fp);

    fseek(fp, len - sizeof(uint16), SEEK_CUR);
}


void read_other(FILE *fp, jpeg_t *jpeg)
{
    uint16 len;

    len = read_uint16(fp);

    fseek(fp, len - sizeof(uint16), SEEK_CUR);
}


void read_dqt(FILE *fp, jpeg_t *jpeg)
{
    uint16 len, index = 0;
    uchar tmp;
    int size, i, id;

    len = read_uint16(fp);
    index += 2;

    while (len - index) {
        fread(&tmp, 1, 1, fp);
        index += 1;
        size = H4BIT(tmp) + 1;
        id = L4BIT(tmp);

        for (i = 0; i < 64; i++) {
            jpeg->quantization_tab[id][i] = 0;
            fread(&jpeg->quantization_tab[id][i], (size_t) size, 1, fp);
            index += size;
        }
    }
}


void read_sof0(FILE *fp, jpeg_t *jpeg)
{
    uint16 len;
    uchar precision, tmp;
    int i;

    len = read_uint16(fp);
    fread(&precision, 1, 1, fp);
    jpeg->height = read_uint16(fp);
    jpeg->width = read_uint16(fp);
    fread(&jpeg->cc_total, 1, 1, fp);

    for (i = 0; i < jpeg->cc_total; i++) {
        fread(&jpeg->cc[i].cc_id, 1, 1, fp);
        fread(&tmp, 1, 1, fp);
        jpeg->cc[i].h_sampling_factor = H4BIT(tmp);
        jpeg->cc[i].v_sampling_factor = L4BIT(tmp);
        fread(&jpeg->cc[i].qt_id, 1, 1, fp);
    }
}


void read_dht(FILE *fp, jpeg_t *jpeg)
{
    uint16 len, index = 0;
    uchar tmp, id, kind;
    int i, no;
    size_t total = 0;

    len = read_uint16(fp);
    index += 2;

    while (len - index) {
        fread(&tmp, 1, 1, fp);
        index += 1;
        kind = H4BIT(tmp);
        id = L4BIT(tmp);

        no = kind * 2 + id;
        jpeg->huffman_tab[no].id = id;
        jpeg->huffman_tab[no].kind = kind;

        fread(jpeg->huffman_tab[no].total, 1, 16, fp);
        index += 16;

        for (i = 0; i < 16; i++) {
            total += jpeg->huffman_tab[no].total[i];
        }

        jpeg->huffman_tab[no].value = calloc(total, sizeof(uchar));
        fread(jpeg->huffman_tab[no].value, 1, total, fp);
        index += total;
    }
}


void read_sos(FILE *fp, jpeg_t *jpeg)
{
    uint16 len;
    uchar total, i, tmp, index;

    len = read_uint16(fp);
    fread(&total, 1, 1, fp);

    for (i = 0; i < total; i++) {
        fread(&index, 1, 1, fp);
        fread(&tmp, 1, 1, fp);
        jpeg->cc[index - 1].dc_huffman_tab = H4BIT(tmp);
        jpeg->cc[index - 1].ac_huffman_tab = L4BIT(tmp);
    }

    fread(&tmp, 1, 1, fp);
    fread(&tmp, 1, 1, fp);
    fread(&tmp, 1, 1, fp);
}


void read_info(FILE *fp, jpeg_t *jpeg)
{
    uint16 sign;
    uchar tmp;

    bitstring_init(&jpeg->content);

    while (1) {
        fread(&tmp, 1, 1, fp);

        if (tmp != 0xFF) {
            bitstring_append_byte(&jpeg->content, tmp);
            continue;
        }

        while (tmp == 0xFF) {
            fread(&tmp, 1, 1, fp);
        }

        sign = (uint16) (0xFF00 | tmp);
        switch (sign) {
            case SOI:
                break;
            case APP0:
                read_app0(fp, jpeg);
                break;
            case DQT:
                read_dqt(fp, jpeg);
                break;
            case SOF0:
                read_sof0(fp, jpeg);
                break;
            case DHT:
                read_dht(fp, jpeg);
                break;
            case DRI:
                read_other(fp, jpeg);
                break;
            case SOS:
                read_sos(fp, jpeg);
                break;
            case EOI:
                return;
            case 0xFF00:
                bitstring_append_byte(&jpeg->content, 0xFF);
                break;
            default:
                read_other(fp, jpeg);
                break;
        }
    }
}


void build_huffman_tab(huffman_table_t *tab)
{
    uchar i;
    uint16 first = 0, index = 0;

    bzero(tab->first, sizeof(uint16) * 16);
    bzero(tab->index, sizeof(uint16) * 16);
    tab->max_len = 0;
    for (i = 0; i < 16; i++) {
        tab->index[i] = index;
        index += tab->total[i];

        tab->first[i] = first;
        first = (first + tab->total[i]) << 1;

        if (tab->total[i] != 0) {
            tab->max_len = i;
        }
    }
}


uchar decode_next(bitstring_t *str, huffman_table_t *tab)
{
    int len = -1;
    uint16 code = 0;
    uint16 index;

    do {
        if (len == tab->max_len) {
            goto END;
        }

        do {
            code <<= 1;
            code |= bitstring_pop_bit(str);
        } while (tab->total[++len] == 0);
    } while (code >= tab->first[len]);

    do {
        code >>= 1;
        str->__head--;
    } while (tab->total[--len] == 0);

    END:

    index = tab->index[len] + (code - tab->first[len]);

    return tab->value[index];
}


int16 value_of(bit_t bits[], uchar len)
{
    int16 v = 0;
    int i;

    if (bits[0] == 0) {
        for (i = 0; i < len; i++) {
            v <<= 1;
            v |= (!bits[i]);
        }
        v = -v;
    } else {
        for (i = 0; i < len; i++) {
            v <<= 1;
            v |= bits[i];
        }
    }

    return v;
}


void parse_color_component(int16 cc[], bitstring_t *str, huffman_table_t *dc, huffman_table_t *ac)
{
    bit_t buf[16];
    uchar len, v, off;
    int i;

    bzero(cc, sizeof(int16) * 64);
    len = decode_next(str, dc);
    bitstring_pop_bits(str, buf, len);
    cc[0] = value_of(buf, len);

    for (i = 1; i < 64; i++) {
        v = decode_next(str, ac);

        if (v == 0) break;

        off = H4BIT(v);
        len = L4BIT(v);

        i += off;

        bitstring_pop_bits(str, buf, len);
        cc[i] = value_of(buf, len);
    }
}


void parse_jpeg(jpeg_t *jpeg, image_t *img)
{
    int i;
    huffman_table_t *dc, *ac;
    mcu_t *mcus;
    uint32 total_of_mcus;

    img_init(img, jpeg->height, jpeg->width);
    total_of_mcus = img->height * img->width / 64;
    mcus = calloc(total_of_mcus, sizeof(mcu_t));

    for (i = 0; i < 4; i++) {
        build_huffman_tab(&jpeg->huffman_tab[i]);
    }

    for (i = 0; i < total_of_mcus; i++) {
        dc = &jpeg->huffman_tab[jpeg->cc[0].dc_huffman_tab];
        ac = &jpeg->huffman_tab[jpeg->cc[0].ac_huffman_tab + 2];
        parse_color_component(mcus[i].Y, &jpeg->content, dc, ac);

        dc = &jpeg->huffman_tab[jpeg->cc[1].dc_huffman_tab];
        ac = &jpeg->huffman_tab[jpeg->cc[1].ac_huffman_tab + 2];
        parse_color_component(mcus[i].Cb, &jpeg->content, dc, ac);

        dc = &jpeg->huffman_tab[jpeg->cc[2].dc_huffman_tab];
        ac = &jpeg->huffman_tab[jpeg->cc[2].ac_huffman_tab + 2];
        parse_color_component(mcus[i].Cr, &jpeg->content, dc, ac);
    }

    for (i = 1; i < total_of_mcus; i++) {
        mcus[i].Y[0]  += mcus[i - 1].Y[0];
        mcus[i].Cr[0] += mcus[i - 1].Cr[0];
        mcus[i].Cb[0] += mcus[i - 1].Cb[0];
    }

    for (i = 0; i < total_of_mcus; i++) {
        reverse_quantization(mcus[i].Y, jpeg->quantization_tab[jpeg->cc[0].qt_id]);
        reverse_quantization(mcus[i].Cr, jpeg->quantization_tab[jpeg->cc[1].qt_id]);
        reverse_quantization(mcus[i].Cb, jpeg->quantization_tab[jpeg->cc[2].qt_id]);
    }

    for (i = 0; i < total_of_mcus; i++) {
        reverse_zig_zag(mcus[i].Y);
        reverse_zig_zag(mcus[i].Cr);
        reverse_zig_zag(mcus[i].Cb);
    }

    for (i = 0; i < total_of_mcus; i++) {
        minus_correct(mcus[i].Y);
        minus_correct(mcus[i].Cr);
        minus_correct(mcus[i].Cb);
    }

    for (i = 0; i < total_of_mcus; i++) {
        idct(mcus[i].Y);
        idct(mcus[i].Cr);
        idct(mcus[i].Cb);
    }

    mkimg(mcus, img);
    free(mcus);
}


int load_jpeg(const char *path, image_t *img)
{
    FILE *fp;
    jpeg_t jpeg;

    fp = fopen(path, "rb");
    read_info(fp, &jpeg);
    fclose(fp);

    parse_jpeg(&jpeg, img);
    bitstring_destroy(&jpeg.content);

    return 0;
}
