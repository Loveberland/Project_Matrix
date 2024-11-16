#include <stdio.h>
#include <stdlib.h>

void get_rows_cols(int *rows, int *cols) {
  printf("Type your rows : ");                      // Prompt user to input the number of rows
  scanf("%d", rows);                                // Read the number of rows
  printf("Type your cols : ");                      // Prompt user to input the number of columns
  scanf("%d", cols);                                // Read the number of columns
}

void get_matrix(int **mat, int rows, int cols) {
  printf("--------------------\n");                   // Print a separator for clarity
  printf("Type your matrix\n");                     // Prompt user to input the matrix elements
  for (int i = 0 ; i < cols ; i++) {                // Print column indices marker
    printf("* ");                                   // Print marker for each column
  }
  printf("<--- This is your cols\n");               // Explain the marker above
  
  for (int i = 0; i < rows; i++) {                  // Loop through each row
    for (int j = 0; j < cols; j++) {                // Loop through each column in the row
      scanf("%d", &mat[i][j]);                      // Read the matrix element at position [i][j]
    }
  }
}

int **create_minor_matrix(int **mat, int rows, int cols, int excluded_col) {
  int **minor = (int **)malloc((rows - 1) * sizeof(int *)); // Allocate memory for the minor matrix
  for (int i = 0; i < rows - 1; i++) {            // Allocate memory for each row in the minor matrix
    minor[i] = (int *)malloc((cols - 1) * sizeof(int));
  }

  for (int i = 1; i < rows; i++) {                // Loop through rows, skipping the first row
    int minor_col = 0;                            // Initialize column index for the minor matrix
    for (int j = 0; j < cols; j++) {              // Loop through columns of the original matrix
      if (j == excluded_col)                      // Skip the column that is excluded
        continue;
      minor[i - 1][minor_col++] = mat[i][j];      // Copy element to the minor matrix
    }
  }
  return minor;                                   // Return the constructed minor matrix
}

void free_matrix(int **mat, int rows) {
  for (int i = 0; i < rows; i++) {                // Loop through each row
    free(mat[i]);                                 // Free memory allocated for each row
  }
  free(mat);                                      // Free the top-level pointer
}

int det(int **mat, int rows, int cols) {
  if (rows == 1 && cols == 1) {                   // Base case: 1x1 matrix
    return mat[0][0];                             // Determinant is the single element
  } else if (rows == 2 && cols == 2) {            // Base case: 2x2 matrix
    return (mat[0][0] * mat[1][1]) -              // Determinant formula for 2x2 matrix
           (mat[0][1] * mat[1][0]);
  }

  int determinant = 0;                            // Initialize determinant value
  for (int col = 0; col < cols; col++) {          // Loop through each column of the first row
    int **minor = create_minor_matrix(mat, rows, cols, col); // Create minor matrix excluding column
    int sign = (col % 2 == 0) ? 1 : -1;           // Calculate sign based on column index
    determinant += sign * mat[0][col] *           // Add contribution to determinant
                   det(minor, rows - 1, cols - 1);
    free_matrix(minor, rows - 1);                 // Free memory for minor matrix
  }
  return determinant;                             // Return the determinant value
}

void main() {
  int rows, cols;                                 // Variables to store number of rows and columns
  get_rows_cols(&rows, &cols);                    // Get rows and columns from user

  if (rows != cols) {                             // Check if matrix is not square
    printf("Determinant is only defined for square matrices\n"); // Print error message
    printf("Program is finish!!\n");              // Indicate program termination
    return;                                       // Exit the program
  }

  int **mat = (int **)malloc(rows * sizeof(int *)); // Allocate memory for the matrix
  if (mat == NULL) {                              // Check for memory allocation failure
    printf("Memory allocation failed\n");         // Print error message
    printf("Program is finish!!\n");              // Indicate program termination
    exit(1);                                      // Exit with error code
  }
  for (int i = 0; i < rows; i++) {                // Loop through each row
    mat[i] = (int *)malloc(cols * sizeof(int));   // Allocate memory for each row
    if (mat[i] == NULL) {                         // Check for memory allocation failure
      printf("Memory allocation failed\n");       // Print error message
      printf("Program is finish!!\n");            // Indicate program termination
      exit(1);                                    // Exit with error code
    }
  }

  get_matrix(mat, rows, cols);                    // Get matrix elements from user
  int result = det(mat, rows, cols);              // Calculate determinant
  
  printf("--------------------\n");                   // Print a separator
  printf("Determinant : %d\n", result);           // Print the calculated determinant

  free_matrix(mat, rows);                         // Free memory allocated for the matrix
  printf("Program is finish!!\n");                // Indicate program termination
}

