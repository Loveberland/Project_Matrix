#include <stdio.h>

#include "display.h"

void print_mat(const Matrix *m, const char *s) {
	fputs(s, stdout);
	for (size_t i = 0; i < m->rows; i++) {
		for (size_t j = 0; j < m->cols; j++)
			fprintf(stdout, "%8.8f ", MAT(m, i, j));
		putchar('\n');
	}
}

void print_det(const double result) {
	fprintf(stdout, "Result: %8.8f\n", result);
}
