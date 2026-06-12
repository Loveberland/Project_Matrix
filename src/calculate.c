#include <stdlib.h>

#include "calculate.h"
#include "matrix.h"
#include "display.h"

int add_mat(Matrix *mat, const int n) {
	int status = 0;
	for (int i = 1; i < n; i++) {
		#ifdef _WIN32
			status = _add_mat_w(&mat[0], &mat[i]);
		#else
			status = _add_mat(&mat[0], &mat[i]);	
		#endif
		if (status)
			return status;
	}
	print_mat(&mat[0], "result is:\n");
	return status;
}

int sub_mat(Matrix *mat, const int n) {
	int status = 0;
	for (int i = 1; i < n; i++) {
		#ifdef _WIN32
			status = _sub_mat_w(&mat[0], &mat[i]);
		#else
			status = _sub_mat(&mat[0], &mat[i]);	
		#endif
		if (status)
			return status;
	}
	print_mat(&mat[0], "result is:\n");
	return status;
}

int mul_mat(Matrix *mat, const int n) {
	int status = 0;
	for (int i = 1; i < n; i++) {
		#ifdef _WIN32
			status = _mul_mat_w(&mat[0], &mat[i]);
		#else
			status = _mul_mat(&mat[0], &mat[i]);	
		#endif
		if (status)
			return status;
	}
	print_mat(&mat[0], "result is:\n");
	return status;
}
