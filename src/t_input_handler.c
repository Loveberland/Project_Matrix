#include <stdio.h>
#include <stdlib.h>

#include "input_handler.h"
#include "matrix.h"

#define ROWS 3
#define COLS 3
#define CNT_ANS 2

int t_get_mat_cnt() {
	puts("\033[0;33m--- Test get_mat_cnt function ---\033[0m");
	fputs("You need to enter: 2\n", stdout);
	size_t s = get_mat_cnt();
	fprintf(stdout, "get_matrix_cnt(): %zu\n", s);
	if (CNT_ANS != s)
		return (1);
	return (0);
}

int t_get_mat() {
	puts("\n\033[0;33m--- Test_get_mat function ---\033[0m");
	int status = 0;
	fputs("\nMatrix size is: 3x3\n", stdout);
	fputs("You need to enter: 1 - 9\n", stdout); 
	Matrix *mat = get_mat(1);
	if (mat->rows != ROWS) {
		fputs("Result: Rows not equal\n", stdout);
		status = 1;
	}
	if (mat->cols != COLS) {
		fputs("Result: Columns not equal\n", stdout);
		status = 1;
	}
	for (int i = 0; i < 9; i++) {
		if (mat->data[i] != i + 1) {
			fputs("Result: Data not equal\n", stdout);
			status = 1;
			break;
		}
	}
	return status;
}

int main(void) {
	int status = 0;
	status = t_get_mat_cnt();
	if (status)
		return status;
	status = t_get_mat();
	if (status)
		return status;
	return (0);
}
