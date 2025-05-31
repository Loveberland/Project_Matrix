#include <stdio.h>
#include <stdlib.h>
#include "get_size_of_matrix.h"
#include "get_matrix.h"

int determinant(int **mat, int n)
{
	int det = 0;
	if(n == 1)
	{
		return mat[0][0];
	}
	else if(n == 2)
	{
		return mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
	}
	else
	{
		int **temp = (int**)malloc((n - 1) * sizeof(int*));
		for(int i = 0 ; i < n - 1 ; i++)
		{
			temp[i] = (int*)malloc((n - 1) * sizeof(int));
		}
	
		for(int k = 0 ; k < n ; k++)
		{
			int sign = (k % 2 == 0) ? 1 : -1;
		
			int tempRow = 0, tempCol = 0;
			for(int i = 1 ; i < n ; i++)
			{
				for(int j = 0 ; j < n ; j++)
				{
					if(j == k) continue;
					temp[tempRow][tempCol] = mat[i][j];
					tempCol++;
					if(tempCol == n - 1)
					{
						tempCol = 0;
						tempRow++;
					}
				}
			}
			
			det += sign * mat[0][k] * determinant(temp, n - 1);	
	
			for(int i = 0 ; i < n - 1 ; i++)
			{
				free(temp[i]);
			}
			free(temp);
		}
	}	
	return det;
}

void det(int rows, int cols, int ****mat, int ***result)
{
	if(rows != cols)
	{
		printf("Matrix must be squre to calculate determinant\n");
		exit(1);
	}	
	
	*result = (int**)malloc(rows * sizeof(int*));
	if(*result == NULL)
	{
		printf("ERROR\n");
		exit(1);
	}
	(*result)[0] = (int *)malloc(sizeof(int));
	if((*result)[0] == NULL)
	{
		printf("ERROR\n");
		exit(1);
	}	
	(*result)[0][0] = determinant(*mat[0], rows);
}

void main()
{
	int rows, cols, ***mat, **result, count = 1;

	get_size_of_matrix(&rows, &cols);

	get_matrix_for_real(&mat, rows, cols, count);

	det(rows, cols, &mat, &result);
	
	printf("\n------------------------------\n\n");
	printf("Answer of determinant is %d\n", result[0][0]);

	for(int i = 0 ; i < rows ; i++)
	{
		free(mat[i]);
	}	
	free(mat);
	free(result[0]);
	free(result);
}

