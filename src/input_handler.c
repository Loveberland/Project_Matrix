#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>

#include "matrix.h"
#include "input_handler.h"

/*
 * Gets a number from the user.
 * Returns 0 on success, -1 on failure.
 */
int get_num(const char *prompt, int *out) {
	/*
	 * Get a line of input from the user.
	 */
	fprintf(stdout, "%s", prompt);
	char line[16];
	if (fgets(line, sizeof(line), stdin) == NULL) {
		fprintf(stderr, "Error: Failed to read input.\n");
		return (-1);
	}

	/*
	 * Check if the input is a valid integer.
	 */
	const char *p = line;
	if (*p == '-' || *p == '+') {
		p++;
	}
	if (*p == '\0' || *p == '\n') {
		fprintf(stderr, "Error: Invalid input. Please enter number.\n");
		return (-1);
	}
	for (; *p != '\0' && *p != '\n'; p++) {
		if (!isdigit((unsigned char)*p)) {
			fprintf(stderr, "Error: Invalid input. Please enter number.\n");
			return (-1);
		}
	}

	/*
	 * Convert the string to a long integer and check for errors.
	 */
	char *end;
	errno = 0;
	long val = strtol(line, &end, 10);

	if (errno == ERANGE || val < INT_MIN || val > INT_MAX) {
		fprintf(stderr, "Error: Input out of range.\n");
		return (-1);
	}

	/*
	 * Assign the converted value to the output pointer.
	 */
	*out = (int)val;
	return (0);
}

/*
 * Gets the number of matrices the user wants to create.
 * Returns the count on success, recall until valid input is received.
 */
int get_mat_cnt() {
	int cnt;
	if (get_num("\nHow many matrices do you want to create?: ", &cnt) == -1) {
		fprintf(stderr, "Error: Failed to get matrix count.\n");
		return get_mat_cnt(); // Retry on failure
	}
	if (cnt <= 0) {
		fprintf(stderr, "Error: Matrix count must be a positive number.\n");
		return get_mat_cnt(); // Retry on failure
	}
	return cnt;
}

/*
 * Gets the number of rows for a specific matrix.
 * Returns the count on success, recall until valid input is received.
 */
int get_rows(int cnt) {
	int rows;
	char prompt[64];
	snprintf(prompt, sizeof(prompt), "\nHow many rows of matrix %d do you want to create?: ", cnt);
	if (get_num(prompt, &rows) == -1) {
		fprintf(stderr, "Error: Failed to get number of rows.\n");
		return get_rows(cnt); // Retry on failure
	}
	if (rows <= 0) {
		fprintf(stderr, "Error: Number of rows must be a positive number.\n");
		return get_rows(cnt); // Retry on failure
	}
	return rows;
}

/*
 * Gets the number of columns for a specific matrix.
 * Returns the count on success, recall until valid input is received.
 */
int get_cols(int cnt) {
	int cols;
	char prompt[64];
	snprintf(prompt, sizeof(prompt), "\nHow many columns of matrix %d do you want to create?: ", cnt);
	if (get_num(prompt, &cols) == -1) {
		fprintf(stderr, "Error: Failed to get number of columns.\n");
		return get_cols(cnt); // Retry on failure
	}
	if (cols <= 0) {
		fprintf(stderr, "Error: Number of columns must be a positive number.\n");
		return get_cols(cnt); // Retry on failure
	}
	return cols;
}

/*
 * Parses a string into a double.
 * Returns 0 on success, -1 on failure.
 */
int parse_num(const char *s, double *out) {
	/*
	 * Check if the string is valid.
	 */
	if (!s || *s == '\0' || *s == '\n') {
		return (-1);
	}

	/*
	 * Convert the string to a double and check for errors.
	 */
	char *end;
	errno = 0;
	double val = strtod(s, &end);
	
	/*
	 * Check for conversion errors.
	 */
	if (end == s || (*end != '\0' && *end != '\n')) {
		return (-1);
	}
	if (errno == ERANGE) {
		return (-1);
	}

	/*
	 * Assign the converted value to the output pointer.
	 */
	*out = val;
	return (0);
}

/*
 * Gets a matrix from the user.
 * Returns a pointer to the allocated matrix on success, NULL on failure.
 */
Matrix* get_mat(int cnt) {
	int rows = get_rows(cnt);
	int cols = get_cols(cnt);
	Matrix *mat = malloc(sizeof(Matrix));
	if (mat == NULL) {
		fprintf(stderr, "Error: Memory allocation failed for matrix %d.\n", cnt);
		exit(EXIT_FAILURE);
	}
	mat->rows = rows;
	mat->cols = cols;
	mat->data = malloc(rows * cols * sizeof(double));
	if (mat->data == NULL) {
		fprintf(stderr, "Error: Memory allocation failed for matrix data %d.\n", cnt);
		free(mat);
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < rows * cols; i++) {
		char buf[64];
		double val;
		
		while (1) {
			fprintf(stdout, "\n[%d]: ", i + 1);
			if (fgets(buf, sizeof(buf), stdin) == NULL) {
				fprintf(stderr, "Error: Failed to read input\n");
				continue; // Retry on failure
			}
			
			if (parse_num(buf, &val) == -1) {
				fprintf(stderr, "Error: Invalid input. Please enter a valid number.\n");
				continue; // Retry on failure
			}

			break;
		}

		mat->data[i] = val;
	}
	return mat;
}
