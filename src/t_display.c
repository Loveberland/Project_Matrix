#include <stdlib.h>

#include "matrix.h"
#include "display.h"

#define ROWS 5
#define COLS 5

int main(void) {
	Matrix *mat = malloc(sizeof(Matrix));
	mat->data = malloc(ROWS * COLS * sizeof(double));
	mat->rows = ROWS;
	mat->cols = COLS;
	for (int i = 0; i < ROWS; i++)
		for (int j = 0; j < COLS; j++)
			mat->data[i * COLS + j] = i * COLS + j;
	print_mat(mat);

	return (0);
}
