#include <stdio.h>
#include <stdlib.h>
#include "get_matrix.h"

void get_matrix(int ***mat, int rows, int cols, int count)
{
	// Reserve memory	
	*mat = (int**)malloc(rows * sizeof(int*));
	if(*mat == NULL)
	{
		printf("ERROR\n");
		exit(1);
	}
	for(int i = 0 ; i < rows ; i++)
	{
		(*mat)[i] = (int*)malloc(cols * sizeof(int));
		if((*mat) == NULL)
		{
			printf("ERROR\n");
			exit(1);	
		}
	}
	
	while(1)
	{
		printf("Type your matrix %d here \n",count);		
		for(int i = 0 ; i < cols ; i++)	
		{	
				printf("* ");
		}		
		printf("<--- This is your cols\n");	
		
		int vaild = 1;	
		for(int i = 0 ; i < rows ; i++)
		{
			for(int j = 0 ; j < cols ; j++)
			{
				int temp;	
				if(scanf("%d",&temp) != 1)
				{
					printf("Type your matrix (please type only number)\n");
					for(int k = 0 ; k < cols ; k++)
					{
						printf("* ");
					}
					printf("<--- This is your cols\n");
					vaild = 0;
					while(getchar() != '\n')
					{
						break;
					}	
				}
				(*mat)[i][j] = temp;	
			}
			if(!vaild) break;	
		}
		if(vaild) break;	
	}
}

void get_matrix_for_real(int ****mat, int rows, int cols, int count)
{
	*mat = (int ***)malloc(count * sizeof(int**));
	if(*mat == NULL)
	{
		printf("ERROR\n");
		exit(1);
	}
	for(int k = 0 ; k < count ; k++)
	{
		get_matrix(&((*mat)[k]), rows, cols, k+1);
	}
}

