#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "get_size_of_matrix.h"
#include "get_count_of_matrix.h"
#include "get_matrix.h"

void add(int rows, int cols,int count, int ***result,int ***mat)
{
	*result = (int**)malloc((rows * count) * sizeof(int*));
	if(*result == NULL)
	{
		printf("ERROR\n");
		exit(1);
	}
	for(int i = 0 ; i < rows ; i++)
	{
		(*result)[i] = (int*)malloc((cols * count) * sizeof(int));
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
			for(int k = 0 ; k < count ; k++)
			{
				(*result)[i][j] -= mat[k][i][j];
			}	
		}
	}
}

void main()
{
	int rows, cols, count, **result , ***mat;

	get_size_of_matrix(&rows,&cols);	
	
	get_count_of_matrix(&count);
	
	get_matrix_for_real(&mat,rows,cols,count);	

	add(rows,cols,count,&result,mat);

	printf("\n------------------------------\n\n");
	printf("This is answer of add matrix\n");	
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

