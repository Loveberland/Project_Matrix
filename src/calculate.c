#include <stdlib.h>

#include "calculate.h"
#include "matrix.h"
#include "display.h"

int add_mat(Matrix *mat, const int n) {
	int status = 0;
	for (int i = 1; i < n; i++) {
		status = _add_mat(&mat[0], &mat[i]);	
		if (status)
			return status;
	}
	print_mat(&mat[0], "result is:\n");
	return status;
}

int sub_mat(Matrix *mat, const int n) {
	int status = 0;
	for (int i = 1; i < n; i++) {
		status = _sub_mat(&mat[0], &mat[i]);	
		if (status)
			return status;
	}
	print_mat(&mat[0], "result is:\n");
	return status;
}
