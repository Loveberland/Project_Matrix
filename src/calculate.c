#include <stdlib.h>

#include "calculate.h"
#include "matrix.h"
#include "display.h"

int add_mat(Matrix *mat, int n) {
	int status = 0;
	if (n < 2)
		return (1);
	for (int i = 1; i < n; i++) {
		if (mat[0].rows != mat[i].rows || mat[0].cols != mat[i].cols)
			return (1);
		status = _add_mat(&mat[0], &mat[i]);	
		if (status)
			return status;
	}
	print_mat(&mat[0]);
	return status;
}
