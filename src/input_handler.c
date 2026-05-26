#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "input_handler.h"

size_t get_number(char *txt) {
	size_t number;
	char s[64];
	while (1) {	
		fputs(txt, stdout);
		fgets(s, sizeof(s), stdin);
		s[strcspn(s, "\n")] = '\0';
		int check = 0;
		for (char *c = &s[0]; *c != '\0'; c++) {
			if (!isdigit((unsigned char) *c)) {
				fputs("only number\n", stdout);
				check =  1;
				break;	
			}
		}
		if (check)
			continue;
		number = atoi(s);
		break;
	}

	return number;
}

size_t get_mat_cnt() {
	return get_number("how many count of matrix: ");
}

size_t get_rows() {
	return get_number("enter rows of matrix: ");
}

size_t get_cols() {
	return get_number("enter columns of matrix: ");
}

Matrix *get_mat(int cnt) {
	fprintf(stdout, "\nMatrix %d:\n", cnt);
	size_t rows = get_rows();
	size_t cols = get_cols();	
	Matrix *mat = malloc(sizeof(Matrix));
	mat->rows = rows;
	mat->cols = cols;
	mat->data = malloc(rows * cols * sizeof(double));	

	return mat;
}
