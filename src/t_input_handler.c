#include <stdio.h>

#include "input_handler.h"

#define ANS 2

int main(void) {
	fputs("you need to enter 2\n", stdout);
	size_t s = get_mat_cnt();
	fprintf(stdout, "get_matrix_cnt(): %zu\n", s);
	if (ANS != s)
		return (1);
	return (0);
}
