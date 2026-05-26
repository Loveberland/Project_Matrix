#include <stdio.h>

#include "input_handler.h"

int main(void) {
	size_t s = get_mat_cnt();
	fprintf(stdout, "get_matrix_cnt(): %zu\n", s);
}
