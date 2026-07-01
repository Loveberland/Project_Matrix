#include <stdio.h>

#include "matrix.h"
#include "file_handler.h"

void save_mat_to_file(const Matrix *mat) {
    	FILE *output = fopen("output.txt", "w");
    	if (output == NULL) {
        	fprintf(stderr, "Error: File output.txt not found\n");
        	return;
    	}

    	fputs("Result is:\n", output);
    	for (size_t i = 0; i < mat->rows; i++) {
        	for (size_t j = 0; j < mat->cols; j++) {
            		fprintf(output, "%8.8f ", MAT(mat, i, j));
        	}
        	fputs("\n", output);
    	}

    	fclose(output);
}

void save_double_to_file(const double val) {
    	FILE *output = fopen("output.txt", "w");
    	if (output == NULL) {
        	fprintf(stderr, "Error: File output.txt not found\n");
        	return;
    	}

    	fprintf(output, "Result is: %8.8f\n", val);

    	fclose(output);
}

int read_from_file() {
    	FILE *input = fopen("input.txt", "r");
    	if (input == NULL) {
        	fprintf(stderr, "Error: File input.txt not found\n");
        	return (-1);
    	}

    	fclose(input);

	return (0);
}
