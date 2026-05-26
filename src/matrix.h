#include <stddef.h>

#ifndef MATRIX_H
#define MATRIX_H

typedef struct {
	double *data;
	size_t rows;
	size_t cols;
} Matrix;

#define MAT(m, i, j) ((m)->data[(i) * (m)->cols + (j)])

#endif MATRIX_H
