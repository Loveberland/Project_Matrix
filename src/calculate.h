#include "matrix.h"

#ifndef CALCULATE_H
#define CALCULATE_H

/*
 * Return status of function
 */
int add_mat(Matrix *mat, int n);
int sub_mat(Matrix *mat, int n);
int mul_mat(Matrix *mat, int n);
int det_mat(const Matrix *mat, double *ans);
int trans_mat(Matrix *mat);
int _add_mat(Matrix *a, const Matrix *b);
int _sub_mat(Matrix *a, const Matrix *b);
int _mul_mat(Matrix *a, const Matrix *b);
int _trans_mat(Matrix *mat);
/*
 * Return value of determinant
 */
double _det_mat(const Matrix *a);
/*
 * Return status of function
 */
int _add_mat_w(Matrix *a, const Matrix *b);
int _sub_mat_w(Matrix *a, const Matrix *b);
int _mul_mat_w(Matrix *a, const Matrix *b);
int _trans_mat_w(Matrix *mat);
/*
 * Return value of determinant
 */
double _det_mat_w(const Matrix *mat);

#endif
