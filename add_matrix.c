#include <stdio.h>
#include <stdlib.h>

// Function to input matrix dimensions and populate two matrices
void get_number(int **matA, int **matB, int *row, int *col) {
    printf("Type your rows : ");      // Prompt for the number of rows
    scanf("%d", row);                // Read the number of rows
    printf("Type your cols : ");     // Prompt for the number of columns
    scanf("%d", col);                // Read the number of columns

    *matA = malloc((*row) * (*col) * sizeof(int));    // Allocate memory for matrix A
    *matB = malloc((*row) * (*col) * sizeof(int));    // Allocate memory for matrix B
    printf("--------------------\n");
    printf("Enter values for Matrix A\n");           // Prompt for matrix A values

    for(int i = 0 ; i < *col ; i++) {                // Print cols indicator
        printf("* ");                                // Print asterisk for each cols
    }
    printf(" <--- This is your cols\n");             // Indicate the cols visually
    for(int i = 0; i < (*row) * (*col); i++) {       // Loop to input values for matrix A
        scanf("%d", (*matA) + i);                    // Store values in matrix A
    }
    printf("--------------------\n");
    printf("Enter values for Matrix B\n");           // Prompt for matrix B values

    for(int i = 0 ; i < *col ; i++) {                // Print cols indicator
        printf("* ");                                // Print asterisk for each cols 
    }
    printf(" <--- This is your cols\n");             // Indicate the cols visually
    for(int i = 0; i < (*row) * (*col); i++) {       // Loop to input values for matrix B
        scanf("%d", (*matB) + i);                    // Store values in matrix B
    }
}

// Function to add two matrices and print the result
void add_and_print(int *matA, int *matB, int row, int col) {
    int *summat = malloc(row * col * sizeof(int));   // Allocate memory for the result matrix
    printf("--------------------\n");
    printf("Sum of matrix\n");                       // Print a heading for the result

    for(int i = 0; i < row * col; i++) {             // Loop through each element of matrices
        summat[i] = matA[i] + matB[i];              // Calculate the sum of corresponding elements
        printf("%d ", summat[i]);                   // Print the current element of the sum matrix

        if ((i + 1) % col == 0) {                   // Check if the end of a row is reached
            printf("\n");                           // Print a newline to format the matrix
        }
    }
    free(summat);                                   // Free the allocated memory for the result matrix
}

int main() {
    int *matA, *matB;                               // Declare pointers for matrices A and B
    int row, col;                                   // Variables to hold matrix dimensions

    get_number(&matA, &matB, &row, &col);           // Call function to input matrices
    add_and_print(matA, matB, row, col);            // Call function to add and print matrices

    free(matA);                                     // Free memory allocated for matrix A
    free(matB);                                     // Free memory allocated for matrix B
    
    printf("Program is finish!!\n");                 // Indicate that the program is complete
    return 0;                                       // Exit the program
}

