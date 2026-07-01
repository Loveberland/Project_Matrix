#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "input_handler.h"
#include "matrix.h"
#include "calculate.h"
#include "display.h"
#include "choice.h"

void greedy() {
	fprintf(stdout, "--- Welcome to matrix calculator ---\n");
}

void bye() {
	fprintf(stdout, "--- Exit program ---\n");
}

int main(void) {
	greedy();

	int n = get_mat_cnt();	
	Matrix *mat = malloc(n * sizeof(Matrix));
	for (int i = 0; i < n; i++) {
		Matrix *tmp = get_mat(i + 1);
		mat[i] = *tmp;
		free(tmp);	
	}
	int c = calculate_choice();
	double det_answer = NAN;
	if (c == 0) {
		if (add_mat(mat, n)) {
			fprintf(stderr, "Something went wrong, can't addition matrix.\n");
		}
	}else if (c == 1) {
		if (sub_mat(mat, n)) {
			fprintf(stderr, "Something went wrong, can't subtraction matrix.\n");
		}
	}else if (c == 2) {
		if (mul_mat(mat, n)) {
			fprintf(stderr, "Something went wrong, can't multiplication matrix.\n");
		}
	} else if (c == 3) {
		if (det_mat(mat, &det_answer) == NAN) {
			fprintf(stderr, "Something went wrong, can't find determinant.\n");
		}
	} else if (c == 4) {
		if (trans_mat(mat) == -1) {
			fprintf(stderr, "Something went wrong, can't find transpose.\n");
		}
	} else if (c == 5) {
		puts("Coming soon...");
	} else if (c == 6) {
		bye();
		return (0);
	} else {
		fprintf(stderr, "Something went wrong.\n");
	}

	c = output_choice();
	if (c == 0) {
		if (!isnan(det_answer)) {
			print_det(det_answer);
		} else {
			print_mat(&mat[0], "Result: \n");
		}
	} else if (c == 1) {
		puts("Coming soon...");
	} else if (c == 2) {
		bye();
		return (0);
	} else {
		fprintf(stderr, "Something went wrong.\n");
	}

	for (int i = 0; i < n; i++) {
		free(mat[i].data);
	}
	free(mat);

	bye();

	return (0);
}
