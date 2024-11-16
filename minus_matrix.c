#include <stdio.h>
#include <stdlib.h>

// Function to get dimensions and values for two matrices
void get_number(int **matA, int **matB, int *row, int *col) {
    printf("Type your rows : ");	// Prompt user for the number of rows
    scanf("%d", row);			// Read number of rows into the pointer variable `row`
    printf("Type your cols : ");	// Prompt user for the number of columns
    scanf("%d", col);			// Read number of columns into the pointer variable `col`

    // Allocate memory dynamically for the two matrices based on rows and columns
    *matA = malloc((*row) * (*col) * sizeof(int));	// Allocate memory for Matrix A
    *matB = malloc((*row) * (*col) * sizeof(int));	// Allocate memory for Matrix B

    printf("--------------------\n");	// Separator for better readability
    printf("Enter values for Matrix A\n");		// Inform the user to input values for Matrix A

    for (int i = 0; i < *col; i++) {		// Loop to display the number of cols as stars
        printf("* ");				// Print a star for each cols
    }
    printf(" <--- This is your cols\n");		// Indicate the printed stars represent cols

    // Input values into Matrix A
    for (int i = 0; i < (*row) * (*col); i++) {
        scanf("%d", (*matA) + i);			// Read values directly into allocated memory for Matrix A
    }

    printf("--------------------\n");	// Separator for better readability
    printf("Enter values for Matrix B\n");		// Inform the user to input values for Matrix B

    for (int i = 0; i < *col; i++) {		// Loop to display the number of cols as stars
        printf("* ");				// Print a star for each cols
    }
    printf(" <--- This is your cols\n");		// Indicate the printed stars represent cols

    // Input values into Matrix B
    for (int i = 0; i < (*row) * (*col); i++) {
        scanf("%d", (*matB) + i);			// Read values directly into allocated memory for Matrix B
    }
}

// Function to compute the difference of two matrices and print the result
void add_and_print(int *matA, int *matB, int row, int col) {
    // Allocate memory dynamically for the result matrix
    int *summat = malloc(row * col * sizeof(int));	// Allocate memory for the result matrix

    printf("--------------------\n");	// Separator for better readability
    printf("Sum of matrix\n");			// Inform the user about the matrix sum being displayed

    // Compute the difference and print the result
    for (int i = 0; i < row * col; i++) {
        summat[i] = matA[i] - matB[i];		// Subtract corresponding elements of matB from matA
        printf("%d ", summat[i]);		// Print each element of the result matrix

        if ((i + 1) % col == 0) {		// Check if end of a row is reached
            printf("\n");			// Print a newline to start the next row
        }
    }

    free(summat);				// Free the dynamically allocated memory for the result matrix
}

int main() {
    int *matA, *matB;				// Pointers for matrices A and B
    int row, col;				// Variables to store the dimensions of the matrices

    get_number(&matA, &matB, &row, &col);	// Call function to get input matrices and their dimensions
    add_and_print(matA, matB, row, col);	// Call function to compute and print matrix sum

    free(matA);				// Free the dynamically allocated memory for Matrix A
    free(matB);				// Free the dynamically allocated memory for Matrix B

    printf("Program is finish!!\n");		// Inform the user that the program has finished execution
    return 0;				// Return 0 to indicate successful execution
}

