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

// bug need another design
double get_number_double(char *txt) {
	int number;
	char s[64];
	while (1) {	
		fputs(txt, stdout);
		fgets(s, sizeof(s), stdin);
		s[strcspn(s, "\n")] = '\0';
		for (char *c = &s[0]; *c != '\0'; c++) {
			if (!isdigit((unsigned char) *c)) {
				fputs("only number\n", stdout);
				exit(1);
			}
		}
		if (check)
			continue;
		number = atoi(s);
		break;
	}

	return number;
}

// bug need another design
Matrix *get_mat(int cnt) {
	fprintf(stdout, "\nMatrix %d:\n", cnt);
	size_t rows = get_rows();
	size_t cols = get_cols();	
	Matrix *mat = malloc(sizeof(Matrix));
	mat->rows = rows;
	mat->cols = cols;
	mat->data = malloc(rows * cols * sizeof(double));	
	while (1) {
		for (int i = 0; i < mat->cols; i++)
			fputs("* ", stdout);
		fputs("<-- this is your columns\n", stdout);

		int valid = 1;
		for (int i = 0; i < mat.rows * mat.cols; i++) {
			char 
			mat->data[i] = get_number_double();
		}
	}
	return mat;
}
