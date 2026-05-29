#include <stdio.h>
#include <stdlib.h>

#include "input_handler.h"
#include "matrix.h"
#include "calculate.h"
#include "display.h"

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
	int add_status = add_mat(mat, n);	
	if (add_status)
		puts("Something went wrong, can't add matrix");

	int sub_status = sub_mat(mat, n);
	if (sub_status)
		puts("Something went wrong, can't sub matrix");

	for (int i = 0; i < n; i++)
		free(mat[i].data);
	free(mat);
	bye();
}
