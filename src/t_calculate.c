#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#include "matrix.h"
#include "calculate.h"

#define EPSILON 1e-9

int status = 0;

void init_mat(Matrix *m, size_t rows, size_t cols, double init_val) {
	if (!m) {
		return;
	}
	m->rows = rows;
	m->cols = cols;
	m->data = malloc(rows * cols * sizeof(double));
	for (size_t i = 0; i < rows * cols; i++)
		m->data[i] = init_val;
}

void free_mat(Matrix *m) {
	if (!m) {
		return;
	}
	free(m->data);
	m->data = NULL;
}

void free_mat_arr(Matrix *arr, size_t n) {
	if (!arr) {
		return;
	}
	for (size_t i = 0; i < n; i++) {
		free_mat(&arr[i]);
	}
	free(arr);
}

int is_mat_equal(const Matrix *m1, const Matrix *m2) {
	if (m1 == NULL || m2 == NULL || m1->rows != m2-> rows || m1->cols != m2->cols) {
		return (0);
	}
	for (size_t i = 0; i < m1->rows; i++) {
		for (size_t j = 0; j < m1->cols; j++) {
			double diff = fabs(MAT(m1, i , j) - MAT(m2, i, j));
			if (diff > EPSILON) {
				return (0);
			}
		}
	}
	return (1);
}

int is_double_equal(const double n1, const double n2) {
	if (n1 == NAN || n2 == NAN) { 
		return (0);
	}
	double diff = fabs(n1 - n2);
	if (diff > EPSILON) {
		return (0);
	}
	return (1);
}

void t_add_mat() {
	puts("\033[0;33mtest add_mat function\033[0m");
	puts("test 1:");
	Matrix *m1 = malloc(2 * sizeof(Matrix));
	init_mat(&m1[0], 3, 3, 0.33);
	init_mat(&m1[1], 3, 3, 0.34);
	status = add_mat(m1, 2);
	assert(!status);
	Matrix *ans1 = malloc(sizeof(Matrix));
	init_mat(ans1, 3, 3, 0.67);
	assert(is_mat_equal(ans1, &m1[0]));
	free_mat_arr(m1, 2);
	free_mat(ans1);

	puts("test 2:");
	Matrix *m2 = malloc(3 * sizeof(Matrix));
	init_mat(&m2[0], 3, 3, 0.00015);
	init_mat(&m2[1], 3, 3, 0.00012);
	init_mat(&m2[2], 3, 3, 0.00040);
	status = add_mat(m2, 3);
	assert(!status);
	Matrix *ans2 = malloc(sizeof(Matrix));
	init_mat(ans2, 3, 3, 0.00067);
	assert(is_mat_equal(ans2, &m2[0]));
	free_mat_arr(m2, 3);
	free_mat(ans2);

	puts("test 3:");
	Matrix *m3 = malloc(5 * sizeof(Matrix));
	init_mat(&m3[0], 3, 3, 0.00000012);
	init_mat(&m3[1], 3, 3, 0.00000002);
	init_mat(&m3[2], 3, 3, 0.00000040);
	init_mat(&m3[3], 3, 3, 0.00000010);
	init_mat(&m3[4], 3, 3, 0.00000003);
	status = add_mat(m3, 5);
	assert(!status);
	Matrix *ans3 = malloc(sizeof(Matrix));
	init_mat(ans3, 3, 3, 0.00000067);
	assert(is_mat_equal(ans3, &m3[0]));
	free_mat_arr(m3, 5);
	free_mat(ans3);


	puts("test 4:");
	Matrix *m4 = malloc(3 * sizeof(Matrix));
	init_mat(&m4[0], 5, 5, 12345.54321);
	init_mat(&m4[1], 5, 5, 30000.00003);
	init_mat(&m4[2], 5, 5, 00003.30000);
	status = add_mat(m4, 3);
	assert(!status);
	Matrix *ans4 = malloc(sizeof(Matrix));
	init_mat(ans4, 5, 5, 42348.84324);
	assert(is_mat_equal(ans4, &m4[0]));
	free_mat_arr(m4, 3);
	free_mat(ans4);

	puts("test 5:");
	Matrix *m5 = malloc(5 * sizeof(Matrix));
	init_mat(&m5[0], 5, 5, 0.0);
	init_mat(&m5[1], 5, 5, 0.0);
	init_mat(&m5[2], 5, 5, 0.0);
	init_mat(&m5[3], 5, 5, 0.0);
	init_mat(&m5[4], 5, 5, 0.0);
	status = add_mat(m5, 5);
	assert(!status);
	Matrix *ans5 = malloc(sizeof(Matrix));
	init_mat(ans5, 5, 5, 0.0);
	assert(is_mat_equal(ans5, &m5[0]));
	free_mat_arr(m5, 5);
	free_mat(ans5);
}

void t_sub_mat() {
	puts("\033[0;33mtest sub_mat function\033[0m");
	puts("test 1:");
	Matrix *m1 = malloc(2 * sizeof(Matrix));
	init_mat(&m1[0], 3, 3, 0.33);
	init_mat(&m1[1], 3, 3, 0.34);
	status = sub_mat(m1, 2);
	assert(!status);
	Matrix *ans1 = malloc(sizeof(Matrix));
	init_mat(ans1, 3, 3, -0.01);
	assert(is_mat_equal(ans1, &m1[0]));
	free_mat_arr(m1, 2);
	free_mat(ans1);

	puts("test 2:");
	Matrix *m2 = malloc(3 * sizeof(Matrix));
	init_mat(&m2[0], 3, 3, 0.00015);
	init_mat(&m2[1], 3, 3, 0.00012);
	init_mat(&m2[2], 3, 3, 0.00040);
	status = sub_mat(m2, 3);
	assert(!status);
	Matrix *ans2 = malloc(sizeof(Matrix));
	init_mat(ans2, 3, 3, -0.00037);
	assert(is_mat_equal(ans2, &m2[0]));
	free_mat_arr(m2, 3);
	free_mat(ans2);

	puts("test 3:");
	Matrix *m3 = malloc(5 * sizeof(Matrix));
	init_mat(&m3[0], 3, 3, 0.00000012);
	init_mat(&m3[1], 3, 3, 0.00000002);
	init_mat(&m3[2], 3, 3, 0.00000040);
	init_mat(&m3[3], 3, 3, 0.00000010);
	init_mat(&m3[4], 3, 3, 0.00000003);
	status = sub_mat(m3, 5);
	assert(!status);
	Matrix *ans3 = malloc(sizeof(Matrix));
	init_mat(ans3, 3, 3, -0.00000043);
	assert(is_mat_equal(ans3, &m3[0]));
	free_mat_arr(m3, 5);
	free_mat(ans3);


	puts("test 4:");
	Matrix *m4 = malloc(3 * sizeof(Matrix));
	init_mat(&m4[0], 5, 5, 12345.54321);
	init_mat(&m4[1], 5, 5, 30000.00003);
	init_mat(&m4[2], 5, 5, 00003.30000);
	status = sub_mat(m4, 3);
	assert(!status);
	Matrix *ans4 = malloc(sizeof(Matrix));
	init_mat(ans4, 5, 5, -17657.75682);
	assert(is_mat_equal(ans4, &m4[0]));
	free_mat_arr(m4, 3);
	free_mat(ans4);

	puts("test 5:");
	Matrix *m5 = malloc(5 * sizeof(Matrix));
	init_mat(&m5[0], 5, 5, 0.0);
	init_mat(&m5[1], 5, 5, 0.0);
	init_mat(&m5[2], 5, 5, 0.0);
	init_mat(&m5[3], 5, 5, 0.0);
	init_mat(&m5[4], 5, 5, 0.0);
	status = sub_mat(m5, 5);
	assert(!status);
	Matrix *ans5 = malloc(sizeof(Matrix));
	init_mat(ans5, 5, 5, 0.0);
	assert(is_mat_equal(ans5, &m5[0]));
	free_mat_arr(m5, 5);
	free_mat(ans5);

}

void t_mul_mat() {
	puts("\033[0;33mtest mul_mat function\033[0m");
	puts("test 1:");
	Matrix *m1 = malloc(3 * sizeof(Matrix));
	init_mat(&m1[0], 3, 3, 9.0);
	init_mat(&m1[1], 3, 3, 12.0);
	init_mat(&m1[2], 3, 3, 20.0);
	status = mul_mat(m1, 3);
	assert(!status);
	Matrix *ans1 = malloc(sizeof(Matrix));
	init_mat(ans1, 3, 3, 19440.0);
	assert(is_mat_equal(ans1, &m1[0]));
	free_mat_arr(m1, 3);
	free_mat(ans1);

	puts("test 2:");
	Matrix *m2 = malloc(2 * sizeof(Matrix));
	init_mat(&m2[0], 3, 3, 9.0);
	init_mat(&m2[1], 3, 3, 12.0);
	status = mul_mat(m2, 2);
	assert(!status);
	Matrix *ans2 = malloc(sizeof(Matrix));
	init_mat(ans2, 3, 3, 324.0);
	assert(is_mat_equal(ans2, &m2[0]));
	free_mat_arr(m2, 2);
	free_mat(ans2);

	puts("test 3:");
	Matrix *m3 = malloc(sizeof(Matrix));
	init_mat(&m3[0], 3, 3, 9.0);
	status = mul_mat(m3, 1);
	assert(!status);
	Matrix *ans3 = malloc(sizeof(Matrix));
	init_mat(ans3, 3, 3, 9.0);
	assert(is_mat_equal(ans3, &m3[0]));
	free_mat_arr(m3, 1);
	free_mat(ans3);

	puts("test 4:");
	Matrix *m4 = malloc(5 * sizeof(Matrix));
	init_mat(&m4[0], 2, 2, 0.2);
	init_mat(&m4[1], 2, 2, 0.2);
	init_mat(&m4[2], 2, 2, 0.2);
	init_mat(&m4[3], 2, 2, 0.2);
	init_mat(&m4[4], 2, 2, 0.2);
	status = mul_mat(m4, 5);
	assert(!status);
	Matrix *ans4 = malloc(sizeof(Matrix));
	init_mat(ans4, 2, 2, 0.00512);
	assert(is_mat_equal(ans4, &m4[0]));
	free_mat_arr(m4, 5);
	free_mat(ans4);

	puts("test 5:");
	Matrix *m5 = malloc(3 * sizeof(Matrix));
	init_mat(&m5[0], 3, 2, 1.1);
	init_mat(&m5[1], 2, 3, 2.2);
	init_mat(&m5[2], 3, 2, 3.3);
	status = mul_mat(m5, 3);
	assert(!status);
	Matrix *ans5 = malloc(sizeof(Matrix));
	init_mat(ans5, 3, 2, 47.916);
	assert(is_mat_equal(ans5, &m5[0]));
	free_mat_arr(m5, 3);
	free_mat(ans5);
}

double result;

void t_det_mat() {
	double answer = NAN;
	puts("\033[0;33mtest det_mat function\033[0m");
	puts("test 1:");
	Matrix *m1 = malloc(sizeof(Matrix));
	init_mat(m1, 2, 2, 0.0);
	m1->data[0] = 6.7;
	m1->data[1] = 67;
	m1->data[2] = 670;
	m1->data[3] = -67;
	result = det_mat(m1, &answer);
	if (result == NAN || !is_double_equal(answer, -45338.9)) {
		fprintf(stderr, "test 1: failed");
		abort();
	}
	free_mat(m1);

	puts("test 2:");
	Matrix *m2 = malloc(sizeof(Matrix));
	init_mat(m2, 2, 2, 0.0);
	m2->data[0] = 2;
	m2->data[1] = 4;
	m2->data[2] = 6;
	m2->data[3] = 8;
	result = det_mat(m2, &answer);
	if (result == NAN || !is_double_equal(answer, -8)) {
		fprintf(stderr, "test 2: failed");
		abort();
	}
	free_mat(m2);

	puts("test 3:");
	Matrix *m3 = malloc(sizeof(Matrix));
	init_mat(m3, 4, 4, 0.0);
	m3->data[0] = 6.7;
	m3->data[2] = -7.6;
	m3->data[5] = -6.7;
	m3->data[10] = 7.6;
	m3->data[12] = 0.67;
	m3->data[15] = 1.0;
	result = det_mat(m3, &answer);
	if (result == NAN || !is_double_equal(answer, -341.164)) {
		fprintf(stderr, "test 3: failed");
		abort();
	}
	free_mat(m3);

	puts("test 4:");
	Matrix *m4 = malloc(sizeof(Matrix));
	init_mat(m4, 3, 3, 3.3);
	m4->data[2] = 1.0;
	m4->data[4] = 1.0;
	m4->data[6] = 1.0;
	m4->data[8] = 1.0;
	result = det_mat(m4, &answer);
	if (result == NAN || !is_double_equal(answer, -22.747)) {
		fprintf(stderr, "test 4: failed");
		abort();
	}
	free_mat(m4);

	puts("test 5:");
	Matrix *m5 = malloc(sizeof(Matrix));
	init_mat(m5, 3, 3, 0.0);
	m5->data[0] = 2;
	m5->data[1] = 0.1;
	m5->data[2] = 45;
	m5->data[3] = 4;
	m5->data[4] = 67;
	m5->data[5] = 11;
	m5->data[6] = 6;
	m5->data[7] = 23;
	m5->data[8] = 22;
	result = det_mat(m5, &answer);
	if (result == NAN || !is_double_equal(answer, -11510.2)) {
		fprintf(stderr, "test 5: failed");
		abort();
	}
	free_mat(m5);
}

int main(void) {
	t_add_mat();
	t_sub_mat();
	t_mul_mat();
	t_det_mat();
	return (0);
}
