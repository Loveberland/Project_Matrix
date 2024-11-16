#include <stdio.h>
#include <stdlib.h>

// Function to get matrix dimensions from the user
void get_dimension(int *rows, int *cols)
{
    printf("Type your rows : ");           // Prompt user for number of rows
    scanf("%d", rows);                    // Read the number of rows
    printf("Type your cols : ");          // Prompt user for number of columns
    scanf("%d", cols);                    // Read the number of columns
}

// Function to allocate memory and get matrix values from the user
void get_matrix(int ***matA, int ***matB, int rows, int cols)
{
    *matA = (int **)malloc(rows * sizeof(int *));   // Allocate memory for matrix A's rows
    *matB = (int **)malloc(rows * sizeof(int *));   // Allocate memory for matrix B's rows
    
    for (int i = 0; i < rows; i++) 
    {
        (*matA)[i] = (int *)malloc(cols * sizeof(int));  // Allocate memory for matrix A's columns
        (*matB)[i] = (int *)malloc(cols * sizeof(int));  // Allocate memory for matrix B's columns
    }
    
    printf("-------------------\n");                     // Display separator
    printf("Enter values for matrix A\n");            // Prompt user for matrix A values
    for(int i = 0 ; i < cols ; i++) 
    {
        printf("* ");                                 // Print column markers for clarity
    }
    printf("<--- This is your cols\n");               // Indicate this is the column count line
    
    for (int i = 0; i < rows; i++) 
    {
        for (int j = 0; j < cols; j++) 
        {
            scanf("%d", &(*matA)[i][j]);             // Read values into matrix A
        }
    }
    
    printf("-------------------\n");                    // Display separator
    printf("Enter values for matrix B\n");           // Prompt user for matrix B values
    for(int i = 0 ; i < cols ; i++) 
    {
        printf("* ");                                // Print column markers for clarity
    }
    printf("<--- This is your cols\n");              // Indicate this is the column count line
    
    for (int i = 0; i < rows; i++) 
    {
        for (int j = 0; j < cols; j++) 
        {
            scanf("%d", &(*matB)[i][j]);            // Read values into matrix B
        }
    }
}

// Function to multiply two matrices
void multiply(int **matA, int **matB, int rows, int cols)
{
    int **result = (int **)malloc(rows * sizeof(int *)); // Allocate memory for result matrix

    for (int i = 0; i < rows; i++) 
    {
        result[i] = (int *)malloc(cols * sizeof(int));   // Allocate memory for result matrix's columns
    }

    for (int i = 0; i < rows; i++) 
    {
        for (int j = 0; j < cols; j++) 
        {
            result[i][j] = 0;                           // Initialize result matrix cell to 0

            for (int k = 0; k < cols; k++) 
            {
                result[i][j] += matA[i][k] * matB[k][j]; // Compute the matrix multiplication
            }
        }
    }
    printf("--------------------\n");                   // Display separator
    printf("Result of matrix multiplication\n");      // Print result header

    for (int i = 0; i < rows; i++) 
    {
        for (int j = 0; j < cols; j++) 
        {
            printf("%d ", result[i][j]);              // Print each value in the result matrix
        }
        printf("\n");                                 // Move to the next line for each row
    }

    for (int i = 0; i < rows; i++) 
    {
        free(result[i]);                              // Free memory allocated for result rows
    }
    free(result);                                     // Free memory allocated for result matrix
}

// Main function
void main()
{
    int rows, cols;                                  // Variables for dimensions
    int **matA, **matB;                              // Pointers for matrices

    get_dimension(&rows, &cols);                    // Get dimensions from the user
    get_matrix(&matA, &matB, rows, cols);           // Allocate and populate matrices
    multiply(matA, matB, rows, cols);               // Multiply the matrices

    for (int i = 0; i < rows; i++) 
    {
        free(matA[i]);                              // Free memory allocated for matrix A rows
        free(matB[i]);                              // Free memory allocated for matrix B rows
    }
    free(matA);                                     // Free memory allocated for matrix A
    free(matB);                                     // Free memory allocated for matrix B
    printf("Program is finish\n");                  // Indicate program termination
}

