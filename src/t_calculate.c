#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "matrix.h"
#include "calculate.h"
#include "display.h"

#define ROWS 2
#define COLS 2

int t_add_mat() {
	puts("\033[0;33mtest add_mat function\033[0m");
	puts("matrix count is 3");
	puts("matrix size is 2x2");
	Matrix *mat = malloc(3 * sizeof(Matrix));
	for (int i = 0; i < 3; i++) {
		mat[i].data = malloc(ROWS * COLS * sizeof(double));
		mat[i].rows = ROWS;
		mat[i].cols = COLS;
	}
	for (int i = 0; i < 4; i++)
		mat[0].data[i] = i + 1;
	print_mat(&mat[0], "matrix 1:\n");

	for (int i = 0; i < 4; i++)
		mat[1].data[i] = 1;
	print_mat(&mat[1], "matrix 2:\n");

	for (int i = 0; i < 4; i++)
		mat[2].data[i] = (i + 1) * 2;
	print_mat(&mat[2], "matrix 3:\n");

	int status = add_mat(mat, 3);
	if (mat[0].data[0] != 4)
		status = 1;
	if (mat[0].data[1] != 7)
		status = 1;
	if (mat[0].data[2] != 10)
		status = 1;
	if (mat[0].data[3] != 13)
		status = 1;
	if (status)
		puts("wrong answer");

	return status;
}

int t_sub_mat() {
	puts("\n\033[0;33mtest sub_mat function\033[0m");
	puts("matrix count is 3");
	puts("matrix size is 2x2");
	Matrix *mat = malloc(3 * sizeof(Matrix));
	for (int i = 0; i < 3; i++) {
		mat[i].data = malloc(ROWS * COLS * sizeof(double));
		mat[i].rows = ROWS;
		mat[i].cols = COLS;
	}
	for (int i = 0; i < 4; i++)
		mat[0].data[i] = i + 1;
	print_mat(&mat[0], "matrix 1:\n");

	for (int i = 0; i < 4; i++)
		mat[1].data[i] = 1;
	print_mat(&mat[1], "matrix 2:\n");

	for (int i = 0; i < 4; i++)
		mat[2].data[i] = (i + 1) * 2;
	print_mat(&mat[2], "matrix 3:\n");

	int status = sub_mat(mat, 3);
	if (mat[0].data[0] != -2)
		status = 1;
	if (mat[0].data[1] != -3)
		status = 1;
	if (mat[0].data[2] != -4)
		status = 1;
	if (mat[0].data[3] != -5)
		status = 1;

	if (status)
		puts("wrong answer");
	return status;
}

int t_mul_mat() {
	puts("\n\033[0;33mtest mul_mat function\033[0m");
	puts("matrix count is 3");
	puts("matrix size is 2x2");
	Matrix *mat = malloc(3 * sizeof(Matrix));
	for (int i = 0; i < 3; i++) {
		mat[i].data = malloc(ROWS * COLS * sizeof(double));
		mat[i].rows = ROWS;
		mat[i].cols = COLS;
	}
	for (int i = 0; i < 4; i++)
		mat[0].data[i] = i + 1;
	print_mat(&mat[0], "matrix 1:\n");

	for (int i = 0; i < 4; i++)
		mat[1].data[i] = 1;
	print_mat(&mat[1], "matrix 2:\n");

	for (int i = 0; i < 4; i++)
		mat[2].data[i] = (i + 1) * 2;
	print_mat(&mat[2], "matrix 3:\n");

	int status = mul_mat(mat, 3);	
	if (mat[0].data[0] != 24)
		status = 1;
	if (mat[0].data[1] != 36)
		status = 1;
	if (mat[0].data[2] != 56)
		status = 1;
	if (mat[0].data[3] != 84)
		status = 1;

	if (status)
		puts("wrong answer");
	return status;
}

int t_det_mat() {
	puts("\n\033[0;33mtest det_mat function\033[0m");
	puts("matrix count is 1");
	puts("matrix size is 3x3");
	Matrix *mat = malloc(1 * sizeof(Matrix));
	mat->data = malloc(3 * 3 * sizeof(double));
	mat->rows = 3;
	mat->cols = 3;
	for (int i = 0; i < 9; i++)
		mat->data[i] = (i + 1) * 2;
	print_mat(mat, "matrix 1:\n");
	int result = det_mat(mat);
	if (result == 0)
		return (-1);

	if (result == NAN)
		puts("wrong answer");
	return (0);
}

int main(void) {
	int status;
	status = t_add_mat();
	if (status)
		return status;

	status = t_sub_mat();
	if (status)
		return status;

	status = t_mul_mat();
	if (status)
		return status;

	status = t_det_mat();
	if (status)
		return status;
	return status;
}
