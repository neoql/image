//
// Created by moons on 17-5-12.
//

#ifndef MAT_MAT_H
#define MAT_MAT_H


typedef unsigned int uint32;

typedef struct {
    uint32 width;
    uint32 height;
    double **content;
} mat_t;


extern mat_t * create_mat(uint32 height, uint32 width);
extern void mat_destroy(mat_t *mat);
extern void mat_print(mat_t *mat);
extern mat_t * mat_transposition(mat_t *mat);
extern mat_t * mat_multiply(mat_t *a, mat_t *b);

#endif //MAT_MAT_H
