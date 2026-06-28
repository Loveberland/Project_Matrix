#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "input_handler.h"
#include "matrix.h"
#include "calculate.h"
#include "display.h"
#include "choice.h"

void greedy() {
	fprintf(stdout, "--- welcome to matrix calculator ---\n");
}

void bye() {
	fprintf(stdout, "--- exit program ---\n");
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
	if (c == 0) {
		int add_status = add_mat(mat, n);	
		if (add_status)
			puts("something went wrong, can't addition matrix");
	} else if (c == 1) {
		int sub_status = sub_mat(mat, n);
		if (sub_status)
			puts("something went wrong, can't subtraction matrix");
	} else if (c == 2) {
		int mul_status = mul_mat(mat, n);
		if (mul_status)
			puts("something went wrong, can't multiplication matrix");
	} else if (c == 3) {
		int det_status = det_mat(mat);
		if (det_status == NAN)
			puts("something went wrong, can't find determinant");
	} else if (c == 4) {
		puts("coming soon...");
	} else if (c == 5) {
		puts("coming soon...");
	} else if (c == 6) {	
	} else
		puts("something went wrong");
	for (int i = 0; i < n; i++)
		free(mat[i].data);
	free(mat);
	bye();
}
