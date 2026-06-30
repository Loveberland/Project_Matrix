#include <stdlib.h>
#include <stdio.h>

#include "matrix.h"
#include "display.h"

#define ROWS 5
#define COLS 5

int main(void) {
	puts("\033[0;33m--- Test print_mat function ---\033[0m");
	Matrix *mat = malloc(sizeof(Matrix));
	mat->data = malloc(ROWS * COLS * sizeof(double));
	mat->rows = ROWS;
	mat->cols = COLS;
	for (int i = 0; i < ROWS; i++)
		for (int j = 0; j < COLS; j++)
			mat->data[i * COLS + j] = i * COLS + j;
	print_mat(mat, "Result: \n");

	return (0);
}
