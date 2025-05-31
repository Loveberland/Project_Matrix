#include <stdio.h>
#include <stdlib.h>
#include "get_size_of_matrix.h"
#include "get_count_of_matrix.h"
#include "get_matrix.h"

void multiply(int rows, int cols, int count, int ***mat, int ***result)
{
	*result = (int**)malloc(rows * sizeof(int*));
	if(*result == NULL)
	{
		printf("ERROR\n");
		exit(1);
	}
	for(int i = 0 ; i < rows ; i++)
	{
		(*result)[i] = (int*)malloc(cols * sizeof(int));
		if((*result)[i] == NULL)
		{
			printf("ERROR\n");
			exit(1);	
		}	
	}

	for(int i = 0 ; i < rows ; i++)
	{
		for(int j = 0 ; j < cols ; j++)
		{
			(*result)[i][j] = mat[0][i][j];
		}
	}

	for(int c = 1 ; c < count ; c++)
	{
		int **temp = (int**)malloc(rows * sizeof(int*));
		for(int i = 0 ; i < rows ; i++)
		{
			temp[i] = (int*)malloc(cols * sizeof(int));
		}
		for(int i = 0 ; i < rows ; i++)
		{
			for(int j = 0 ; j < cols ; j++)
			{
				temp[i][j] = 0;
				for(int k = 0 ; k < cols ; k++)
				{
					temp[i][j] += (*result)[i][k] * mat[c][k][j];
				}
			}
		}	
		for(int i = 0 ; i < rows ; i++)
		{
			for(int j = 0 ; j < cols ; j++)
			{
				(*result)[i][j] = temp[i][j];
			}
		}	
		for(int i = 0 ; i < rows ; i++)
		{
			free(temp[i]);
		}	
		free(temp);	
	}		
}

void main()
{
	int rows, cols, count, ***mat, **result;
	
	get_size_of_matrix(&rows, &cols);

	get_count_of_matrix(&count);

	get_matrix_for_real(&mat,rows, cols, count);

	multiply(rows, cols, count, mat, &result);

	printf("\n------------------------------\n\n");
	printf("This is answer of multiply matrix\n");
	for(int i = 0 ; i < rows ; i++)
	{
		for(int j = 0 ; j < cols ; j++)
		{
			printf("%d ",result[i][j]);
		}
		printf("\n");
	}
	for(int i = 0 ; i < rows ; i++)
	{
		free(result[i]);
	}
	free(result);
	for(int i = 0 ; i < rows ; i++)
	{
		for(int j = 0 ; j < cols ; j++)
		{
			free(mat[i][j]);
		}
	}
	free(mat);
}

