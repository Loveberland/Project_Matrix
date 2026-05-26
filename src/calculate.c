#include <stdlib.h>

#include "matrix.h"

int add_mat(Matrix *mat, size_t n) {
	int status = 0;
	if (n < 2)
		return (1);
	for (int i = 0; i < n - 1; i++) {
		if (mat[i]->rows != mat[i + 1]->rows || mat[i]->cols != mat[i + 1]->cols)
			return (1);
		status = _add_mat(&mat[i], &mat[i + 1]);	
		if (status)
			return status;
	}
	return status;
}
