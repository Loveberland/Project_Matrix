#include "matrix.h"

#ifndef CALCULATE_H
#define CALCULATE_H

int add_mat(Matrix *mat, int n);
int sub_mat(Matrix *mat, int n);
int mul_mat(Matrix *mat, int n);
int det_mat(Matrix *mat);
int _add_mat(Matrix *a, const Matrix *b);
int _sub_mat(Matrix *a, const Matrix *b);
int _mul_mat(Matrix *a, const Matrix *b);
double _det_mat(Matrix *a);
int _add_mat_w(Matrix *a, const Matrix *b);
int _sub_mat_w(Matrix *a, const Matrix *b);
int _mul_mat_w(Matrix *a, const Matrix *b);
double _det_mat_w(Matrix *a);

#endif
