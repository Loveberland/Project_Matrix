#include <stdio.h>
#include <stdlib.h>

void get_dimension(int *rows, int *cols)
{
    printf("Type your rows: ");    // Function to get the matrix dimensions (rows and columns) from the user
    scanf("%d", rows);             // Store the number of rows entered by the user in the variable pointed to by rows

    printf("Type your cols: ");    // Prompt user to enter the number of columns
    scanf("%d", cols);             // Store the number of columns entered by the user in the variable pointed to by cols
}

void get_matrix(int ***matA, int ***matB, int rows, int cols)
{
    *matA = (int **)malloc(rows * sizeof(int *));    // Allocate memory for matA as an array of pointers (each representing a row)
    *matB = (int **)malloc(rows * sizeof(int *));    // Allocate memory for matB as an array of pointers (each representing a row)
    
    for (int i = 0; i < rows; i++)
    {
        (*matA)[i] = (int *)malloc(cols * sizeof(int));    // Allocate memory for each column in row i of matA
        (*matB)[i] = (int *)malloc(cols * sizeof(int));    // Allocate memory for each column in row i of matB
    }

    printf("Enter elements for matrix A:\n");    // Prompt user to enter values for matrix A

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            scanf("%d", &(*matA)[i][j]);    // Store each element in row i and column j of matA
        }
    }

    printf("Enter elements for matrix B:\n");    // Prompt user to enter values for matrix B

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            scanf("%d", &(*matB)[i][j]);    // Store each element in row i and column j of matB
        }
    }
}

void multiply(int **matA, int **matB, int rows, int cols)
{
    int **result = (int **)malloc(rows * sizeof(int *));    // Allocate memory for the result matrix

    for (int i = 0; i < rows; i++)
    {
        result[i] = (int *)malloc(cols * sizeof(int));    // Allocate memory for each row in result
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            result[i][j] = 0;    // Initialize the result element at (i, j) to 0

            for (int k = 0; k < cols; k++)
            {
                result[i][j] += matA[i][k] * matB[k][j];    // Accumulate the product of corresponding elements of matA and matB for result[i][j]
            }
        }
    }

    printf("Result of matrix multiplication:\n");    // Display the result matrix

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            printf("%d ", result[i][j]);    // Print each element in result
        }
        printf("\n");    // Newline after each row
    }

    for (int i = 0; i < rows; i++)
    {
        free(result[i]);    // Free memory allocated for each row in result
    }
    free(result);    // Free the array of row pointers
}

void main()
{
    int rows, cols;               // Variables to store matrix dimensions
    int **matA, **matB;           // Pointers to store dynamically allocated matrices

    get_dimension(&rows, &cols);    // Get matrix dimensions from the user
    get_matrix(&matA, &matB, rows, cols);    // Populate matA and matB with user input
    multiply(matA, matB, rows, cols);    // Multiply matrices and display the result

    for (int i = 0; i < rows; i++)
    {
        free(matA[i]);    // Free memory allocated for each row in matA
        free(matB[i]);    // Free memory allocated for each row in matB
    }
    free(matA);    // Free the array of row pointers for matA
    free(matB);    // Free the array of row pointers for matB
}

