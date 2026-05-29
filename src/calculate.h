#include <stddef.h>

#include "matrix.h"

#ifndef CALCULATE_H
#define CALCULATE_H

int add_mat(Matrix *mat, int n);
int sub_mat(Matrix *mat, int n);
int _add_mat(Matrix *a, const Matrix *b);
int _sub_mat(Matrix *a, const Matrix *b);

#endif
